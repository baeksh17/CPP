//
//  Receiver.cpp
//  WebSocketClient
//
//  Created by donghyun Kim on 2018. 2. 6..
//  Copyright © 2018년 donghyun Kim. All rights reserved.
//

#include "Receiver.hpp"

Receiver::Receiver() {}
Receiver::~Receiver() {}
    
void Receiver::HandleReceiveData()
{
    Poco::FastMutex::ScopedLock lock(mutex);
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
