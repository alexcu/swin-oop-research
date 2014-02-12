/**
 * @class   GUI View
 * @author  Alex Cummaudo
 * @date    2 Nov 2013
 * @brief   Provides GUI View for the game
 *          to display the game on in a graphics
 *          window
 */

#ifndef __CatMouse__GUI__
#define __CatMouse__GUI__

// Include SwinGame
#include "SwinGame.h"

// Includes and std namespace
#include <iostream>
#include <sstream>
using namespace std;

// Include forward references
class Animal;

class GUI
{

public:
    
    // Constructor and destructor defs
    GUI(float refRate);
    
    // Public methods
    void process_screen();
    void draw_animal(Animal *animal);
    
private:
    
    // Private fields
    
    //! Timer used to refresh the screen at the by clearing the
    //! screen and resetting at refreshRate given
    timer   _refreshTimer;
    //! Seconds to refresh the screen at
    float   _refreshRate;
    
};

#endif /* defined(__CatMouse__GUI__) */
