#import <Foundation/Foundation.h>

// Include SwinGame
#include "SwinGame.h"

// Include Research Information
#include "ProjectInfo.h"

// Import Model
#import "CMGame.h"

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
void setup_network(CMGame **gameModel)
{
    // Ask for hosting
    NSLog(@"Are you hosting? [y/n]");
    
    // Check if hosting
    char input[32];
    scanf("%s", input);

    // If Client
    if (input[0] == 'n')
    {
        // Ask for IP
        NSLog(@"Enter Host IP: ");

        // Read in IP
        scanf("%s", input);
        
        // Initate Model (as Client)
        *gameModel   = [[CMGame alloc] initAsClientMouseConnectingTo:
                        [NSString stringWithFormat:@"%s", input]];
    }
    // If Host (blank IP)
    else
    {
        // Initate Model (as host)
        *gameModel   = [[CMGame alloc] initAsHostCat];
    }
}

/**
 * @brief   The main entry point to the program
 */
int main()
{
    @autoreleasepool
    
    {        

        // Announce Hello Message
        NSLog(@"Welcome to %@", @PROJECT_DESC);
        
        // Decalre game model
        CMGame *gameModel = nil;
        
        /*
          Network needed to construct the gameModel;
          we pass it in by reference here to do just
          that
        */
        setup_network(&gameModel);
        
        // Process game loop while not window closed
        while ( (![SGInput windowCloseRequested]) )
        {
            
            [gameModel processGame];
            
            // Only process network where still connected
            if ( !gameModel.isValid ) break;
        
        }
        
        // Delete the model
        [gameModel dealloc];
        
        return 0;
    }
    
}