/**
 * @class   EventManager
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   Defines EventManager class which
 *          processes each event to each kind of
 *          EventProcessor. 
 * @note    This is a static member class; so that 
 *          clients do not need to make an instance 
 *          of an EventManager (since there's only ever
 *          going to be one processor). Therefore 
 *          we invoke EventManager by calling directly 
 *          on the class 
 *          (i.e. EventManager::notify_subscribers(event))
 */

#ifndef __CatMouse__EventManager__
#define __CatMouse__EventManager__

// Includes and std namespace
#include <iostream>
#include <vector>
using namespace std;

// Forward declare references to classes
class EventSubscriber;
class Event;

class EventManager
{
public:
    EventManager();
    
    static void publish_event(Event *eData);
    static void add_subscriber(EventSubscriber *sub);
    static void forget_subscriber(EventSubscriber *sub);
    
private:
    
    //! Declare subscribers (who process or announce events) vector
    static vector<EventSubscriber*> *_subs;
    
};

#endif /* defined(__CatMouse__EventManager__) */
