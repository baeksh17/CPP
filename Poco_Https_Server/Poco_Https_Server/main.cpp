//
// TimeServer.cpp
//
// This sample demonstrates the HTTPServer and related classes.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:    BSL-1.0
//


#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequestImpl.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Net/X509Certificate.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/SharedPtr.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include <iostream>
#include "Poco/DeflatingStream.h"


using Poco::Net::SecureServerSocket;
using Poco::Net::SecureStreamSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerRequestImpl;
using Poco::Net::X509Certificate;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::SharedPtr;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Net::SSLManager;
using Poco::Net::Context;
using Poco::Net::KeyConsoleHandler;
using Poco::Net::PrivateKeyPassphraseHandler;
using Poco::Net::InvalidCertificateHandler;
using Poco::Net::AcceptCertificateHandler;


class TimeRequestHandler: public HTTPRequestHandler
/// Return a HTML document with the current date and time.
{
public:
    TimeRequestHandler(const std::string& format):
    _format(format)
    {
    }
    
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        std::cout << "start_handleRequest" << std::endl;
        Application& app = Application::instance();
        app.logger().information("Request from " + request.clientAddress().toString());
        
        SecureStreamSocket socket = static_cast<HTTPServerRequestImpl&>(request).socket();
//        socket.completeHandshake();
        
        socket.verifyPeerCertificate();
        if (socket.havePeerCertificate())
        {
            X509Certificate cert = socket.peerCertificate();
            app.logger().information("Client certificate: " + cert.subjectName());
        }
        else
        {
            app.logger().information("No client certificate available.");
        }
        
        Timestamp now;
        std::string dt(DateTimeFormatter::format(now, _format));
        
        response.set("X-Powered-By", "Express");
        response.set("Vary", "Accept-Encoding");
        response.setContentType("application/json; charset=utf-8");
        response.set("ETag", "-32550834");
        response.set("Content-Encoding", "gzip");
        response.setKeepAlive(true);
        response.setChunkedTransferEncoding(true);
        
        std::ostream& ostr = response.send();
//        std::ofstream& ostr = response.send();
//        ostr << response.getReason();
//        ostr << "===================\n";
//        ostr << request.getURI() << "\n";
//        ostr << "============================\n";
        
        std::cout << request.getURI() << std::endl;
        
        Poco::DeflatingOutputStream deflater(ostr, Poco::DeflatingStreamBuf::STREAM_GZIP);
        deflater << "Hello, world!" << std::endl;
//        deflater.close();
//        ostr.close();
        
    }
    
private:
    std::string _format;
};


class TimeRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
    TimeRequestHandlerFactory(const std::string& format):
    _format(format)
    {
        std::cout << "start_TimeRequestHandlerFactory" << std::endl;
    }
    
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
    {
        std::cout << "start_createRequestHandler" << std::endl;
        if (request.getURI() == "/"){
            std::cout << "URI : " << request.getURI() << std::endl;
            return new TimeRequestHandler(_format);
        } else if (request.getURI() == "https://localhost:9443"){
            std::cout << "URI : " << request.getURI() << std::endl;
            return new TimeRequestHandler(_format);
        } else {
            std::cout << "URI : " << request.getURI() << std::endl;
            return new TimeRequestHandler(_format);
        }
        
    }
    
private:
    std::string _format;
};


class HTTPSTimeServer: public Poco::Util::ServerApplication
/// The main application class.
///
/// This class handles command-line arguments and
/// configuration files.
/// Start the HTTPTimeServer executable with the help
/// option (/help on Windows, --help on Unix) for
/// the available command line options.
///
/// To use the sample configuration file (HTTPTimeServer.properties),
/// copy the file to the directory where the HTTPTimeServer executable
/// resides. If you start the debug version of the HTTPTimeServer
/// (HTTPTimeServerd[.exe]), you must also create a copy of the configuration
/// file named HTTPTimeServerd.properties. In the configuration file, you
/// can specify the port on which the server is listening (default
/// 9443) and the format of the date/time string sent back to the client.
///
/// To test the TimeServer you can use any web browser (https://localhost:9443/).
{
public:
    HTTPSTimeServer(): _helpRequested(false)
    {
        std::cout << "start_initializeSSL" << std::endl;
        Poco::Net::initializeSSL();
    }
    
    ~HTTPSTimeServer()
    {
        Poco::Net::uninitializeSSL();
    }
    
protected:
    void initialize(Application& self)
    {
        loadConfiguration(); // load default configuration files, if present
        ServerApplication::initialize(self);
    }
    
    void uninitialize()
    {
        ServerApplication::uninitialize();
    }
    
    void defineOptions(OptionSet& options)
    {
        ServerApplication::defineOptions(options);
        
        options.addOption(
                          Option("help", "h", "display help information on command line arguments")
                          .required(false)
                          .repeatable(false));
    }
    
    void handleOption(const std::string& name, const std::string& value)
    {
        ServerApplication::handleOption(name, value);
        
        if (name == "help")
            _helpRequested = true;
    }
    
    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A web server that serves the current date and time.");
        helpFormatter.format(std::cout);
    }
    
    int main(const std::vector<std::string>& args)
    {
        if (_helpRequested)
        {
            displayHelp();
        }
        else
        {
            // get parameters from configuration file
            unsigned short port = (unsigned short) config().getInt("HTTPSTimeServer.port", 9443);
            std::string format(config().getString("HTTPSTimeServer.format", DateTimeFormat::SORTABLE_FORMAT));
            
            Context::Ptr pContext = new Context(Context::SERVER_USE, "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", "/Users/bko117/Desktop/Git/CPP/Poco_Https_Server/cert.pem", Context::VERIFY_ONCE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
            
            // set-up a server socket
//            SecureServerSocket svs(port, 64, pContext);
            SecureServerSocket svs(port, 64, pContext);
            // set-up a HTTPServer instance
            HTTPServer srv(new TimeRequestHandlerFactory(format), svs, new HTTPServerParams);
            // start the HTTPServer
            srv.start();
            std::cout << "start_HttpServer" << std::endl;
            // wait for CTRL-C or kill
            waitForTerminationRequest();
            // Stop the HTTPServer
            std::cout << "end" << std::endl;
            srv.stop();
        }
        return Application::EXIT_OK;
    }
    
private:
    bool _helpRequested;
};


int main(int argc, char** argv)
{
    HTTPSTimeServer app;
    return app.run(argc, argv);
}
