/**
 * @class   Game
 * @author  Alex Cummaudo
 * @date    16 Oct 2013
 * @brief   Defines class for the general `game' of
 *          the cat and mice
 */

// Include my header
#include "Game.h"

// Include used classes
#include "CatMouse.hpp"
#include "EventManager.h"
#include "Event.h"

/**
 * @brief   On construction of a game, a cat and
 *          a mouse will be created---if the asCat
 *          is true, player references the cat, else
 *          it will reference the mouse
 * @param   asCat
 *          Where true, the game initialises the
 *          player as the cat, with the other player
 *          as the mouse.
 */
Game::Game(bool asCat)
{
    _cat    = new Cat();
    _mouse  = new Mouse();
    
    if (asCat) { _player = _cat  ; _otherPlayer = _mouse; }
    else       { _player = _mouse; _otherPlayer = _cat  ; }
    
    _gameTimer = create_timer();
    start_timer(_gameTimer);
    
    this->announce_event("Game started! You're the "+_player->get_name());
}

/**
 * @brief   Destructor reliquishes resources created
 *          in this class
 */
Game::~Game()
{
    stringstream msg;
    msg << "Game has ended at " << timer_ticks(_gameTimer) / 1000 << "s";
    this->announce_event(msg.str());
    delete _cat;
    delete _mouse;
}

/**
 * @brief   Announces that the player moved (called
 *          by key_check on a key move) to all of EventManager's
 *          EventProcessors---i.e. to announce updates of
 *          the model
 * @param   msg
 *          Message to announce
 */
void Game::announce_event(string msg)
{
    // Announce an event to say that the key was pressed
    map<string, string> eventData;
    eventData["Message"] = msg;
    eventData["x"] = to_string((int)_player->get_position()->x);
    eventData["y"] = to_string((int)_player->get_position()->y);
    eventData["Character"] = _player->get_name();
    eventData["Source"] = "Game";
    eventData["Time"] = to_string((float)timer_ticks(_gameTimer)/1000);
    Event* event = new Event(eventData);
    
    EventManager::publish_event(event);
}

/**
 * @brief   Recieves events from the EventManager
 *          to set the coordinates of the players
 *          to either a specified location (_otherPlayer)
 *          or to move the _player according to key events
 * @param   eData
 *          Event Data to process
 */
void Game::process_event(Event *eData)
{
    // Get the map of the event data
    map<string, string> eventData = eData->get_data();
    
    // Initiate iterator (source) for the data
    auto src = eventData.find("Source");
    auto character = eventData.find("Character");
    auto key = eventData.find("KeyDown");
    
    // Only process events where keys for Source are found
    // and Character (for _otherPlayer update) or
    //     KeyDown   (for _player update)
    if  ( src != eventData.end() &&
        ( character != eventData.end() || key != eventData.end()) )
    {
        /*
         * SOURCE FOR KEYBOARD (_thisPlayer update)
         */
        if (src->second == "Keyboard")
        {
            // For every item in the event
            for (auto i = eventData.begin(); i != eventData.end(); ++i)
            {
                // Given that we're processing KeyDowns
                if (i->first == "KeyDown")
                {
                    if (i->second == "up_key")
                    {
                        _player->move(north);
                        announce_event("Animal Moved");
                    }
                    if (i->second == "down_key")
                    {
                        _player->move(south);
                        announce_event("Animal Moved");
                    }
                    if (i->second == "left_key")
                    {
                        _player->move(west);
                        announce_event("Animal Moved");
                    }
                    if (i->second == "right_key")
                    {
                        _player->move(east);
                        announce_event("Animal Moved");
                    }
                }
            }
        }
        /*
         * SOURCE FOR NETWORK (_otherPlayer update)
         */
        if ((src->second == "Network") &&
            (character->second != _player->get_name()))
        {
            // Create new pos variable
            point2d *newPos = new point2d;
            
            // For every item in the event
            for (auto i = eventData.begin(); i != eventData.end(); ++i)
            {
                
                // Only process events where keys are x or y (of enemy!)
                if (i->first == "x")
                {
                    // x is == to the value for this key
                    newPos->x = atoi(i->second.c_str());
                }
                if (i->first == "y")
                {
                    // y is == to the value for this key
                    newPos->y = atoi(i->second.c_str());
                }
            }
            
            // Set the position of the other player to new pos
            _otherPlayer->set_position(newPos);
        }
    }
}