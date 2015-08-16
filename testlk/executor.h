//
//  executor.h
//  TestLK
//
//  Created by inkooboo on 3/14/13.
//  Copyright (c) 2013 inkooboo. All rights reserved.
//

#ifndef TestLK_thread_pool_h
#  define TestLK_thread_pool_h

#  include "request_api.h"
#  include "noncopyable.hpp"

#  include "mpmc_bounded_lf_queue.h"

#  include <vector>
#  include <thread>
#  include <list>
#  include <mutex>
#  include <condition_variable>

class executor_t : private noncopyable_t
{
public:
    executor_t(size_t threads_count, size_t queue_size);
    ~executor_t();
    
    bool post(Request *request, Stopper stopper);

private:
    struct task_t
    {
        std::shared_ptr<Request> request;
        Stopper stopper;
    };
    
    void thread_func();

    mpmc_bounded_queue<task_t> m_queue;

    std::condition_variable m_cond_var;
    std::mutex m_cond_var_mutex;

    std::vector<std::thread> m_pool;
    
    bool m_stop_flag;
};

#endif
