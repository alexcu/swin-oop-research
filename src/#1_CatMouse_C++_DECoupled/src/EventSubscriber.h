/**
 * @interface   EventSubscriber
 * @author      Alex Cummaudo
 * @date        7 Oct 2013
 * @brief       Acts as a parent to subscribers
 *              and announcers so that the Event
 *              manager knows what to manager
 *              (i.e. both Announcers and Processors,
 *              and this allows this relationship
 *              to occur via inheritance)
 */

#ifndef CatMouse_EventSubscriber_h
#define CatMouse_EventSubscriber_h

// Include referenced classes
#include "EventManager.h"

// No actual definition; this interfaceA is empty
// and exists only to relate Announcers and Processors
class EventSubscriber
{
public:
    
    /**
     * @brief   To dynamically add event subscribers to the
     *          EventManager on creation, the EventSubscriber
     *          constructor does this for us
     */
    EventSubscriber() { EventManager::add_subscriber(this); };
    
    /**
     * @brief   To make EventSubscriber polymorphic, make a virtual
     *          destructor---this will allow for dynamic casting in
     *          the EventManager. On invocation, the EventManager
     *          will forget about this subscriber.
     */
    virtual ~EventSubscriber() { EventManager::forget_subscriber(this); };
};

#endif
