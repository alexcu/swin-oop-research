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

// Include Interfaces Used
#include "CMEventProcessor.h"
#include "CMEventAnnouncer.h"

@interface CMNetwork : NSObject <CMEventProcessor, CMEventAnnouncer>
{
    // Declare ivars
    //! Network connection controller between client and host
    SGConnection *_ctn;
    //! Defines a unique address of this machine
    NSString     *_networkID;
}

@property (readonly) BOOL isConnected;

// Declare constructors
-(id) initAsHost;
-(id) initAsClientWithIPAddress:(NSString*) ipAddr;

// Declare methods
-(void) processMessages;

@end
