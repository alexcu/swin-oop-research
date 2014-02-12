/**
 * @class   Keyboard View
 * @author  Alex Cummaudo
 * @date    19 Oct 2013
 * @brief   Defines class to capture keyboard
 *          events and pass them to the processor
 */

#ifndef __CatMouse__Keyboard__
#define __CatMouse__Keyboard__

// Include SwinGame
#include "SwinGame.h"

// Includes and std namespace
#include <iostream>
#include <map>
using namespace std;

// Include referenced classes
#include "EventAnnouncer.h"

// Forward declare Event
class Event;

class Keyboard : public EventAnnouncer
{
public:
    
    // Processer
    void process_keyboard();
    
private:

    // Redefine overriden EventAnnouncer method
    virtual void announce_event(string key);
    
};


#endif /* defined(__CatMouse__Keyboard__) */
