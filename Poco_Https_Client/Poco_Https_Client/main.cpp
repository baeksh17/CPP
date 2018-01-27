#include <string>
#include <iostream>
#include <sstream>

#include "Poco/URI.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/AcceptCertificateHandler.h"
using namespace std;

int main(int argc, char **argv)
{
    
    // SSL接続情報 初期化
    Poco::Net::initializeSSL();
    Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler ( new Poco::Net::AcceptCertificateHandler(false) );
    Poco::Net::Context::Ptr ptrContext ( new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "") );
    Poco::Net::SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);
    
    
    try {
        Poco::URI uri("https://localhost:9443");
        Poco::Net::HTTPSClientSession session(uri.getHost(), 9443);
        Poco::Net::HTTPRequest req("GET", "https://localhost:9443", Poco::Net::HTTPMessage::HTTP_1_1);
        
        // リクエスト送信
        ostream& ss = session.sendRequest(req);
        
        // レスポンス受信
        Poco::Net::HTTPResponse res;
        istream& rs = session.receiveResponse(res);
        
        stringstream sstr;
        Poco::StreamCopier::copyStream(rs, sstr);
        string response = sstr.str();
        cout << string("response:") + response << endl;
    }
    catch ( Poco::Exception& ex )
    {
        string msg = string("Poco Exception : ") + ex.what() + ", message: " + ex.message();
        cout << msg << endl;
    }
    
    return 0;
}
