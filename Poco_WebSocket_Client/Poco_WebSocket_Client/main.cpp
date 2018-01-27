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

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

Poco::FastMutex mutex;

WebSoc::WebSocketContainer* WebSoc::WebSocketContainer::sockCon = nullptr;
Poco::Net::WebSocket* WebSoc::WebSocketContainer::socket = nullptr;

class WebSocketReceiver
{
    
private:
    
public:
    WebSocketReceiver() {}
    
    void HandleReceiveData()
    {
        Poco::FastMutex::ScopedLock lock(::mutex);
        WebSoc::WebSocketContainer& sockCon = WebSoc::WebSocketContainer::getInstance();
        WebSocket& socket = sockCon.getSocketInstance();
        char receiveBuff[256];
        int flags = 0;
        Poco::Timespan timeOut(10, 0);
        
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
    
    void HandleSendData()
    {
        Poco::FastMutex::ScopedLock lock(::mutex);
        WebSoc::WebSocketContainer::create();
        WebSoc::WebSocketContainer& sockCon = WebSoc::WebSocketContainer::getInstance();
        WebSocket& socket = sockCon.getSocketInstance();
        char const *testStr = "Hello Echo Websocket!";
        int len = socket.sendFrame(testStr, strlen(testStr), WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes : " << len << std::endl;
    }
};

void Sender()
{
    WebSocketSender sender;
    for(int i = 0; i < 5; i++)
        sender.HandleSendData();
}

void Receiver()
{
    WebSocketReceiver receiver;
    receiver.HandleReceiveData();
}

int main(int args,char **argv)
{
    std::thread t1(Sender);
    std::thread t2(Receiver);
    
    t1.join();
    t2.join();
    
//    sleep(10);
    return 0;
}

