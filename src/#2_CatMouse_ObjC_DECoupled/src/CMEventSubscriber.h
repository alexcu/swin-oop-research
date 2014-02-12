/**
 * @protocol    CMEventSubscriber
 * @author      Alex Cummaudo
 * @date        22 Oct 2013
 * @brief       Acts as a parent to subscribers
 *              and announcers so that the Event
 *              manager knows what to manager
 *              (i.e. both Announcers and Processors,
 *              and this allows this relationship
 *              to occur via inheritance)
 */

#import <Foundation/Foundation.h>

// Forward declare classes used
@class CMEvent;


@protocol CMEventSubscriber <NSObject>
// No actual definition; this protocol is empty
// and exists only to relate Announcers and Processors
@end
