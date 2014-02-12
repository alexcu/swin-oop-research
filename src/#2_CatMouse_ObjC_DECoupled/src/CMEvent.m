/**
 * @class   CMEvent
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Defines event class of what to pass a
 *          view, thereby allowing a link between
 *          each view and each model.
 */

#import "CMEvent.h"

@implementation CMEvent

// Synthesis of property
@synthesize data = _data;

/**
 * @brief   Constructor for new event object to
 *          initialise fields
 * @param   initialData
 *          Textual data to insert as data to this
 *          event
 * @return  The self class pointer
 */
-(id) initWithData:(NSDictionary*) initialData
{
    if (self = [super init])
    {
        _data = initialData;
    }
    return self;
}

@end
