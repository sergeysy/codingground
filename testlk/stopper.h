//
//  stopper.h
//  TestLK
//
//  Created by inkooboo on 3/14/13.
//  Copyright (c) 2013 inkooboo. All rights reserved.
//

#ifndef TestLK_stopper_h
#  define TestLK_stopper_h

#  include <memory>

class Stopper
{
public:
    Stopper() : m_signal(false)
    {
    }

    void set()
    {
        m_signal = true;
    }
    
    bool is_set() const
    {
        return m_signal;
    }

private:
    bool m_signal;
};

#endif
