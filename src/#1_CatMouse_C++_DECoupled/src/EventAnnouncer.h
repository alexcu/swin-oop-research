/**
 * @interface   EventAnnouncer
 * @author      Alex Cummaudo
 * @date        7 Oct 2013
 * @brief       An pure abstract class that defines
 *              all the methods that each announcer
 *              of events must implement
 * @note        Inherits as virtual so that any users of BOTH
 *              EventProcessors and EventSubscribers will
 *              avoid diamond inheritance issues.
 */

#ifndef CatMouse_EventAnnouncer_h
#define CatMouse_EventAnnouncer_h

// Include parent interface
#include "EventSubscriber.h"

// Forward declare classes reference
class event;

class EventAnnouncer : virtual public EventSubscriber
{
private:

    /**
     * @brief   Defines that whoever uses this interface
     *          must announce events with given a message
     *          to the EventManager
     * @param   msg
     *          Message to announce when creating an Event
     */
    virtual void    announce_event(string msg) = 0;
};

#endif
