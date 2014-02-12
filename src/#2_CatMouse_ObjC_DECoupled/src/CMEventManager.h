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

#import <Foundation/Foundation.h>

// Forward declare classes/protocols used
@class CMEvent;
@protocol CMEventSubscriber;

@interface CMEventManager : NSObject

/**
 * @brief   This method is automatically called on a
 *          creation of the CMEventClass object, and
 *          is used to initialise the NSMutableArray
 *          that contains the subscribers
 */
+(void) initialize;

// Declare factory methods
+(void) publishEvent:(CMEvent*)   eventToPublish;
+(void) addSubscriber:(NSObject<CMEventSubscriber>*)subscriberToAdd;
+(void) forgetSubscriber:(NSObject<CMEventSubscriber>*)subscriberToForget;

@end
