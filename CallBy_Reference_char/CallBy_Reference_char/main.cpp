//
//  main.cpp
//  CallBy_Reference_char
//
//  Created by 白昔虎 on 2018/01/27.
//  Copyright © 2018年 BAEK SEOKHO. All rights reserved.
//

#include <iostream>

using GetInt;

void GetChar(char** charOutput)
{
    std::string line="hello world";
    
    GetInt();
}

void GetInt();


int main(int argc, const char * argv[]) {
    // insert code here...
    
    char * data = new char[line.size() + 1];
    copy(line.begin(), line.end(), data);
    data[line.size()] = '\0';
    return 0;
}
