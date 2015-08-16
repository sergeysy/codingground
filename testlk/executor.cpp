//
//  executor.cpp
//  TestLK
//
//  Created by inkooboo on 3/14/13.
//  Copyright (c) 2013 inkooboo. All rights reserved.
//

#include "executor.h"

#include <iostream>
#include <stdexcept>

executor_t::executor_t(size_t threads_count, size_t queue_size)
    : m_queue(queue_size)
    , m_pool(threads_count)
    , m_stop_flag(false)
{
    // create threads in pool
    for (auto &thr : m_pool)
    {
        thr = std::thread(&executor_t::thread_func, this);
    }
}

executor_t::~executor_t()
{
    try 
    {
        m_stop_flag = true;
    
        m_cond_var.notify_all();
    
        for (auto &thr : m_pool)
        {
            if (thr.joinable())
            {
                thr.join();
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << "ERROR: error while destructing executor_t: " << ex.what() << std::endl;
    }
}

bool executor_t::post(Request *request, Stopper stopper)
{
    task_t task = {std::shared_ptr<Request>(request), stopper};

    bool posted = m_queue.enqueue(task);

    if (posted)
    {
        m_cond_var.notify_one();
    }
    
    return posted;
}

void executor_t::thread_func()
{
    while (true)
    try {
        task_t task;
        bool have_task = m_queue.dequeue(task);

        if (!have_task)
        {
            std::unique_lock<std::mutex> lock(m_cond_var_mutex);
            while (true)
            {
                if (std::cv_status::timeout != m_cond_var.wait_for(lock, std::chrono::seconds(1)))
                {
                    break;
                }
                
                if (m_stop_flag)
                {
                    return;
                }
            }

            have_task = m_queue.dequeue(task);
        }

        if (have_task)
        {
            ProcessRequest(task.request.get(), task.stopper);
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << "ERROR: error in executor_t::thread_func(): " << ex.what() << std::endl;
    }
}
        
        
