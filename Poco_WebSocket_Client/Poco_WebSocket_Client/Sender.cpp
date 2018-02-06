//
//  Sender.cpp
//  WebSocketClient
//
//  Created by donghyun Kim on 2018. 2. 6..
//  Copyright © 2018년 donghyun Kim. All rights reserved.
//

#include "Sender.hpp"

Sender::Sender() {}
Sender::~Sender() {}
    
void Sender::HandleSendData( void )
{
    Poco::FastMutex::ScopedLock lock(mutex);
    WebSoc::WebSocketContainer::create();
    WebSoc::WebSocketContainer& sockCon = WebSoc::WebSocketContainer::getInstance();
    WebSocket& socket = sockCon.getSocketInstance();
    char const *testStr = "Hello World!!!";
    int len = socket.sendFrame(testStr, strlen(testStr), WebSocket::FRAME_TEXT);
    std::cout << "Sent bytes : " << len << std::endl;
}
