//
//  WebSocketContainer.cpp
//  WebSocketClient
//
//  Created by donghyun Kim on 2018. 1. 21..
//  Copyright © 2018년 donghyun Kim. All rights reserved.
//

#include "WebSocketContainer.hpp"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

namespace WebSoc {
    
    WebSocketContainer::WebSocketContainer()
    {
        sockCon = NULL;
        socket = NULL;
        cs = NULL;
    }
    WebSocketContainer::~WebSocketContainer()
    {
        
    }
    
    WebSocketContainer& WebSocketContainer::getInstance()
    {
        return *sockCon;
    }
    
    WebSocket& WebSocketContainer::getSocketInstance()
    {
        return *socket;
    }
    
    HTTPClientSession& WebSocketContainer::getSessionInstance()
    {
        return *cs;
    }
    
    void WebSocketContainer::create() {
        if ( !sockCon )
        {
            sockCon = new WebSocketContainer;
        }
        if ( !socket )
        {
            cs = new HTTPClientSession("localhost", 9980);
            HTTPRequest *request = new HTTPRequest(HTTPRequest::HTTP_GET, "/", HTTPMessage::HTTP_1_1);
            request->set("origin", "http://localhost");
            HTTPResponse *response = new HTTPResponse();
            
            socket = new WebSocket(*cs, *request, *response);
            
            delete request;
            delete response;
        }
    }
    
    void WebSocketContainer::destroy()
    {
        if ( socket )
        {
            delete socket;
            delete cs;
        }
    }
}
