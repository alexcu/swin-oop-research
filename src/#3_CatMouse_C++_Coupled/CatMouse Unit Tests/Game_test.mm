/**
 * @test    Game Unit Tests
 * @author  Alex Cummaudo
 * @date    18 Oct 2013
 * @brief   Unit tests for Network
 */


#import <XCTest/XCTest.h>

#import "Game.h"
#import "Log.h"
#import "Keyboard.h"
#import "EventManager.h"

@interface Game_test : XCTestCase
{
    // Create some views and model
    Game     *_game;
    Keyboard *_keyView;
    Log      *_logView;
}

@end

@implementation Game_test

- (void)setUp
{
    [super setUp];
    
    // Create a SwinGame window
    open_graphics_window("Kill Shot", 600, 400);
    
    // Construct the EventManager (static class!)
    EventManager::EventManager();
    
    // Construct the Log
    _logView = new Log(true);
    
    // Construct the keyboard
    _keyView = new Keyboard();
    
    // Construct the Game
    _game = new Game(true);
    
    // The only subscriber in this unit test is the log
    EventManager::add_subscriber(_logView);

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
    }
    while (!window_close_requested());
}

@end
