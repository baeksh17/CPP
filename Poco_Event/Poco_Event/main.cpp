//
//  main.cpp
//  Poco_Event
//
//  Created by 白昔虎 on 2018/01/28.
//  Copyright © 2018年 BAEK SEOKHO. All rights reserved.
//

#include <iostream>
#include <thread>
#include <unistd.h>
#include "Poco/Event.h"

void Thread1(Poco::Event* event)
{
    
    std::cout << "Thread1_start\n";
    std::cout << "Thread1_event_wait\n";
    event->wait();
    std::cout << "Thread1_event_set\n";
    std::cout << "Thread1_end\n";
    
}


void Thread2(Poco::Event* event)
{
    std::cout << "Thread2_start\n";
    std::cout << "Thread2_sleep\n";
    
    for(int i = 0; 10 > i; i++)
    {
        std::cout << "sleep : " << i << std::endl;
        sleep(1);
    }
    event->set();
    std::cout << "Thread2_event_set\n";
    std::cout << "Thread2_end\n";
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Poco::Event* event = new Poco::Event;
    
    std::thread t1(Thread1, event);
    
    std::thread t2(Thread2, event);
    
    t1.join();
    t2.join();
    
    
    return 0;
}
