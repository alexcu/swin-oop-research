/**
 * @class   Event
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   Defines event class of what to pass a
 *          view, thereby allowing a link between
 *          each view and each model.
 */

#include "Event.h"

/**
 * @brief   Constructor for new event object to 
 *          initialise fields
 * @param   data
 *          Textual data to insert as data to this
 *          event
 */
Event::Event(map<string, string> data)
{
    _data = data;
}