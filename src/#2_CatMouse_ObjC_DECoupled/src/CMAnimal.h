/**
 * @class   CMAnimal
 * @author  Alex Cummaudo
 * @date    23 Oct 2013
 * @brief   Defines an abstract, base class for a playable
 *          `thing' on the screen which can move around etc.
 */

#import <Foundation/Foundation.h>

// Include SwinGame SDK
#import "SwinGame.h"

/**
 * @typedef dirs
 * @brief   Defines compass directions in which animals can move in
 */
typedef enum dirs
{
    north,  //!< To move in negative y direction
    south,  //!< To move in positive y direction
    east,   //!< To move in positive x direction
    west    //!< To move in negative x direction
}
dirs;

@interface CMAnimal : NSObject
{
    // Declare ivars
    
    //! Centrepoint position of the animal
    SGPoint2D   *_position;
    
    //! Speed at which animals move at, set to a value of 3
    int          _speed;

    //! Name of animals, overriden by children (i.e. `Cat' or `Mouse')
    NSString    *_name;
}

//! Readwrite property to update position, used by CMGame
@property   (retain)    SGPoint2D   *position;
//! Readonly property to name, used by CMGUI and CMNetwork
@property   (readonly)  NSString    *name;

-(void) move:(dirs) dir;

@end
