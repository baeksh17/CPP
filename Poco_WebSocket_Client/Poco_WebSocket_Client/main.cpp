#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/SingletonHolder.h"
#include <iostream>
#include <thread>
#include "WebSocketContainer.hpp"
#include "CommonDef.h"
#include "Receiver.hpp"
#include "Sender.hpp"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

WebSoc::WebSocketContainer* WebSoc::WebSocketContainer::sockCon = nullptr;
Poco::Net::WebSocket* WebSoc::WebSocketContainer::socket = nullptr;
Poco::Net::HTTPClientSession* WebSoc::WebSocketContainer::cs = nullptr;

Poco::FastMutex mutex;

void Sender()
{
    class Sender sender;
    while (true) {
        sender.HandleSendData();
        sleep(1);
    }
}

void Receiver()
{
    class Receiver receiver;
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
