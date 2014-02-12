/**
 * @class   Animal
 * @author  Alex Cummaudo
 * @date    2 Nov 2013
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

// Forward declare all classes referenced
class Cat;
class Mouse;
class Animal;
class Network;
class GUI;

class Game
{

public:
    // Declare constructor and destructor
    Game();
    Game(string ipAddr);
    ~Game();
    
    void process_game();

    // Called by network
    void update_other_player(float x, float y);

    bool is_valid();
    
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
    
    //! Couple the network view to the game model
    Network *_networkView;
    
    //! Couple the GUI view to the game model only for HUD
    GUI     *_guiView;
    
    // Private game methods
    void    send_player_update();
    void    check_keys();
};

#endif /* defined(__CatMouse__Game__) */
