/**
 * @class   Animal
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines an abstract, base class for a playable
 *          `thing' on the screen which can move around etc.
 */

#ifndef __CatMouse__Animal__
#define __CatMouse__Animal__

// Include SwinGame SDK
#include "SwinGame.h"

// Includes and std namespace
#include <iostream>
using namespace std;

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

class Animal
{

public:
    
    // Declare default constructor/destructor
    Animal();
    
    // Declare as pure virtual so that abstract base class can be used
    // (i.e. no Animals can be made since its an abstract base class)
    virtual ~Animal() = 0;
    
    // Define abstract methods
    void    move(dirs dir);
    
    //! Read property to get the position of the Animal
    //! @return Position of the animal
    point2d* const get_position()               { return _position; }
    //! Write property to set the position of the Animal
    //! @param  newPos
    //!         New position to set the animal at
    void           set_position(point2d *newPos){ _position = newPos; }
    
    //! Readonly property to get the name of the animal
    //! @return Name of the animal
    string  const  get_name() { return _name; }
    
protected:
    
    // Define the base items that all
    // children and animals will have

    //! Centrepoint position of the animal
    point2d     *_position;

    //! Speed at which animals move at, set to a value of 3
    const int    _speed = 3;
    
    //! Name of animals, overriden by children (i.e. `Cat' or `Mouse')
    string       _name;
    
private:
    
    // Off-scren check
    void        off_screen();
    
};

#endif /* defined(__CatMouse__Animal__) */
