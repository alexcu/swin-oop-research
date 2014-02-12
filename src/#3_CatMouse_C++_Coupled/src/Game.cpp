/**
 * @class   Game
 * @author  Alex Cummaudo
 * @date    2 Nov 2013
 * @brief   Defines class for the general `game' of
 *          the cat and mice
 */

// Include my header
#include "Game.h"

// Include used classes
#include "CatMouse.hpp"
#include "Network.h"
#include "GUI.h"

/**
 * @brief   On construction of a game, this overloaded
 *          version of the constructor will intitalise
 *          the network as a host, and make the player
 *          a cat.
 */
Game::Game()
{
    // Initiate as host
    _networkView = new Network(this);
    
    // Construct the GUI
    _guiView = new GUI(.5);
    
    _cat    = new Cat();
    _mouse  = new Mouse();
    
    // Hosting... therefore player is a cat!
    _player = _cat  ; _otherPlayer = _mouse;
    
    _gameTimer = create_timer();
    start_timer(_gameTimer);
    
    // Directly to cout
    cout << "Game started! You're the " << _player->get_name() << endl;
}

/**
 * @brief   On construction of a game, this overloaded
 *          version of the constructor will intitalise
 *          the network as a client, and make the player
 *          a mouse.
 * @param   ipAddr
 *          Host to connect to
 */
Game::Game(string ipAddr)
{
    // Initiate as client
    _networkView = new Network(this, ipAddr);
    
    // Construct the GUI
    _guiView = new GUI(.5);
    
    _cat    = new Cat();
    _mouse  = new Mouse();
    
    // Client... therefore player is a mouse
    _player = _mouse; _otherPlayer = _cat;
    
    _gameTimer = create_timer();
    start_timer(_gameTimer);
    
    // Directly to cout
    cout << "Game started! You're the " << _player->get_name() << endl;
}

/**
 * @brief   Destructor reliquishes resources created
 *          in this class
 */
Game::~Game()
{
    stringstream msg;
    cout << "Game has ended at " << timer_ticks(_gameTimer) / 1000 << "s" << endl;
    
    delete _cat;
    delete _mouse;
    delete _guiView;
    delete _networkView;
}

/**
 * @brief   Called to process the game
 */
void Game::process_game()
{
    // Process swingame events
    process_events();
    
    // Check the keys
    this->check_keys();
    
    // Game now asks GUI to update
    _guiView->process_screen();
    // Game now asks network to update
    _networkView->process_messages();
}

/**
 * @brief   Method called to update the players
 *          position and send it to the remote 
 *          model
 */
void Game::check_keys()
{
    // Keyboard checks will directly ask players to move
    if (key_down(VK_UP))
    {
        _player->move(north);
        this->send_player_update();
        
        _guiView->draw_animal(_player);
    }
    if (key_down(VK_DOWN))
    {
        _player->move(south);
        this->send_player_update();
        
        _guiView->draw_animal(_player);
    }
    if (key_down(VK_LEFT))
    {
        _player->move(west);
        this->send_player_update();
        
        _guiView->draw_animal(_player);
    }
    if (key_down(VK_RIGHT))
    {
        _player->move(east);
        this->send_player_update();
        
        _guiView->draw_animal(_player);
    }
}

/**
 * @brief   Sends a message over the network to update
 *          the current player's position
 */
void Game::send_player_update()
{
    // Only process where a connection is established
    if (_networkView->is_connected())
    {
        stringstream data;
        
        // Push data out as key:value, pairs of the x and y coords, as well as the
        // connection's network id
        data    << "Message"    << ":" << "Animal Moved"                        << ","
                << "Character"  << ":" << _player->get_name()                   << ","
                << "x"          << ":" << to_string(_player->get_position()->x) << ","
                << "y"          << ":" << to_string(_player->get_position()->y) << ",";
        
        _networkView->send_message(data.str());
    }
}

/**
 * @brief   Updates the other player's position
 * @note    This is called from CMNetwork
 */
void Game::update_other_player(float x, float y)
{
    point2d *newpoint = new point2d();
    newpoint->x = x;
    newpoint->y = y;
    _otherPlayer->set_position(newpoint);

    // Relinquish new point
    delete newpoint;
    
    // Draw updates to gui
    _guiView->draw_animal(_otherPlayer);
}

//! The is valid ensures that the game is still valid, only where it has a network
//! connection (essentially, returns the state of the connection as true/false)
//! @return The validity of the game (whether or not is connected)
bool Game::is_valid()
{
    return _networkView->is_connected();
}