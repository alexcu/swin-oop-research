/**
 * @protocol    CMEventProcessor
 * @author      Alex Cummaudo
 * @date        20 Oct 2013
 * @brief       A protocol class that defines
 *              all the methods that each processor
 *              of events must implement
 */

#import <Foundation/Foundation.h>

// Import parent protocol
#import "CMEventSubscriber.h"

// Forward declare classes reference
@class CMEvent;

@protocol CMEventProcessor <CMEventSubscriber>

/**
 * @brief   Defines that whoever uses this interface
 *          must process an event in anyway with the
 *          given Event
 * @param   eData
 *          Event Data to process
 */
-(void) processEvent:(CMEvent*) eData;

@end
