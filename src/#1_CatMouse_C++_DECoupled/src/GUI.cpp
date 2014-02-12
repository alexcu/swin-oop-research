/**
 * @class   GUI View
 * @author  Alex Cummaudo
 * @date    19 Oct 2013
 * @brief   Provides GUI View for the game
 *          to display the game on in a graphics
 *          window
 */

#include "GUI.h"

// Include event class
#include "Event.h"

// Include Research Information
#include "ProjectInfo.h"

/**
 * @brief   Constructor for GUI view creates a graphics
 *          window for SwinGame
 */
GUI::GUI(float refRate)
{
    open_graphics_window("Cat Mouse", 800, 600);
    load_default_colors();
    
    // Fresh new screen
    clear_screen(ColorBlack);
    
    // Display initialising message
    draw_simple_text("===     C A T   M O U S E     ===", ColorGreen, 240, 400);
    draw_simple_text(PROJECT_DESC,                        ColorRed,   3  , 3  );
    draw_simple_text("*** INITIALISING ***",              ColorWhite, 300, 440);
    draw_simple_text("Refer to console",                  ColorWhite, 320, 460);
    
    // Draw logo
    draw_bitmap(load_bitmap("meow.png"), 200, 100);
    
    // Refresh screen to update changes
    refresh_screen();

    // Init refresh rate and timer
    _refreshRate = refRate;
    _refreshTimer = create_timer();
    start_timer(_refreshTimer);
}

/**
 * @brief   Clears and refreshes the screen by the
 *          time given in reset timer
 */
void GUI::process_screen()
{
    if (timer_ticks(_refreshTimer) > _refreshRate * 1000)
    {
        reset_timer(_refreshTimer);
        clear_screen(ColorWhite);
    }
    // HUD
    fill_rectangle(ColorBlack, -1, -1, screen_width()+1, 30);
    draw_simple_text(PROJECT_DESC, ColorWhite, 3, 3);
    draw_framerate(3, 13);
    refresh_screen();
}

/**
 * @brief   Processes events by drawing only Game events
 *          onto the screen given the Game event is about
 *          an Animal
 * @param   eData
 *          Event Data to process
 */
void GUI::process_event(Event *eData)
{
    
    // Get the eventData to work with
    map<string, string> eventData = eData->get_data();

    // Initiate *iterator* (not keys) for the data
    auto src = eventData.find("Source");
    auto character = eventData.find("Character");
    
    // Only process events where keys src and character are found
    if (src != eventData.end() && character != eventData.end())
    {
        // Only process events for Network (other player) and Game (this player)
        if (src->second == "Network" || src->second == "Game")
        {
            // 2D vector to work with
            int x = 0;
            int y = 0;

            // Default Color Black for shapes until we change
            // to cat/mouse parsing below
            color shapeColor = ColorBlack;
            
            // For every item in the event
            for (auto i = eventData.begin(); i != eventData.end(); ++i)
            {
                // Get the x value for this Animal
                if (i->first == "x")
                {
                    // x is == to the value for this key
                    x = atoi(i->second.c_str());
                }
                // Get the y value for this Animal
                if (i->first == "y")
                {
                    // y is == to the value for this key
                    y = atoi(i->second.c_str());
                }
                // Process the colors for this Animal
                if (i->first == "Character")
                {
                    // Red for cat characters
                    if (i->second == "Cat")
                    { shapeColor = ColorRed; }
                    // Blue for mouse characters
                    if (i->second == "Mouse")
                    { shapeColor = ColorBlue; }
                }
            }
            // Finally, draw the shapes on the screen
            fill_circle(shapeColor, x, y, 15);
            // Draw whose cat and whose mouse with their initials
            char initials[8] = {character->second.at(0), ' ', ' ', ' ', ' ', ' ', ' '};
            draw_simple_text(initials, ColorWhite, x - 10, y - 2);
        }
    }
}