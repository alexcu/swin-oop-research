/**
 * @class   Network View
 * @author  Alex Cummaudo
 * @date    2 Nov 2013
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

// Forward declare classes referenced
class Game;

class Network
{
    
public:
    
    // Declare constructor/destructor
    // Overriden Network Constructor
    // - string arg will create a connection as client to host
    // - no args will create a connection as a host
    Network (Game *gameModel);
    Network (Game *gameModel, string ipAddr);
    ~Network();

    // Declare public methods
    void    process_messages();
    
    //! Delcare is connected property
    //! @return Boolean whether or not the network is connected
    bool    is_connected() { if (_ctn != nullptr) { return true; } else return false; }
    
    // Send message method
    void    send_message(string msg);
    
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
    
    //! Defines a unique address of this machine
    string _networkID;
    
    //! Defines the coupling between game and network
    Game   *_gameModel;
    
};

#endif /* defined(__CatMouse__Network__) */
