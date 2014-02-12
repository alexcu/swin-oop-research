#include <stdio.h>

// Include Research Information
#include "ProjectInfo.h"

// Import Model
#include "Game.h"

/**
 * @brief   Sets up the network by asking the user
 *          whether they are hosting or connecting
 *          to the host--gameModel is passed in by
 *          reference so that it can initialise its
 *          self contained networkView. Done as a
 *          function for better functional decomp.
 * @param   gameModel
 *          Reference to the game model created in
 *          main
 */
void setup_network(Game **gameModel)
{
    // Ask for hosting
    cout << "Are you hosting? [y/n] ";
    
    // Check if hosting
    string input;
    getline(cin, input);
    
    // If Client
    if (input == "n")
    {
        // Ask for IP
        cout << "Enter Host IP: ";
        
        // Get IP Addr to connect to host
        string ipAddr;
        getline(cin, ipAddr);
        
        // Initate Model (as Client)
        *gameModel = new Game(ipAddr);
        
    }
    // If Host (blank IP)
    else
    {
        // Initate Model (as Host)
        *gameModel = new Game();
    }
    
}

/**
 * @brief   The main entry point to the program
 */
int main()
{
    
    // Announce Hello Message
    cout << "Welcome to " << PROJECT_DESC << endl;

    
    // Decalre game model
    Game *gameModel = nullptr;
    
    /*
        Network needed to construct the gameModel;
        we pass it in by reference here to do just 
        that
     */
   setup_network(&gameModel);

    // If game is still no longer valid (connected) after this stage)---then kill program
    if (! gameModel->is_valid()) { return 0; }
    
    // Process game loop while not window closed
    do
    {
        gameModel->process_game();
        
        // If suddenly no longer valid, then break
        if (! gameModel->is_valid()) { break; }
    }
    while ( ! window_close_requested() );
    
    // Relinquish the model
    delete gameModel;
    
    return 0;
}
