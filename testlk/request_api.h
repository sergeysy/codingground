//
//  request_api.h
//  TestLK
//
//  Created by inkooboo on 3/14/13.
//  Copyright (c) 2013 inkooboo. All rights reserved.
//

#ifndef TestLK_request_api_h
#  define TestLK_request_api_h

#  ifndef __NO_THROW
#    define __NO_THROW throw()
#  endif // __NO_THROW

#  include "stopper.h"

class Request
{
};

Request* GetRequest(Stopper stopSignal) __NO_THROW;
void ProcessRequest(Request* request, Stopper stopSignal) __NO_THROW;

#endif
