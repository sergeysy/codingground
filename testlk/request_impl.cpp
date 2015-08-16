//
//  request_impl.cpp
//  TestLK
//
//  Created by inkooboo on 3/14/13.
//  Copyright (c) 2013 inkooboo. All rights reserved.
//

#include "request_api.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <atomic>

std::atomic<int> g_created(0);
std::atomic<int> g_processed(0);

Request * GetRequest(Stopper stopSignal) __NO_THROW
{
    Request *ret = NULL;
    try
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
        if (!stopSignal.is_set())
        {
            ret = new Request;

            g_created.fetch_add(1);
        }
    }
    catch (...)
    {
    }
    

    return ret;
}

void ProcessRequest(Request *request, Stopper stopSignal) __NO_THROW
{
    try
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        if (stopSignal.is_set())
        {
            return;
        }
    
        g_processed.fetch_add(1);
    }
    catch (...)
    {
    }
}
