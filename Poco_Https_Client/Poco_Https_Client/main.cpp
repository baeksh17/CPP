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
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"

using namespace std;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::SharedPtr;
using Poco::Exception;
using Poco::Net::SSLManager;
using Poco::Net::Context;
using Poco::Net::KeyConsoleHandler;
using Poco::Net::PrivateKeyPassphraseHandler;
using Poco::Net::InvalidCertificateHandler;
using Poco::Net::ConsoleCertificateHandler;



int main(int argc, char **argv)
{
    
    // SSL接続情報 初期化
    Poco::Net::initializeSSL();
//    Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrHandler ( new Poco::Net::AcceptCertificateHandler(false) );
    Poco::SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new Poco::Net::KeyConsoleHandler(true);
    Poco::SharedPtr<InvalidCertificateHandler> ptrCert = new ConsoleCertificateHandler(false);
    
    Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    Poco::Net::SSLManager::instance().initializeClient(pConsoleHandler, ptrCert, ptrContext);
    
    
    try {
        Poco::URI uri("https://localhost:9443");
        uri.addQueryParameter("key","value");
        Poco::Net::HTTPSClientSession session(uri.getHost(), 9443);
        Poco::Net::HTTPRequest req("GET", uri.toString(), Poco::Net::HTTPMessage::HTTP_1_1);
        
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
