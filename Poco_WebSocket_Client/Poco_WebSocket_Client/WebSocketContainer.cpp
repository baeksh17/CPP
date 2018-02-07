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

WebSoc::WebSocketContainer* WebSoc::WebSocketContainer::sockCon = nullptr;
Poco::Net::WebSocket* WebSoc::WebSocketContainer::socket = nullptr;
Poco::Net::HTTPSClientSession* WebSoc::WebSocketContainer::cs = nullptr;

namespace WebSoc {
    
    WebSocketContainer::WebSocketContainer( void )
    {
    }
    
    WebSocketContainer::~WebSocketContainer( void )
    {
    }
    
    WebSocketContainer& WebSocketContainer::getInstance( void )
    {
        return *sockCon;
    }
    
    WebSocket& WebSocketContainer::getSocketInstance( void )
    {
        return *socket;
    }
    
    HTTPClientSession& WebSocketContainer::getSessionInstance( void )
    {
        return *cs;
    }
    
    void WebSocketContainer::create( void ) {
        
        if ( !sockCon )
        {
            sockCon = new WebSocketContainer;
        }
        if ( !socket )
        {
            // =================================================================================
            Poco::Net::initializeSSL();
            Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> pConsoleHandler = new Poco::Net::KeyConsoleHandler(true);
            Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptrCert = new Poco::Net::ConsoleCertificateHandler(false);
            Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/rootcert.pem", Poco::Net::Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
            Poco::Net::SSLManager::instance().initializeClient(pConsoleHandler, ptrCert, ptrContext);
            
            //            Poco::Net::HTTPSClientSession session("localhost", 9980);
            // =================================================================================
            
            
            cs = new HTTPSClientSession("localhost", 9443);
            HTTPRequest *request = new HTTPRequest(HTTPRequest::HTTP_GET, "/", HTTPMessage::HTTP_1_1);
            request->set("origin", "http://localhost");
            HTTPResponse *response = new HTTPResponse();
            
            if ( cs->secure() ) {
                std::cout << "secure!!\n";
            }
            else
            {
                std::cout << "fail secure!!\n";
            }
            socket = new WebSocket(*cs, *request, *response);
            
            delete request;
            delete response;
        }
    }
    
    void WebSocketContainer::destroy( void )
    {
        if ( socket )
        {
            delete socket;
            delete cs;
        }
    }
}


