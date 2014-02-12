// Include SwinGame SDK
#include "SwinGame.h"

// Includes and std namespace
#include <iostream>
using namespace std;

// Include parent Animal
#include "Animal.h"

#ifndef __CatMouse__Cat__
#define __CatMouse__Cat__


/**
 * @class   Cat
 * @author  Alex Cummaudo
 * @date    18 Oct 2013
 * @brief   Defines an class for a playable
 *          chaser (i.e. the chasing cat)
 */
class Cat : public Animal
{

public:
    
    /**
     * @brief   The default constructor for the cat
     *          constructs parent and sets position on
     *          lefthand-side of screen
     */
    Cat()
    {
        _position->x = screen_width() / 4;
        _name = "Cat";
    }
    
};


/**
 * @class   Mouse
 * @author  Alex Cummaudo
 * @date    18 Oct 2013
 * @brief   Defines an class for a playable
 *          chasee (i.e. the hunted mouse)
 */
class Mouse : public Animal
{
    
public:
    
    /**
     * @brief   The default constructor for the mouse
     *          constructs parent and sets position on
     *          righthand-side of screen
     */
    Mouse()
    {
        _position->x = 3 * screen_width() / 4;
        _name = "Mouse";
    }

};

#endif /* defined(__CatMouse__Cat__) */
