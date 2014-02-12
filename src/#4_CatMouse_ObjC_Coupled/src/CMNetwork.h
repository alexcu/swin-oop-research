/**
 * @class   CMNetwork
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Packages up data recieved from the controller
 *          and passes it to a given network.
 */

#import <Foundation/Foundation.h>

// Include SwinGame
#include "SwinGame.h"

// Forward delcare referenced classes
@class CMGame;

@interface CMNetwork : NSObject
{
    // Declare ivars
    //! Network connection controller between client and host
    SGConnection *_ctn;
    //! Defines a unique address of this machine
    NSString     *_networkID;
    //! Defines the coupling between game and network
    CMGame       *_gameModel;
}

@property (readonly) BOOL isConnected;

// Declare constructors
-(id) initAsHostInGame:(CMGame*)gameModel;
-(id) initAsClientWithIPAddress:(NSString*) ipAddr inGame:(CMGame*)gameModel;

// Declare methods
-(void) processMessages;
-(void) sendMessageWithString:(NSString*) msg;


@end
