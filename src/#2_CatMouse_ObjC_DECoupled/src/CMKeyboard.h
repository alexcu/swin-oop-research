/**
 * @class   CMKeyboard
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Defines class to capture keyboard
 *          events and pass them to the processor
 */

#import <Foundation/Foundation.h>

// Include SwinGame
#import "SwinGame.h"

// Import protocol
#import "CMEventAnnouncer.h"

@interface CMKeyboard : NSObject <CMEventAnnouncer>

// Define processor
-(void) processKeyboard;

@end
