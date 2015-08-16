//
//  main.cpp
//  TestLK
//
//  Created by inkooboo on 3/14/13.
//  Copyright (c) 2013 inkooboo. All rights reserved.
//

#include <iostream>

#include "request_api.h"
#include "executor.h"

#include <ctime>
#include <thread>
#include <atomic>

extern std::atomic<int> g_created;
extern std::atomic<int> g_processed;

const static int EXECUTION_TIME = 30;

int main(int argc, const char * argv[])
{
    unsigned int n_threads = std::thread::hardware_concurrency() + 2;

    std::cout << "use " << n_threads << " threads" << std::endl;

    executor_t executor(n_threads, 1024*1024);
    
    Stopper stopper;
    
    time_t start_time = time(0);
    while (true)
    {
        Request *request = GetRequest(stopper);
        
        if (!executor.post(request, stopper))
        {
            std::cout << "ERROR: executor queue is overflowed, abort request " << request << std::endl;
        }
        
        if ( (time(0) - start_time) >= EXECUTION_TIME)
        {
            break;
        }
    }
    
    stopper.set();

    std::cout << "total created: " << g_created.load() << " total processed: " << g_processed.load() << std::endl;

    return 0;
}
