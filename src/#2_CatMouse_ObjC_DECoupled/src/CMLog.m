/**
 * @class   CMLog
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   CLI view to game
 */

#import "CMLog.h"

// Include headers of classes used
#import "CMEvent.h"
#import "CMEventManager.h"

@implementation CMLog

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
 * @brief   Processes a data depending on the
 *          the data passed by printing each
 *          key/value pair in the event data's 
 *          dictionary
 * @param   eData
 *          Event Data to process
 */
-(void) processEvent:(CMEvent *)eData
{
    NSDictionary *eventData = eData.data;
    
    NSMutableString *serialisedEvent =
    [[NSMutableString alloc] initWithString:@"\n*** EVENT OCCURED ***\n{\n"];

    // Print every key/value pair in the event data dictionary
    for (id key in eventData)
    {
        [serialisedEvent appendFormat:@"    %@: %@\n", key, [eventData objectForKey:key]];
    }
    
    [serialisedEvent appendString:@"}"];
    
    // Finally output the serialised event
    NSLog(@"%@", serialisedEvent);
    
    [serialisedEvent release];
}

@end
