/**
 * @class   Log View
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   CLI view to game
 */

// Include my class header
#include "Log.h"

// Include headers of classes used
#include "Event.h"

/**
 * @brief   Processes a data depending 
 *          on the data passed by printing each
 *          key/value pair in the event data's
 *          map, priting lines to cout
 * @param   eData
 *          Event Data to process
 */
void Log::process_event(Event *eData)
{
    map<string, string> eventData = eData->get_data();
    
    cout << "*** EVENT OCCURED ***" << endl << "{" << endl;
    
    // Print every key/value pair in the event data map
    for (auto i = eventData.begin(); i != eventData.end(); ++i)
    { cout << "    " << i->first << ": " << i->second << endl; }
    
    cout << "}" << endl;

}