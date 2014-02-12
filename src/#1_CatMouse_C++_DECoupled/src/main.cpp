#include <stdio.h>

// Include Research Information
#include "ProjectInfo.h"

// Import Model
#include "Game.h"

// Import Views
#include "GUI.h"
#include "Log.h"
#include "Network.h"
#include "Keyboard.h"

// Import Controller
#include "EventManager.h"
#include "Event.h"

/**
 * @brief   Allows simple welcome messages to be
 *          printed to the console and over network
 * @param   msg
 *          Textual string to announce.
 */
void announce_message(string msg)
{
    map<string, string> data;
    data["Message"] = msg;
    data["Source"] = "Main";
    Event *event = new Event(data);
    EventManager::publish_event(event);
    delete event;
}

/**
 * @brief   Sets up the network by asking the user
 *          whether they are hosting or connecting
 *          to the host--networkView and gameModel
 *          are passed in by pointer reference to
 *          their allocated memory on the heap so
 *          that they can be constructed in this
 *          function for better functional decomp.
 * @param   networkView
 *          Reference to the network view created
 *          in main
 * @param   gameModel
 *          Reference to the game model created in
 *          main
 */
void setup_network(Network **networkView, Game **gameModel)
{
    // Ask for hosting
    announce_message("Are you hosting? [y/n]");
    
    // Check if hosting
    string input;
    getline(cin, input);

    // If Client
    if (input == "n")
    {
        // Ask for IP
        announce_message("Enter Host IP");
        
        // Get IP Addr to connect to host
        string ipAddr;
        getline(cin, ipAddr);
        // Initate Model and View (as client)
        *networkView = new Network(ipAddr);
        *gameModel = new Game(false);
    }
    // If Host (blank IP)
    else
    {
        // Initate Model and View (as host)
        *networkView = new Network();
        *gameModel = new Game(true);
    }
    
}

/**
 * @brief   The main entry point to the program
 */
int main()
{   
    // Construct the EventManager Controller
    EventManager::EventManager();
    
    // Construct visual log and GUI, and input Keyboard views
    Log *logView = new Log();
    GUI *guiView = new GUI(0.5);
    Keyboard *keyView = new Keyboard();
    
    // Announce Hello Message
    stringstream hello;
    hello << "Welcome to " << PROJECT_DESC;
    announce_message(hello.str());
    
    // Decalre game model
    Game *gameModel = nullptr;
    // Network is required to create type of Model
    Network *networkView = nullptr;
    
    /*
        Network determines host/client, which determines
        who is cat/mouse. Both gameModel and networkView
        get their own setup network function.
        Setup the network connection and game together
        by passing in the network view and game model
        by reference
     */
    setup_network(&networkView, &gameModel);

    // If there was a timeout (i..e networkView did not connect?)
    if (! networkView->is_connected()) { return 0; }
    
    // Process game loop while not window closed
    do
    {
        keyView    ->process_keyboard();
        guiView    ->process_screen();
        
        // Only process network where still connected
        if ( !networkView->is_connected() ) break;
        networkView->process_messages();
    }
    while ( ! window_close_requested() );
    
    // Relinquish all views and model
    delete guiView;
    delete keyView;
    delete networkView;
    delete gameModel;
    
    // Log is the last to go
    delete logView;
    
    return 0;
}
