//
//  Receiver.hpp
//  WebSocketClient
//
//  Created by donghyun Kim on 2018. 2. 6..
//  Copyright © 2018년 donghyun Kim. All rights reserved.
//

#ifndef Receiver_hpp
#define Receiver_hpp

#include <stdio.h>
#include "CommonDef.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/SingletonHolder.h"
#include <iostream>
#include <thread>
#include "WebSocketContainer.hpp"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;



class Receiver
{
private:
    
public:
    Receiver();
    ~Receiver();
    
    void HandleReceiveData(void);
};

#endif /* Receiver_hpp */
