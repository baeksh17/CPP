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
#include "Poco/Environment.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Stopwatch.h"
#include <iostream>
#include <iomanip>

int ExtractMap(Poco::JSON::Object::Ptr pObject_) {
    
    int result = 0;
    
    for(Poco::JSON::Object::ConstIterator it = pObject_->begin(), end = pObject_->end(); it != end; ++it) {
        
        if (it->second.type() == typeid(std::string))
        {
//            std::cout << "Value is string" << std::endl;
//            std::cout << "Key : " << it->first << std::endl;
//            std::cout << "Value.typeid : " << it->second.type().name() << std::endl;
            
            std::map<std::string, std::string> stringMap;
            
            stringMap.insert(std::make_pair(it->first, it->second.toString()));
            
            std::cout << "stringMap key : " << it->first << std::endl;
            std::cout << "stringMap value : " << stringMap[it->first] << std::endl;
        }
        else if(it->second.type() == typeid(Poco::JSON::Object::Ptr))
        {
            std::cout << "Value is Object::Ptr" << std::endl;
            std::cout << "Key : " << it->first << std::endl;
//            std::cout << "Value.typeid : " << it->second.type().name() << std::endl;
        }
        else if(it->second.type() == typeid(Poco::JSON::Array::Ptr))
        {
            std::cout << "Value is Array::Ptr" << std::endl;
            std::cout << "Key : " << it->first << std::endl;
//            std::cout << "Value.typeid : " << it->second.type().name() << std::endl;
            
            ExtractArray(it->second);
            
        }
    }
    return result;
}

int ExtractArray(Poco::JSON::Array::Ptr pArray_) {
    
    for(Poco::JSON::Array::ConstIterator it = pArray_->begin(), end = pArray_->end(); it !=end; ++it) {
        
        std::cout << "Nest Array key : " << it-> << std::endl;
        
    }
    
}

int main(int argc, char** argv)
{
//    Poco::Stopwatch sw;
    
    std::string dir = "/Users/bko117/Desktop/Git/CPP/Poco_Json_Convert/JSON_Dir/";
    Poco::Path filePath(dir, "input.json");
    
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
    
//    std::cout << jsonData << std::endl;
    
    Poco::JSON::Parser parser;
    
    Poco::Dynamic::Var result = parser.parse(jsonData);
    
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
    
    ExtractMap(object);
    
    return 0;
}
