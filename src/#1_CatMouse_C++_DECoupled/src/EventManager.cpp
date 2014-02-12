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

// Include my parent class
#include "EventManager.h"

// Include used references
#include "EventProcessor.h"

// Include access to Event Pro's _subs
vector<EventSubscriber*> *EventManager::_subs;

/**
 * @brief   Constructor initialises _subs vector
 */
EventManager::EventManager()
{
    _subs = new vector<EventSubscriber*>;
}

/**
 * @brief   Adds a subscriber to the _subs vector
 * @param   sub
 *          Subscriber to manage
 */
void EventManager::add_subscriber(EventSubscriber *sub)
{
    _subs->push_back(sub);
}

/**
 * @brief   Removes a subscriber to the _subs vector
 * @param   sub
 *          Subscriber to forget
 */
void EventManager::forget_subscriber(EventSubscriber *sub)
{
    _subs->erase(remove(_subs->begin(), _subs->end(), sub));
}

/**
 * @brief   Processes the event for each kind
 *          subscriber who publishes events
 *          (i.e. EventProcessors ONLY!)
 * @param   eData
 *          Event to publish to all EventProcessors
 */
void EventManager::publish_event(Event *eData)
{
    // For each subscriber
    for_each(_subs->begin(),
             _subs->end(),
             // Process a processors event
             [&eData](EventSubscriber* subscriber)
             {
                 
                 // Dynamically cast a processor at runtime so that
                 // we have access to the process_event method;
                 // where this fails, we do not process the event (i.e.
                 // where a subscriber is just an EventAnnouncer)
                 EventProcessor *processor =
                        dynamic_cast<EventProcessor*>(subscriber);
                 
                 if (processor != nullptr)
                 {
                     processor->process_event(eData);
                 }
                 
             });
}