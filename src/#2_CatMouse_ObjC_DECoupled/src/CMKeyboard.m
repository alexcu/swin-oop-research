/**
 * @class   CMKeyboard
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Defines class to capture keyboard
 *          events and pass them to the processor
 */

// Import parent header
#import "CMKeyboard.h"

// Import referenced classes
#import "CMEventManager.h"
#import "CMEvent.h"

@implementation CMKeyboard

/**
 * @brief   Constructor asks CMEventManager to
 *          start handling me
 */
-(id) init
{
   if (self = [super init])
   {
       [CMEventManager addSubscriber:self];
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
 * @brief   Captures keydown events and processes
 *          them by passing them to the Event Manager
 */
-(void) processKeyboard
{
    [SGInput processEvents];
    if ([SGInput keyDown:VK_UP   ]) { [self announceEvent:@"up_key"   ]; }
    if ([SGInput keyDown:VK_DOWN ]) { [self announceEvent:@"down_key" ]; }
    if ([SGInput keyDown:VK_LEFT ]) { [self announceEvent:@"left_key" ]; }
    if ([SGInput keyDown:VK_RIGHT]) { [self announceEvent:@"right_key"]; }
}

/**
 * @brief   Sends an event to all subscribers with the given key
 * @param   msg
 *          Message to announce when creating an Event
 */
-(void) announceEvent:(NSString *)message;
{
    // Push to eventData to say this event originated from the keyboard view
    CMEvent* event = [[CMEvent alloc] initWithData:@{@"KeyDown" : message,
                                                     @"Source"  : @"Keyboard"}];
    
    [CMEventManager publishEvent:event];
    [event release];
}

@end