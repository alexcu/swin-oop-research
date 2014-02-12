/**
 * @class   GUI View
 * @author  Alex Cummaudo
 * @date    2 Nov 2013
 * @brief   Provides GUI View for the game
 *          to display the game on in a graphics
 *          window
 */

#include "GUI.h"

// Include animal class
#include "Animal.h"

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
 * @brief   Draws the given animal to the screen
 * @param   animal
 *          Animal to draw to the screen
 */
void GUI::draw_animal(Animal *animal)
{
    // 2D vector to work with
    int x = animal->get_position()->x;
    int y = animal->get_position()->y;
    
    // Default Color Black for shapes until we change
    // to cat/mouse parsing below
    color shapeColor = ColorBlack;
    
    // Get the name of the animal
    string type = animal->get_name();
    
    // Red for cat characters
    if (type == "Cat")
    { shapeColor = ColorRed; }
    // Blue for mouse characters
    if (type == "Mouse")
    { shapeColor = ColorBlue; }
    
    // Finally, draw the shapes on the screen
    fill_circle(shapeColor, x, y, 15);
    // Draw whose cat and whose mouse with their initials
    char initials[8] = {type.at(0), ' ', ' ', ' ', ' ', ' ', ' '};
    draw_simple_text(initials, ColorWhite, x - 10, y - 2);
}