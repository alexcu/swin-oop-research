/**
 * @class   CMAnimal
 * @author  Alex Cummaudo
 * @date    23 Oct 2013
 * @brief   Defines an abstract, base class for a playable
 *          `thing' on the screen which can move around etc.
 */

#import "CMAnimal.h"

@implementation CMAnimal

@synthesize position = _position;
@synthesize name     = _name;

/**
 * @brief   Default constructor for initialising
 *          _position and _speed for all new Animals
 * @return  The self class pointer
 */
-(id) init
{
    if (self = [super init])
    {
        // Initialise new SGPoint2D object
        _position = [[SGPoint2D alloc] init];
        // Y pos it always random y coord
        _position.y = [SGUtils rndUpto:[SGGraphics screenHeight]];
        // Initialise speed for all animals
        _speed = 3;
    }
    return self;
}

/**
 * @brief   Move implementation for a Animal to
 *          move an animal in a direction at
 *          its speed
 * @param   dir
 *          Direction the animal is told to move
 *          in (alters x and y axis position of
 *          poisition accordingly)
 */
-(void) move:(dirs)dir
{
    // Move only where not off screen
    if (dir == north) { _position.y -= _speed; }
    if (dir == south) { _position.y += _speed; }
    if (dir == east ) { _position.x += _speed; }
    if (dir == west ) { _position.x -= _speed; }
    // Check off screen
    [self checkOffScreen];
}

/**
 * @brief   Off screen check that prevents any Animal from
 *          going outside the borders of the screen
 */
-(void) checkOffScreen
{
    // If position has move beyond the screen
    // then push it back in all cases
    if (_position.x > [SGGraphics screenWidth] ) { _position.x = [SGGraphics screenWidth];  }
    if (_position.x < 0)                         { _position.x = 0;                         }
    if (_position.y > [SGGraphics screenHeight]) { _position.y = [SGGraphics screenHeight]; }
    if (_position.y < 0)                         { _position.y = 0;                         }
}

@end
