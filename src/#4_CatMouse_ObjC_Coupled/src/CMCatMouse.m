#import "CMCatMouse.h"

@implementation CMCat

/**
 * @brief   The default constructor for the cat
 *          constructs parent and sets position on
 *          lefthand-side of screen
 * @return  The self class pointer
 */
-(id) init
{
    if (self = [super init])
    {
        _position.x = [SGGraphics screenWidth]/4;
        _name       = @"Cat";
    }
    return self;
}

@end

@implementation CMMouse

/**
 * @brief   The default constructor for the mouse
 *          constructs parent and sets position on
 *          righthand-side of screen
 * @return  The self class pointer
 */
-(id) init
{
    if (self = [super init])
    {
        _position.x = 3*[SGGraphics screenWidth]/4;
        _name       = @"Mouse";
    }
    return self;
}

@end