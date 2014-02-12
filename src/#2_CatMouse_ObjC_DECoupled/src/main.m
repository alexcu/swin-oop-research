#import <Foundation/Foundation.h>

// Include Research Information
#include "ProjectInfo.h"

// Import Model
#import "CMGame.h"

// Import Views
#import "CMLog.h"
#import "CMKeyboard.h"
#import "CMGUI.h"
#import "CMNetwork.h"

// Import Controllers
#import "CMEventManager.h"
#import "CMEvent.h"

/**
 * @brief   Allows simple welcome messages to printed
 *          printed to the console and over network
 * @param   message
 *          Textual string to announce.
 */
void announce_message(NSString* message)
{
    CMEvent *event = [[CMEvent alloc] initWithData:@{@"Message": message,
                                                     @"Source" : @"Main"}];
    [CMEventManager publishEvent:event];
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
void setup_network(CMNetwork **networkView, CMGame **gameModel)
{
    // Ask for hosting
    announce_message(@"Are you hosting? [y/n]");
    
    // Check if hosting
    char input[32];
    scanf("%s", input);

    // If Client
    if (input[0] == 'n')
    {
        // Ask for IP
        announce_message(@"Enter Host IP");

        // Read in IP
        scanf("%s", input);
        *networkView = [[CMNetwork alloc] initAsClientWithIPAddress:
                        [NSString stringWithFormat:@"%s", input]];
        *gameModel   = [[CMGame alloc] initControllingCat:NO];
    }
    // If Host (blank IP)
    else
    {
        // Initate Model and View (as host)
        *networkView = [[CMNetwork alloc] initAsHost];
        *gameModel   = [[CMGame alloc] initControllingCat:YES];
    }
}

/**
 * @brief   The main entry point to the program
 */
int main()
{
    @autoreleasepool
    
    {        
        // Construct visual log and GUI, and input Keyboard views
        CMLog *logView = [[CMLog alloc] init];
        CMGUI *guiView = [[CMGUI alloc] initWithRefreshRate:0.5];
        CMKeyboard *keyView = [[CMKeyboard alloc] init];
        
        // Announce Hello Message
        announce_message([NSString stringWithFormat:@"Welcome to %@", @PROJECT_DESC]);
        
        // Declare Model
        CMGame *gameModel = nil;
        // Network is required to create type of Model
        CMNetwork *networkView = nil;
        
        /*
         Network determines host/client, which determines
         who is cat/mouse. Both gameModel and networkView
         get their own setup network function.
         Setup the network connection and game together
         by passing in the network view and game model
         by reference
         */
        setup_network(&networkView, &gameModel);
        
        // Process game loop while not window closed
        while ( (![SGInput windowCloseRequested]) )
        {
            
            [keyView     processKeyboard];
            [guiView     processScreen  ];
            
            // Only process network where still connected
            if ( ![networkView isConnected] ) break;
            [networkView processMessages];
            
        }
        
        // Delete all views and model
        [guiView dealloc];
        [keyView dealloc];
        [networkView dealloc];
        [gameModel dealloc];
        
        // Log view is last to go
        [logView dealloc];
        
        return 0;
    }
    
}