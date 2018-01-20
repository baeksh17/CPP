//
// Benchmark.cpp
//
// This sample shows a benchmark of the JSON parser.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:    BSL-1.0
//


#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include <iostream>

class CExtractMap
{
public:
    int ExtractMap(Poco::JSON::Object::Ptr pObject_, std::string pKey = "") {
        
        int result = 0;
        if(pKey != "")
        {
            std::cout << "親のKeyは : " << pKey << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
        std::cout << "" << std::endl;
        std::cout << "this is ExtractMap" << std::endl;
        std::cout << "====================================" << std::endl;
    
        for(Poco::JSON::Object::ConstIterator it = pObject_->begin(), end = pObject_->end(); it != end; ++it) {
            
            if (it->second.type() == typeid(std::string))
            {
                
                std::cout << "Value is string(ExtractMap)" << std::endl;
                std::cout << "Key : " << it->first << std::endl;
                std::cout << "Value : " << it->second.toString() << std::endl;
                std::cout << "" << std::endl;
            }
            else if (it->second.type() == typeid(long))
            {
                
                std::cout << "Value is long(ExtractMap)" << std::endl;
                std::cout << "Key : " << it->first << std::endl;
                std::cout << "Value : " << it->second.toString() << std::endl;
                std::cout << "" << std::endl;
            }
            else if(it->second.type() == typeid(Poco::JSON::Object::Ptr))
            {
                std::cout << "Value is Object::Ptr(ExtractMap)" << std::endl;
                std::cout << "Key : " << it->first << std::endl;
                std::cout << "Value : " << std::endl;
                std::cout << "====================================" << std::endl;
                Poco::JSON::Object::Ptr NestObject = it->second.extract<Poco::JSON::Object::Ptr>();
                result = ExtractMap(NestObject, it->first);
                std::cout << "====================================" << std::endl;
                std::cout << "" << std::endl;
                
            }
            else if(it->second.type() == typeid(Poco::JSON::Array::Ptr))
            {
                std::cout << "Value is Array::Ptr(ExtractMap)" << std::endl;
                std::cout << "Key : " << it->first << std::endl;
                std::cout << "Value : " << std::endl;
                std::cout << "====================================" << std::endl;
                Poco::JSON::Array::Ptr NestArray = it->second.extract<Poco::JSON::Array::Ptr>();
                result = ExtractArray(NestArray, it->first);
                std::cout << "====================================" << std::endl;
                std::cout << "" << std::endl;
            }
        }
        
        std::cout << "====================================" << std::endl;
        if(pKey != "")
        {
            std::cout << "-----------------------------------" << std::endl;
        }
        return result;
    }

    int ExtractArray(Poco::JSON::Array::Ptr pArray_, std::string pKey = "") {
        int result = 0;
        if(pKey != "")
        {
            std::cout << "親のKeyは : " << pKey << std::endl;
            
        }
        std::cout << "" << std::endl;
        std::cout << "this is ExtractArray" << std::endl;
        std::cout << "====================================" << std::endl;
        int checker = 0;
        
        for(Poco::JSON::Array::ConstIterator it = pArray_->begin(), end = pArray_->end(); it !=end; ++it) {
            
            if (it->type() == typeid(std::string))
            {
                std::cout << "Value is string(Nested_ExtractArray)" << std::endl;
                std::cout << "Key : " << checker << std::endl;
                std::cout << "Value : " << it->toString() << std::endl;
                std::cout << "" << std::endl;
        
            }
            else if (it->type() == typeid(long))
            {
                
                std::cout << "Value is long(Nested_ExtractMap)" << std::endl;
                std::cout << "Key : " << checker << std::endl;
                std::cout << "Value : " << it->toString() << std::endl;
                std::cout << "" << std::endl;
            }
            else if(it->type() == typeid(Poco::JSON::Object::Ptr))
            {
                std::cout << "Value is Object::Ptr(Nested_ExtractArray)" << std::endl;
                std::cout << "Key : " << checker << std::endl;
                std::cout << "Value : "<< std::endl;
                std::cout << "====================================" << std::endl;
                Poco::JSON::Object::Ptr NestObject = it->extract<Poco::JSON::Object::Ptr>();
                result = ExtractMap(NestObject, std::to_string(checker));
                std::cout << "====================================" << std::endl;
                std::cout << "" << std::endl;
                
            }
            else if(it->type() == typeid(Poco::JSON::Array::Ptr))
            {
                std::cout << "Value is Array::Ptr(Nested_ExtractArray)" << std::endl;
                std::cout << "Key : " << checker << std::endl;
                std::cout << "Value : " << std::endl;
                std::cout << "====================================" << std::endl;
                Poco::JSON::Array::Ptr NestArray = it->extract<Poco::JSON::Array::Ptr>();
                result = ExtractArray(NestArray, std::to_string(checker));
                std::cout << "====================================" << std::endl;
                std::cout << "" << std::endl;
            }
            
            checker++;
            
        }
    
        std::cout << "====================================" << std::endl;
        if(pKey != "")
        {
            std::cout << "-----------------------------------" << std::endl;
        }
        return result;
    }

};

int main(int argc, char** argv)
{
    
    std::string dir = "/Users/bko117/Desktop/Git/CPP/Poco_Json_Convert/JSON_Dir/";
//    Poco::Path filePath(dir, "input.json");
    Poco::Path filePath(dir, "nestMap.json");
    
    std::ostringstream ostr;
    
    if (filePath.isFile())
    {
        Poco::File inputFile(filePath);
        if ( inputFile.exists() )
        {
            Poco::FileInputStream fis(filePath.toString());
            Poco::StreamCopier::copyStream(fis, ostr);
        }
        else
        {
            std::cout << filePath.toString() << " doesn't exist!" << std::endl;
            return 1;
        }
    }
    
    std::string jsonData = ostr.str();
    
    Poco::JSON::Parser parser;
    
    Poco::Dynamic::Var result = parser.parse(jsonData);
    
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
    
    CExtractMap abc;
    
    abc.ExtractMap(object);
    
    return 0;
}
