/**
 * @test    Network Unit Tests
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   Unit tests for Network
 */

#import <XCTest/XCTest.h>

#import "Network.h"
#import "Log.h"
#import "Event.h"
#import "EventManager.h"

@interface network_tests : XCTestCase
{
    Network *_netView;
    Log     *_logView;
}

@end

@implementation network_tests

- (void)setUp
{
    
    [super setUp];

    // Construct the EventManager (static class!)
    EventManager::EventManager();
    
    // Construct the Log
    _logView = new Log(true);
    
    // The only subscriber in this unit test is the log
    EventManager::add_subscriber(_logView);
    
    
    // Check if hosting
    string isHost;
    cout << "Are you hosting [y/n]? ";
    getline(cin, isHost);
    
    if (isHost == "n")
    {
        // Get IP Addr to connect to host
        string ipAddr;
        cout << "Enter IP Address: ";
        getline(cin, ipAddr);
        
        _netView = new Network(ipAddr);
    }
    else
    {
        // Setup connection as host
        _netView = new Network();
    }
}

- (void)tearDown
{
    [super tearDown];
    
    close_all_connections();
    close_all_sockets();
}

- (void)test_network_connection
{
    
    // Have to store in result since issues with
    // Obj-C++ and C++
    XCTAssertTrue(_netView->is_connected(), @"Error connecting to network");
    
}

- (void)test_simple_event
{
    // Setup message to send
    map<string, string> data;
    data["Message From Network"] = "Hello, world!";
    Event *test = new Event(data);
    
    // Send message 15 times
    const int ATTEMPTS = 5;
    for (int i = 0; i < ATTEMPTS; i++)
    {
        _netView->process_event(test);
        // Add random time for network jittering
        int delayTime = 500 + rnd_upto(1000);
        delay(delayTime);
        _netView->process_messages();
    }
    
    // NOTE THIS UNIT TEST WILL NOT HAVE AN ASSERT TEST
    // IT IS PURELY TO TEST NETWORK CONNECTIVITIY AND MESSGAGE
    // SENDING---ONLY THE TERMINAL LOG VIEW WILL PRINT ITS OUTPUT

}

@end