/**
 * @test    GUI Unit Tests
 * @author  Alex Cummaudo
 * @date    18 Oct 2013
 * @brief   Unit tests for Network
 */


#import <XCTest/XCTest.h>

#import "Game.h"
#import "GUI.h"
#import "Keyboard.h"
#import "EventManager.h"

@interface GUI_test : XCTestCase
{
    // Create some views and model
    Game     *_game;
    Keyboard *_keyView;
    GUI      *_guiView;
    
}

@end

@implementation GUI_test

- (void)setUp
{
    [super setUp];
    
    // Construct the EventManager (static class!)
    EventManager::EventManager();
    
    // Construct the GUI
    _guiView = new GUI(1.5);
    
    // Construct the Game
    _game = new Game(true);
    
    // Construct keyboard
    _keyView = new Keyboard();
    
    // The only publisher in this unit test is the log and keyboard
    EventManager::add_subscriber(_guiView);
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)test_publish_movement
{
    // Run the `game' while not quit key pressed
    do
    {
        _keyView->process_keyboard();
        _guiView->process_screen();
    }
    while (!window_close_requested());
}

@end
