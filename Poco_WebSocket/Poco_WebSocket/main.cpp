#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include <iostream>

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

class WebSocketTest {
    
private:
    WebSocketTest() = default;
    ~WebSocketTest() = default;
    
    static WebSocket* m_psock;
    static WebSocketTest* instance;
    
public:
    WebSocketTest(const WebSocketTest&) = delete;
    WebSocketTest& operator=(const WebSocketTest&) = delete;
    WebSocketTest(WebSocketTest&&) = delete;
    WebSocketTest& operator=(WebSocketTest&&) = delete;
    
    static WebSocket& getInstance()
    {
        if ( !m_psock )
        {
            HTTPClientSession cs("localhost", 9980);
            HTTPRequest request(HTTPRequest::HTTP_GET, "/?encoding=text", HTTPMessage::HTTP_1_1);
            request.set("origin", "http://localhost");
            HTTPResponse response;
            
            m_psock = new WebSocket(cs, request, response);
        }
        return *m_psock;
    }
    
    static void destroy()
    {
        if ( m_psock )
        {
            delete m_psock;
            m_psock = nullptr;
        }
    }
    
};

class WebSocketReceiver
{
    
private:
    
public:
    WebSocketReceiver() {}
    
    void HandleReceiveData()
    {
        WebSocket& m_psock = WebSocketTest::getInstance();
        char receiveBuff[256];
        int flags = 0;
        int rlen = m_psock.receiveFrame(receiveBuff, 256, flags);
        std::cout << "Received bytes : " << rlen << std::endl;
        std::cout << receiveBuff << std::endl;
    }
};

class WebSocketSender
{
    
private:
    
public:
    WebSocketSender() {}
    
    void HandleSendData()
    {
        WebSocket& m_psock = WebSocketTest::getInstance();
        char const *testStr = "Hello Echo Websocket!";
        int len = m_psock.sendFrame(testStr, strlen(testStr), WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes : " << len << std::endl;
    }
};

int main(int args,char **argv)
{
    
    
    try {
        
        WebSocket* m_psock = nullptr;
        m_psock = WebSocketTest::getInstance();
        
        char const *testStr="Hello echo websocket!";
        char receiveBuff[256];
        
        int len=m_psock->sendFrame(testStr,strlen(testStr),WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes " << len << std::endl;
        int flags=0;
        
        int rlen=m_psock->receiveFrame(receiveBuff,256,flags);
        std::cout << "Received bytes " << rlen << std::endl;
        std::cout << receiveBuff << std::endl;
        
        m_psock.close();
        
    } catch (std::exception &e) {
        std::cout << "Exception " << e.what();
    }
    
}

