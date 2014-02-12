/**
 * @class   Animal
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines an abstract, base class for a playable
 *          `thing' on the screen which can move around etc.
 */

#include "Animal.h"

/**
 * @brief   Default constructor for initialising
 *          _position and _speed for all new Animals
 */
Animal::Animal()
{
    // Initialise new point2d object
    _position = new point2d;
    // Y pos it always random y coord
    _position->y = rnd_upto(screen_height());
};

/**
 * @brief   Destructor reliquishes resources created
 *          in this class
 */
Animal::~Animal()
{
    _position = NULL;
    delete _position;
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
void Animal::move(dirs dir)
{
    // Move only where not off screen
    if (dir == north) { _position->y -= _speed; }
    if (dir == south) { _position->y += _speed; }
    if (dir == east ) { _position->x += _speed; }
    if (dir == west ) { _position->x -= _speed; }
    // Check off screen
    this->off_screen();
}

/**
 * @brief   Off screen check that prevents any Animal from
 *          going outside the borders of the screen
 */
void Animal::off_screen()
{

    // If position has move beyond the screen
    // then push it back in all cases
    if (_position->x > screen_width() ) { _position->x = screen_width();    }
    if (_position->x < 0              ) { _position->x = 0;                 }
    if (_position->y > screen_height()) { _position->y = screen_height();   }
    if (_position->y < 0              ) { _position->y = 0;                 }

}