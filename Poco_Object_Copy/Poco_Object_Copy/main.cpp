//
//  main.cpp
//  Poco_Object_Copy
//
//  Created by 白昔虎 on 2018/01/27.
//  Copyright © 2018年 BAEK SEOKHO. All rights reserved.
//
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include <iostream>


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
    
    Poco::JSON::Object* object = new Poco::JSON::Object;
    
    object->set("key","value");
    
//    object = result.extract<Poco::JSON::Object::Ptr>();
    
    for(Poco::JSON::Object::ConstIterator it = object->begin(), end = object->end(); it != end; it++)
    {
        std::cout << it->first << std::endl;
        break;
    }
    
    
    delete object;
    
    
    Poco::JSON::Object::Ptr object2(object);
    
    for(Poco::JSON::Object::ConstIterator it = object2->begin(), end = object2->end(); it != end; it++)
    {
        std::cout << it->first << std::endl;
        break;
    }
    
    return 0;
}
