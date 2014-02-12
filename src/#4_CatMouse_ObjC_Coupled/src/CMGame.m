// Import header file
#import "CMGame.h"

// Import referenced classes
#include "CMNetwork.h"
#include "CMGUI.h"
#include "CMCatMouse.h"

// Import SwinGame
#import "SwinGame.h"


/**
 * @class   CMGame
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines class for the general `game' of
 *          the cat and mice
 */
@implementation CMGame

/**
 * @brief   Implentation of the isValid property
 * @return  Valid connection of network
 */
-(BOOL) isValid
{
    return _networkView.isConnected;
}

/**
 * @brief   On construction of a game, this overloaded
 *          version of the constructor will intitalise
 *          the network as a host, and make the player
 *          a cat.
 */
-(id) initAsHostCat
{
    if (self = [super init])
    {
        // Initiate as host
        _networkView = [[CMNetwork alloc] initAsHostInGame:self];

        // Construct the GUI
        _guiView = [[CMGUI alloc] initWithRefreshRate:.5f];
        
        _cat    = [[CMCat alloc] init];
        _mouse  = [[CMMouse alloc] init];
        
        // Hosting... therefore player is a cat!
        _player = _cat  ; _otherPlayer = _mouse;
        
        // Initialise _gameTimer
        _gameTimer = [SGTimer createWithId:create_timer()];
        [_gameTimer start];
        
        NSLog(@"Game started! You're the %@", _player.name);
    }
    return self;
}

/**
 * @brief   On construction of a game, this overloaded
 *          version of the constructor will intitalise
 *          the network as a client, and make the player
 *          a mouse.
 * @param   ipAddr
 *          Host to connect to
 */
-(id) initAsClientMouseConnectingTo:(NSString *)ipAddr
{
    if (self = [super init])
    {
        // Initiate as host
        _networkView = [[CMNetwork alloc] initAsClientWithIPAddress:ipAddr
                                                             inGame:self];
        
        // Construct the GUI
        _guiView = [[CMGUI alloc] initWithRefreshRate:.5f];
        
        _cat    = [[CMCat alloc] init];
        _mouse  = [[CMMouse alloc] init];
        
        // Client... therefore player is a mouse
        _player = _mouse; _otherPlayer = _cat;
        
        // Initialise _gameTimer
        _gameTimer = [SGTimer createWithId:create_timer()];
        [_gameTimer start];
        
        NSLog(@"Game started! You're the %@", _player.name);
    }
    return self;
}

/**
 * @brief   Destructor removes all references to my owned
 *          views
 */
-(void) dealloc
{
    NSLog(@"Game has ended at %0.2fs", (float)_gameTimer.ticks/1000);
    
    [_networkView dealloc];
    [_guiView dealloc];
    
    [super dealloc];
}


/**
 * @brief   Called to process the game
 */
-(void) processGame
{
    // Process swingame events
    [SGInput processEvents];
    
    // Checks the keys
    [self checkKeys];
    
    // Game now asks GUI to update
    [_guiView processScreen];
    // Game now asks network to upate
    [_networkView processMessages];
}

/**
 * @brief   Method called to update the players
 *          position and send it to the remote
 *          model
 */
-(void) checkKeys
{
    // Keyboard checks will directly ask players to move
    if (key_down(VK_UP))
    {
        [_player move:north];
        [self sendPlayerUpdate];
        
        [_guiView drawAnimal:_player];
    }
    if (key_down(VK_DOWN))
    {
        [_player move:south];
        [self sendPlayerUpdate];
        
        [_guiView drawAnimal:_player];
    }
    if (key_down(VK_LEFT))
    {
        [_player move:west];
        [self sendPlayerUpdate];
        
        [_guiView drawAnimal:_player];
    }
    if (key_down(VK_RIGHT))
    {
        [_player move:east];
        [self sendPlayerUpdate];
        
        [_guiView drawAnimal:_player];
    }
}


/**
 * @brief   Sends a message over the network to update
 *          the current player's position
 */
-(void) sendPlayerUpdate
{
    // Only process where a connection is established
    if (_networkView.isConnected)
    {
        
        // Push data out as key:value, pairs of the x and y coords, as well as the
        // connection's network id
        [_networkView sendMessageWithString:
         [NSString stringWithFormat:@"%@:%@,%@:%@,%@:%@,%@:%@,",
                                   @"Message", @"Animal Moved",
                                   @"Character", _player.name,
                                   @"x",[NSString stringWithFormat:@"%f",_player.position.x],
                                   @"y",[NSString stringWithFormat:@"%f",_player.position.y]]]
                                                                                             ;
    }
}

/**
 * @brief   Updates the other player's position
 * @note    This is called from CMNetwork
 */
-(void) updateOtherPlayerToX:(float)x andY:(float)y
{
    [_otherPlayer setPosition:[SGGeometry pointAtX:x y:y]];
    [_guiView drawAnimal:_otherPlayer];
}

@end
