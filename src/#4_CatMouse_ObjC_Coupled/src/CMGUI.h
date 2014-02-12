/**
 * @class   CMGUI
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Provides GUI View for the game
 *          to display the game on in a graphics
 *          window
 */

#import <Foundation/Foundation.h>

// Include SwinGame
#import "SwinGame.h"

// Forward declare referenced classes
@class CMAnimal;

@interface CMGUI : NSObject
{
    // Declare ivars
    //! Timer used to refresh the screen at the by clearing the
    //! screen and resetting at refreshRate given
    SGTimer *_refreshTimer;
    //! Seconds to refresh the screen at
    float    _refreshRate;
}

// Declare constructor
-(id) initWithRefreshRate:(float) refRate;

// Decalre processor
-(void) processScreen;

-(void) drawAnimal:(CMAnimal*) animalToDraw;

@end
