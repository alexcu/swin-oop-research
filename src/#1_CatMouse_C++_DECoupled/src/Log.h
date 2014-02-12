/**
 * @class   Log View
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   CLI view to game
 */

#ifndef __CatMouse__Log__
#define __CatMouse__Log__

// Includes and std namespace
#include <iostream>
#include <sstream>
using namespace std;

// Include Interface
#include "EventProcessor.h"

class Log : public EventProcessor
{
    
public:
    
    // Redefine overriden EventProcessor method
    virtual void process_event(Event *eData);

};

#endif /* defined(__CatMouse__Log__) */