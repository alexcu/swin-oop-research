/**
 * @class   CMEvent
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Defines event class of what to pass a
 *          view, thereby allowing a link between
 *          each view and each model.
 */


#import <Foundation/Foundation.h>

@interface CMEvent : NSObject
{
    //! Textual data contained within the Event
    NSDictionary *_data;
}

//! Readonly property to data
@property (readonly) NSDictionary *data;

// Constructor
-(id) initWithData:(NSDictionary*)data;

@end
