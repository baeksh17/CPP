//
//  main.cpp
//  Poco_Uri_Edit
//
//  Created by 白昔虎 on 2018/01/20.
//  Copyright © 2018年 BAEK SEOKHO. All rights reserved.
//

#include <iostream>
#include <map>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::map<std::string, std::string> uriMap;
    uriMap.insert(std::make_pair("id", "1"));
    uriMap.insert(std::make_pair("jsonrpc", "2.0"));
    uriMap.insert(std::make_pair("total", "10"));
    uriMap.insert(std::make_pair("limit", "1"));
    uriMap.insert(std::make_pair("expand", "2"));
    uriMap.insert(std::make_pair("fields", "text"));
    uriMap.insert(std::make_pair("sortby", "name"));
    
//    for(std::map::iterator it = uriMap.begin(), end = uriMap.end(); it != end; ++it) {
//
//    }
    
    
    
    
    return 0;
}
