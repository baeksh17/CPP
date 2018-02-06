#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Mutex.h"
#include "Poco/SingletonHolder.h"
#include <iostream>
#include <thread>
#include "WebSocketContainer.hpp"
#include "CommonDef.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

WebSoc::WebSocketContainer* WebSoc::WebSocketContainer::sockCon = nullptr;
Poco::Net::WebSocket* WebSoc::WebSocketContainer::socket = nullptr;
Poco::Net::HTTPClientSession* WebSoc::WebSocketContainer::cs = nullptr;

class WebSocketReceiver
{

private:
    
public:
    WebSocketReceiver() {}
    
    void HandleReceiveData()
    {
        Poco::FastMutex::ScopedLock lock(::mutex);
        WebSoc::WebSocketContainer::create();
        WebSoc::WebSocketContainer& sockCon = WebSoc::WebSocketContainer::getInstance();
        WebSocket& socket = sockCon.getSocketInstance();
        char receiveBuff[256];
        int flags = 0;
        Poco::Timespan timeOut(0.1, 0);

        if (socket.poll(timeOut, Poco::Net::Socket::SELECT_READ) == false) {
            std::cout << "TIME OUT" << std::endl;
        } else {
            int rlen = socket.receiveFrame(receiveBuff, 256, flags);
            std::cout << "Received bytes : " << rlen << std::endl;
            std::cout << receiveBuff << std::endl;
        }
    }
};

class WebSocketSender
{
    
private:
    
public:
    WebSocketSender() {}
    
    void HandleSendData( void )
    {
        Poco::FastMutex::ScopedLock lock(::mutex);
        WebSoc::WebSocketContainer::create();
        WebSoc::WebSocketContainer& sockCon = WebSoc::WebSocketContainer::getInstance();
        WebSocket& socket = sockCon.getSocketInstance();
        char const *testStr = "Hello World!!!";
        int len = socket.sendFrame(testStr, strlen(testStr), WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes : " << len << std::endl;
    }
};

void Sender()
{
    WebSocketSender sender;
    while (true) {
        sender.HandleSendData();
        sleep(1);
    }
}

void Receiver()
{
    WebSocketReceiver receiver;
    while(true) {
        receiver.HandleReceiveData();
        sleep(1);
    }
}

int main(int args,char **argv)
{
    std::thread t2(Receiver);
    std::thread t1(Sender);
    
    
    t2.join();
    t1.join();
    
    
    return 0;
}
