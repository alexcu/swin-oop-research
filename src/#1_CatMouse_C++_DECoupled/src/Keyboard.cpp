/**
 * @class   Keyboard View
 * @author  Alex Cummaudo
 * @date    19 Oct 2013
 * @brief   Defines class to capture keyboard
 *          events and pass them to the processor
 */

#include "Keyboard.h"

// Include referenced classes
#include "EventManager.h"
#include "Event.h"

/**
 * @brief   Captures keydown events and processes
 *          them by passing them to the EventManager
 */
void Keyboard::process_keyboard()
{
    process_events();
    if (key_down(VK_UP)   ) { this->announce_event("up_key"   ); }
    if (key_down(VK_DOWN) ) { this->announce_event("down_key" ); }
    if (key_down(VK_LEFT) ) { this->announce_event("left_key" ); }
    if (key_down(VK_RIGHT)) { this->announce_event("right_key"); }
}

/**
 * @brief   Sends an event to all subscribers with the given key
 * @param   msg
 *          Message to announce when creating an Event
 */
void Keyboard::announce_event(string key)
{
    map<string, string> eventData;
    
    // Push to eventData to say this event originated from the keyboard view
    eventData["KeyDown"] = key;
    eventData["Source"] = "Keyboard";
    
    // Push an event out with this information
    Event* result = new Event(eventData);
    
    // Notify subscribers of the new result
    EventManager::publish_event(result);
    
    delete result;
}