// Import parent header
#import "CMGUI.h"

// Import referenced classes
#import "CMEvent.h"
#import "CMEventManager.h"

// Import research details
#import "ProjectInfo.h"

/**
 * @class   CMGUI
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Provides GUI View for the game
 *          to display the game on in a graphics
 *          window
 */
@implementation CMGUI

/**
 * @brief   Constructor for GUI view creates a graphics
 *          window for SwinGame
 * @return  The self class pointer
 */
-(id) initWithRefreshRate:(float) refRate
{
    if (self = [super init])
    {
        // Ask CMEventManager to start handling me
        [CMEventManager addSubscriber:self];
        
        [SGGraphics openGraphicsWindow:@"Cat Mouse"];
        [SGColors loadDefaultColors];
        
        // Fresh new screen to start with
        [SGGraphics clearScreen:ColorBlack];
        
        // Display initialising message
        [SGText drawText:@"===     C A T   M O U S E     ===" color:ColorGreen x:240 y:400];
        [SGText drawText:@PROJECT_DESC                        color:ColorRed   x:3   y:3  ];
        [SGText drawText:@"*** INITIALISING ***"              color:ColorWhite x:300 y:440];
        [SGText drawText:@"Refer to console"                  color:ColorWhite x:320 y:460];
        
        // Draw logo
        [SGImages draw:[SGImages loadBitmapFile:@"meow.png"] onScreenAtX:200 y:100];
        
        // Refresh screen to update changes
        [SGGraphics refreshScreen];
        
        // Delay to ensure window is open
        [SGUtils delay:1000];
        
        // Init and start refresh timer
        _refreshRate  = refRate;
        _refreshTimer = [SGTimer createWithId:create_timer()];
        [_refreshTimer start];
    }
    return self;
}

/**
 * @brief   Destructor asks CMEventManager to
 *          forget about me
 */
-(void) dealloc
{
    
    [CMEventManager forgetSubscriber:self];
    [super dealloc];
}

/**
 * @brief   Clears and refreshes the screen by the
 *          time given in reset timer
 */
-(void) processScreen
{
    if ([_refreshTimer ticks] > _refreshRate * 1000)
    {
        [_refreshTimer reset];
        [SGGraphics clearScreen: ColorWhite];
    }
    [SGGraphics fill:ColorBlack
  rectangleOnScreenX:0
                   y:0
               width:[SGGraphics screenWidth]
              height:30];
    [SGText drawText:@PROJECT_DESC color:ColorWhite x:3 y:3];
    [SGText drawFramerateAtX:2 y:13];
    [SGGraphics refreshScreen];
}

/**
 * @brief   Processes events by drawing only Game events
 *          onto the screen given the Game event is about
 *          an Animal
 * @param   eData
 *          Event Data to process
 */
-(void) processEvent:(CMEvent *)eData
{
    NSDictionary *eventData = eData.data;
    
    id source    = [eventData objectForKey:@"Source"];
    id character = [eventData objectForKey:@"Character"];
    
    // Only process events for Network (other player) and Game (this player)
    // and given that there was some character data passed
    if (( [source  isEqual: @"Network"] || [source  isEqual: @"Game"]) &&
        ( character != nil                                           )    )
        {
            // Get the x/y value for this dot
            NSNumber *x = [eventData valueForKey:@"x"];
            NSNumber *y = [eventData valueForKey:@"y"];
            
            // Default Color Black for shapes until we change
            // to cat/mouse parsing below
            color shapeColor = ColorBlack;

            // Red for cat characters
            if ([character  isEqual: @"Cat"]  ) { shapeColor = ColorRed; }
            
            // Blue for cat characters
            if ([character  isEqual: @"Mouse"]) { shapeColor = ColorBlue; }

            // Finally, draw the shapes on the screen
            [SGGraphics fill:shapeColor
             circleOnScreenX:[x intValue]
                           y:[y intValue]
                      radius:15];
            // Draw whose cat and whose mouse with their initials
            [SGText drawText:[NSString stringWithFormat:@"%@      ",
                              [character substringToIndex:1]]
                       color:ColorWhite
                           x:[x intValue]-10
                           y:[y intValue]-2];
        }
}

@end