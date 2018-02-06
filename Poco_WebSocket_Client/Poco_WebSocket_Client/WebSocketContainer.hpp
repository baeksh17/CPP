//
//  WebSocketContainer.hpp
//  WebSocketClient
//
//  Created by donghyun Kim on 2018. 1. 21..
//  Copyright © 2018년 donghyun Kim. All rights reserved.
//

#ifndef WebSocketContainer_hpp
#define WebSocketContainer_hpp

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Mutex.h"
#include "Poco/SingletonHolder.h"
#include <iostream>
#include <thread>
#include <stdio.h>

namespace WebSoc {

    class WebSocketContainer {
        
    private:
        WebSocketContainer();
        ~WebSocketContainer();
        static WebSocketContainer* sockCon;
        static Poco::Net::WebSocket* socket;
        static Poco::Net::HTTPClientSession* cs;
        
    public:
        WebSocketContainer(const WebSocketContainer&) = delete;
        WebSocketContainer& operator=(const WebSocketContainer&) = delete;
        WebSocketContainer(WebSocketContainer&&) = delete;
        WebSocketContainer& operator=(WebSocketContainer&&) = delete;
        
        static WebSocketContainer& getInstance(void);
        static Poco::Net::WebSocket& getSocketInstance(void);
        static Poco::Net::HTTPClientSession& getSessionInstance(void);
        static void create(void);
        static void destroy(void);
        
    };
}
#endif /* WebSocketContainer_hpp */
