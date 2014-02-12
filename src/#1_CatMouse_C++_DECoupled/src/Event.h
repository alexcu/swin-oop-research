/**
 * @class   Event
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   Defines event class of what to pass a
 *          view, thereby allowing a link between
 *          each view and each model.
 */

#ifndef __CatMouse__Event__
#define __CatMouse__Event__

// Includes and std namespace
#include <iostream>
#include <map>
using namespace std;

class Event
{
public:

    // Define constructor
    Event(map<string, string> data);
    
    //! Readonly property to data
    map<string, string> const get_data() { return _data; }

private:
   
    // Private fields
    map<string, string>     _data;  //!< Textual data contained within the Event
    
};

#endif /* defined(__CatMouse__Event__) */
