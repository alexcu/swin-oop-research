#import <Foundation/Foundation.h>

// Import protocols
#import "CMEventProcessor.h"
#import "CMEventAnnouncer.h"

// Forward declare referened classes
@class CMCat;
@class CMAnimal;
@class CMMouse;
@class SGTimer;

/**
 * @class   CMGame
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines class for the general `game' of
 *          the cat and mice
 */
@interface CMGame : NSObject <CMEventAnnouncer, CMEventProcessor>
{
    
    // A game will only control one of the cat or
    // mouse; so we have a controller as a Animal base
    // class to signify the controller (the player)
    
    //! Player of the game (person controlling the game)
    CMAnimal    *_player;
    //! Other player in the game (other person controlling enemy)
    CMAnimal    *_otherPlayer;
    
    // Cat and mouse to work with within the game
    //! Cat (chaser) of the game
    CMCat       *_cat;
    //! Mouse (chasee) of the game
    CMMouse     *_mouse;
    
    //! Ingame-timer to keep track of how long game has gone for
    SGTimer     *_gameTimer;
}

-(id) initControllingCat:(BOOL) asCat;

@end