/**
 * @interface   EventProcessor
 * @author      Alex Cummaudo
 * @date        7 Oct 2013
 * @brief       An pure abstract class that defines
 *              all the methods that each processor
 *              of events must implement
 * @note        Inherits as virtual so that any users of BOTH
 *              EventProcessors and EventSubscribers will
 *              avoid diamond inheritance issues.
 */

#ifndef CatMouse_EventProcessor_h
#define CatMouse_EventProcessor_h

// Include parent interface
#include "EventSubscriber.h"

// Forward declare classes reference
class Event;

class EventProcessor : virtual public EventSubscriber
{
public:
    
    /**
     * @brief   Defines that whoever uses this interface
     *          must process an event in anyway with the
     *          given Event
     * @param   eData
     *          Event Data to process
     */
    virtual void    process_event(Event *eData) = 0;
    
};

#endif
