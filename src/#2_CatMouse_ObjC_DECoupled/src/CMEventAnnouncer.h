/**
 * @protocol    CMEventAnnouncer
 * @author      Alex Cummaudo
 * @date        20 Oct 2013
 * @brief       An protocol that defines all the
 *              methods that each announcer of
 *              events must implement
 */

#import <Foundation/Foundation.h>

// Import parent protocol
#import "CMEventSubscriber.h"

@protocol CMEventAnnouncer <CMEventSubscriber>

/**
 * @brief   Defines that whoever uses this interface
 *          must announce events with given a message
 *          to the EventManager
 * @param   message
 *          Message to announce when creating an Event
 */
-(void) announceEvent:(NSString*) message;

@end