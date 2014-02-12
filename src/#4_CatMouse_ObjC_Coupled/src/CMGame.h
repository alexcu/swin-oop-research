#import <Foundation/Foundation.h>

// Forward declare referened classes
@class CMCat;
@class CMAnimal;
@class CMMouse;
@class SGTimer;
@class CMNetwork;
@class CMGUI;

/**
 * @class   CMGame
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines class for the general `game' of
 *          the cat and mice
 */
@interface CMGame : NSObject
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
    
    //! Couple the network view to the game model
    CMNetwork   *_networkView;
    
    //! Couple the GUI view to the game model only for HUD
    CMGUI       *_guiView;
}

//! The is valid ensures that the game is still valid, only where it has a network
//! connection (essentially, returns the state of the connection as true/false)
//! @return The validity of the game (whether or not is connected)
@property (readonly) BOOL isValid;


-(id)   initAsHostCat;
-(id)   initAsClientMouseConnectingTo:(NSString*) ipAddr;
-(void) updateOtherPlayerToX:(float)x andY:(float)y;
-(void) processGame;

@end