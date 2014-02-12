// Import header file
#import "CMGame.h"

// Import referenced classes
#import "CMCatMouse.h"
#import "CMEvent.h"
#import "CMEventManager.h"

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
 * @brief   On construction of a game, a cat and
 *          a mouse will be created---if the asCat
 *          is true, player references the cat, else
 *          it will reference the mouse. Automatically
 *          adds me to the CMEventManager.
 * @param   asCat
 *          Where true, the game initialises the
 *          player as the cat, with the other player
 *          as the mouse.
 * @return  The self class pointer
 */
-(id) initControllingCat:(BOOL) asCat;
{
    if (self = [super init])
    {
        // Add me to CMEventManager
        [CMEventManager addSubscriber:self];
        
        _cat    = [[CMCat alloc] init];
        _mouse  = [[CMMouse alloc] init];
        
        if (asCat) { _player = _cat  ; _otherPlayer = _mouse; }
        else       { _player = _mouse; _otherPlayer = _cat  ; }
        
        // Initialise _gameTimer
        _gameTimer = [SGTimer createWithId:create_timer()];
        [_gameTimer start];
        
        [self announceEvent:
         [NSString stringWithFormat:@"Game started! You're the %@", _player.name]];
    }
    return self;
}

/**
 * @brief   Destructor removes me from the CMEventManager
 */
-(void) dealloc
{
    [self announceEvent:
     [NSString stringWithFormat:@"Game has ended at %0.2fs", (float)_gameTimer.ticks/1000]];
    
    // Ask CMEventManager to forget about me
    [CMEventManager forgetSubscriber:self];
    [super dealloc];
}

/**
 * @brief   Announces that the player moved (called
 *          by key_check on a key move) to all of CMEventManager's
 *          CMEventProcessors---i.e. to announce updates of
 *          the model
 * @param   message
 *          Message to announce
 */
-(void) announceEvent:(NSString*) message
{
    CMEvent* event = [[CMEvent alloc]
                      initWithData:@{@"Message"     : message                                ,
                                     @"x"           :
                                   [NSString stringWithFormat:@"%d", (int)_player.position.x],
                                     @"y"           :
                                   [NSString stringWithFormat:@"%d", (int)_player.position.y],
                                     @"Character"   : _player.name                           ,
                                     @"Source"      : @"Game"                                ,
                                     @"Time"        :
                         [NSString stringWithFormat:@"%0.2f", (float)_gameTimer.ticks/1000]}];
    [CMEventManager publishEvent:event];
    [event release];
}

/**
 * @brief   Recieves events from the CMEventManager
 *          to set the coordinates of the players
 *          to either a specified location (_otherPlayer)
 *          or to move the _player according to key events
 * @param   eData
 *          Event Data to process
 */
-(void) processEvent:(CMEvent*) eData
{
    // Get the dictionary of the event data
    NSDictionary *eventData = eData.data;

    // Only process events where keys for Source are found
    // and Character (for _otherPlayer update) or
    //     KeyDown   (for _player update)
    
    /*
     * SOURCE FOR KEYBOARD (_thisPlayer update)
     */
    if ([[eventData objectForKey:@"Source"] isEqual:@"Keyboard"])
    {
        // Begin scanning through each key/value pair in data
        for (id key in eventData)
        {
            NSString* keyDown = [eventData objectForKey:@"KeyDown"];
            //! Given there is data for that key
            if (keyDown)
            {
                if ([keyDown isEqual: @"up_key"])
                {
                    [_player move:north];
                    [self announceEvent:@"Animal Moved"];
                }
                if ([keyDown isEqual: @"down_key"])
                {
                    [_player move:south];
                    [self announceEvent:@"Animal Moved"];
                }
                if ([keyDown isEqual: @"left_key"])
                {
                    [_player move:west];
                    [self announceEvent:@"Animal Moved"];
                }
                if ([keyDown isEqual: @"right_key"])
                {
                    [_player move:east];
                    [self announceEvent:@"Animal Moved"];
                }
            }
        }
    }
    /*
     * SOURCE FOR NETWORK (_otherPlayer update)
     */
    else if ([[eventData objectForKey:@"Source"]    isEqual     :@"Network"]   &&
             [[eventData objectForKey:@"Character"] isNotEqualTo:_player.name] &&
             [[eventData objectForKey:@"x"] isNotEqualTo:nil]                  &&
             [[eventData objectForKey:@"y"] isNotEqualTo:nil]                    )
    {
        // Get the x/y value for this dot
        NSNumber *x = [eventData valueForKey:@"x"];
        NSNumber *y = [eventData valueForKey:@"y"];
        
        // Create new pos variable
        SGPoint2D *newPos = [[SGPoint2D alloc]
                             // Need to get int value since object is NSNumber object
                             // and not primitive int value
                             initAtX:[x intValue]
                                   y:[y intValue]];

        // Set the position of the other player to new pos
        [_otherPlayer setPosition:newPos];
        [newPos release];
    }

    
}

@end