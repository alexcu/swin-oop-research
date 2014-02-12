/**
 * @class   CMEventManager
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Defines Event Manager class which
 *          processes each event to each kind of
 *          event subscriber.
 * @note    This is a factory member class; so that
 *          clients do not need to make an instance
 *          of an CMEventManager (since there's only ever
 *          going to be one processor). Therefore
 *          we invoke EventManager by calling directly
 *          on the class
 *          (i.e. [EventManager notifySubscribers:Event])
 */

// Import my class header
#import "CMEventManager.h"

// Import referenced classes
#import "CMEventSubscriber.h"
#import "CMEventProcessor.h"

// Declare static fields to use on factory methods
static NSMutableArray* _subs;

@implementation CMEventManager

/**
 * @brief   This method is automatically called on a when
 *          class objects are created, to initialise the
 *          _subs Collection.
 */
+(void) initialize
{
    if (self == [CMEventManager class])
    {
        _subs = [[NSMutableArray alloc] init];
    }
}

/**
 * @brief   Adds a subscriber to the _subs collection
 *          (can be any NSObject as long as it uses
 *          the CMEventSubscriber interface---either a:
 *          CMEventAnnouncer or CMEventProcessor
 * @param   subscriberToAdd
 *          Subscriber to now manage
 */
+(void) addSubscriber:(NSObject<CMEventSubscriber> *)subscriberToAdd
{
    [_subs addObject:subscriberToAdd];
}

/**
 * @brief   Kills a subscriber
 * @param   subscriberToKill
 *          Subscriber to now forget
 */
+(void) forgetSubscriber:(NSObject<CMEventSubscriber> *)subscriberToForget
{
    [_subs removeObject:subscriberToForget];
}


/**
 * @brief   Processes the event for each kind
 *          subscriber (i.e. CMEventProcessors ONLY!)
 * @param   eventToPublish
 *          CMEvent to publish to all CMEventProcessors
 */
+(void) publishEvent:(CMEvent *)eData
{
    // For each NSObject that is an CMEventProcessor
    for (id subscriber in _subs)
    {
        // Process the event only where 
        if ([subscriber conformsToProtocol:@protocol(CMEventProcessor)])
            [subscriber processEvent:eData];
    }
}

@end
