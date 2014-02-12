/**
 * @class   Network View
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   Packages up data recieved from the controller
 *          and passes it to a given network.
 */

#ifndef __CatMouse__Network__
#define __CatMouse__Network__

// Include SwinGame
#include "SwinGame.h"

// Includes and std namespace
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

// Include Interfaces Used
#include "EventProcessor.h"
#include "EventAnnouncer.h"

class Network : public EventProcessor, public EventAnnouncer
{
    
public:
    
    // Redefine overriden EventProcessor method
    virtual void process_event(Event *eData);
    
    // Declare constructor/destructor
    // Overriden Network Constructor
    // - string arg will create a connection as client to host
    // - no args will create a connection as a host
    Network ();
    Network (string ipAddr);
    ~Network();
    
    // Declare public methods
    void    process_messages();
    
    //! Delcare is connected property
    //! @return Boolean whether or not the network is connected
    bool    is_connected() { if (_ctn != nullptr) { return true; } else return false; }
    
private:
    // Declare private fields
    //! Network connection controller between client and host
    connection _ctn;
    
    // Declare private methods
    connection  new_connection();
    connection  new_connection(string ipAddr);
    
    // Timeout method explained in implementation
    void    timeout                     (string msgPrompt,
                                         string msgSucc,
                                         string msgFail,
                                         int timeoutSecs,
                                         function<void(void)> countdownBody,
                                         function<bool(void)> breakCondition);

    // Redefine overriden EventAnnouncer method
    virtual void announce_event(string msg);
    
    //! Defines a unique address of this machine
    string _networkID;
    
};

#endif /* defined(__CatMouse__Network__) */
