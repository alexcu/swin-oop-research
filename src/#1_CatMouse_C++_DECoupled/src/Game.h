/**
 * @class   Animal
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines class for the general `game' of
 *          the cat and mice
 */

#ifndef __CatMouse__Game__
#define __CatMouse__Game__

// Include SwinGame
#include "SwinGame.h"

// Includes and std namespace
#include <iostream>
#include <sstream>
using namespace std;

// Include the EventProcessor
#include "EventProcessor.h"
#include "EventAnnouncer.h"

// Forward declare all classes referenced
class Cat;
class Mouse;
class Animal;

class Game : public EventProcessor, public EventAnnouncer
{

public:
    // Declare constructor and destructor
    Game(bool asCat);
    ~Game();
    
    virtual void    process_event(Event *eData);
    
private:
    
    // A game will only control one of the cat or
    // mouse; so we have a controller as a Animal base
    // class to signify the controller (the player)
    Animal     *_player;        //!< Player of the game (person controlling the game)
    Animal     *_otherPlayer;   //!< Other player in the game (other person controlling enemy)
    
    // Cat and mouse to work with within the game
    Cat     *_cat;              //!< Cat (chaser) of the game
    Mouse   *_mouse;            //!< Mouse (chasee) of the game
    
    //! Ingame-timer to keep track of how long game has gone for
    timer   _gameTimer;
    
    // Private game methods used to update changes to model
    virtual void    announce_event(string msg);
    
};

#endif /* defined(__CatMouse__Game__) */
