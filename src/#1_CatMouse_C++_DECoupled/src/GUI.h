/**
 * @class   GUI View
 * @author  Alex Cummaudo
 * @date    19 Oct 2013
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
using namespace std;

// Include Interface
#include "EventProcessor.h"

class GUI : public EventProcessor
{

public:
    
    // Constructor and destructor defs
     GUI(float refRate);
    
    // Redefine overriden EventProcessor method
    virtual void process_event(Event *eData);
    
    // Public methods
    void process_screen();
    
private:
    
    // Private fields
    
    //! Timer used to refresh the screen at the by clearing the
    //! screen and resetting at refreshRate given
    timer   _refreshTimer;
    //! Seconds to refresh the screen at
    float   _refreshRate;
    
};

#endif /* defined(__CatMouse__GUI__) */
