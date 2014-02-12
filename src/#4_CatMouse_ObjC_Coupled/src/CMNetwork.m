/**
 * @class   CMNetwork
 * @author  Alex Cummaudo
 * @date    22 Oct 2013
 * @brief   Packages up data recieved from the controller
 *          and passes it to a given network.
 */

// Include SwinGame Framework
#include "SwinGame.h"

// Include my header
#import "CMNetwork.h"

// Include game model class
#import "CMGame.h"

@implementation CMNetwork

/**
 * @brief   Constructor initiates a connection
 *          as a host
 * @param   gameModel
 *          The game model to link to and update
 * @return  The self class pointer
 */
-(id) initAsHostInGame:(id)gameModel
{
    // Close all former connections
    [SGNetworking closeAllConnections];
    [SGNetworking closeAllSockets];
    
    // Initilaise my game model to param
    _gameModel = gameModel;
    
    if (self = [super init])
    {
        // Generate random number for network ID
        // This is a workaround for SwinGame's my_IP
        // function---my_IP just returns localhost
        // 127.0.0.1, which is the same for every PC
        _networkID = [NSString stringWithFormat:@"%d", [SGUtils rndUpto:2048]];
        NSLog(@"Network ID set to %@", _networkID);
        
        // Initialise with connection initialiser
        _ctn = [self newConnectionAsHost];
    }
    return self;
}

/**
 * @brief   Constructor initiates a connection
 *          to a given ip address (as a client)
 * @param   ipAddr
 *          The IP Address of the host this client
 *          will connect to
 * @param   gameModel
 *          The game model to link to and update
 * @return  The self class pointer
 */
-(id) initAsClientWithIPAddress:(NSString*) ipAddr inGame:(CMGame*)gameModel
{
    // Close all former connections
    [SGNetworking closeAllConnections];
    [SGNetworking closeAllSockets];
    
    // Initilaise my game model to param
    _gameModel = gameModel;
    
    if (self = [super init])
    {
        // Generate random number for network ID
        // This is a workaround for SwinGame's my_IP
        // function---my_IP just returns localhost
        // 127.0.0.1, which is the same for every PC
        _networkID = [NSString stringWithFormat:@"%d", [SGUtils rndUpto:2048]];
        NSLog(@"Network ID set to %@", _networkID);
        
        // Initialise with connection initialiser
        _ctn = [self newConnectionAsClientWithIPAddress:ipAddr];
    }
    return self;
}

/**
 * @brief   Destructor sends goodbye message and
 *          asks CMEventManager to forget about
 *          me and closes all connections
 */
-(void) dealloc
{
    [self sendMessageWithString:@"Message:Goodbye,"];
    
    [SGNetworking closeAllConnections];
    [SGNetworking closeAllSockets];
 
    [super dealloc];
}


/**
 * @brief   Gets connection status
 * @return  YES on a connection with another machine or NO when not
 */
-(BOOL) isConnected
{
    if (_ctn != nil) return YES;
    else return NO;
}

/**
 * @brief   The timeout connection; runs the passed function success on
 *          a success, and error function on error; allow passing of two
 *          block objects can be passed in as parameters to the timeout.
 * @param   msgPrompt
 *          Prompt message announced when timeout begins (i.e., why we're having
 *          a timeout).
 * @param   msgSucc
 *          Message announced when timeout did not run out and the break condition
 *          was met
 * @param   msgFail
 *          Message announced when timeout did ran out of timeoutSecs and the
 *          break condition was never met
 * @param   timeoutSecs
 *          How long to run timeout for
 * @param   countdownBody
 *          Function to run every second on timeout
 * @param   breakCondition
 *          Function that returns a bool to check whether or not the timeout
 *          should break
 */
-(void) timeoutWithPrompt:(NSString*)msgPrompt
           successMessage:(NSString*)msgSuc
           failureMessage:(NSString*)msgFail
           timeoutSeconds:(int)timeoutSecs
    countdownBodyFunction:(void (^)()) countdownBody
           breakCondition:(BOOL (^)()) breakCondition
{
   
    // Create and start timeout timer
    SGTimer *timeout = [SGTimer createWithId:create_timer()];
    [timeout start];
    
    NSLog(@"%@: A timeout will occur after %d seconds.", msgPrompt, timeoutSecs);
    
    // While timeout is less than timeoutSecs * 1000 (in s)
    while ([timeout ticks] < timeoutSecs * 1000)
    {
        // Run the countdownBody and check to break
        countdownBody();
        if (breakCondition())
        {
            NSLog(@"SUCCESS! %@", msgSuc);
            return;
        }
    }

    // Outside while loop means a fail
    NSLog(@"FAILURE! %@", msgFail);
    
}
/**
 * @brief   Initiates the connection as a host, returning true
 *          or false on a success or error
 * @return  A new host connection to work with
 */
-(SGConnection*) newConnectionAsHost
{
    //! Define newConnection as __block to allow access to the
    __block SGConnection *newConnection = nil;
    
    // Setup a host port at 25585
    BOOL hostOk = [SGNetworking createTCPHost:25585];
    // If creating the host was not successful...
    if (!hostOk)
    {
        NSLog(@"%@ %@",
              @"Couldn't create open port at port 25585.",
              @"Ensure nothing else is using that port!");
    }
    
    // On each timeout countdown, accept TCP connections while we wait (Obj-C Blocks)
    void (^countdownBody )() = ^() {[SGNetworking acceptTCPConnection];};
    
    // Break timeout condition when we get a connection (Obj-C Blocks)
    BOOL (^breakCondition)() = ^()
    {
        // The new connection from outside this block is now the fetched connection
        newConnection = [SGNetworking fetchConnection];
        // Return true/false from block obj. on existance of connection
        if (newConnection != nil)
        {
            //! Force break condition to be true
            return YES;
        }
        else return NO;
    };

    // Pass everything to timeout
    [self timeoutWithPrompt:@"Waiting for client to connect"
             successMessage:@"A client has connected!"
             failureMessage:@"No clients connected."
             timeoutSeconds:30
      countdownBodyFunction:countdownBody
             breakCondition:breakCondition];
    
    return newConnection;
}

/**
 * @brief   Initiates the connection as a client, returning true or false
 *          on a success or error
 * @param   ipAddr
 *          IP Address that this client should connect to
 * @return  A new client connection to work with
 */
-(SGConnection*) newConnectionAsClientWithIPAddress:(NSString *) ipAddr
{
    __block SGConnection *newConnection = nil;
    
    // On each timeout countdown, accept TCP connections while we wait (Obj-C blocks)
    void (^countdownBody )() = ^() { /* do nothing */ };
    
    // Break timeout condition when we get a connection (Obj-C blocks)
    BOOL (^breakCondition)() = ^()
    {
        // The new connection from outside this block is now the fetched ctn
        newConnection = [SGNetworking createTCPConnection:ipAddr
                                                                port:25585];
        // Return true/false from block obj. on existance of connection
        if (newConnection != nil)
        {
            //! Force break condition to be true
            return YES;
        }
        else return NO;
    };
    
    // Pass everything to timeout
    [self timeoutWithPrompt:[NSString stringWithFormat:@"Attempting to connect to %@" ,ipAddr]
             successMessage:[NSString stringWithFormat:@"Successfully connected to %@",ipAddr]
             failureMessage:[NSString stringWithFormat:@"Couldn't connect to %@",      ipAddr]
             timeoutSeconds:10
      countdownBodyFunction:countdownBody
             breakCondition:breakCondition];
    
    return newConnection;
}

/**
 * @brief   Process messages that are being recieved (i.e.
 *          incoming network string to event)
 */
-(void) processMessages
{
    NSString* msg;
    
    // Process only if still connected
    if (self.isConnected)
    {
        if ([SGNetworking tCPMessageReceived])
        {
            msg = [_ctn readLastMessage];
            
            /**
             * @note    Messages recieved in the format:
             *              key:value,key:value, etc.
             *          Hence we want to parse the msg back
             *          into its event kind
             */
            
            NSArray *allKeyValuePairs = [msg componentsSeparatedByString: @","];
            
            // Declare a dict for event we're going to create from this message
            NSMutableDictionary* msgData = [[NSMutableDictionary alloc] init];
            
            // For every key:value Pair
            for (id pair in allKeyValuePairs)
            {
                // Given pair is not blank
                if (![pair  isEqual: @""])
                {
                    // Get every component separated by a tile m
                    NSArray *keyAndValueForThisPair = [pair componentsSeparatedByString: @":"];
                    
                    // At 0 = key
                    NSString *key = [keyAndValueForThisPair objectAtIndex:0];
                    // At 1 = value
                    NSString *value = [keyAndValueForThisPair objectAtIndex:1];
                    
                    // Insert the key/value pair from this pair
                    [msgData setObject:value forKey:key];
                }
            }

            // Set the network id of the other message
            NSString *incomingNetworkID = [msgData objectForKey:@"Network-ID"];
            
            /*
             * PARSE THROUGH DATA TO UPDATE MODEL AS REQUIRED
             */
            
            // Given im not about to process my own message
            if (![incomingNetworkID isEqual:_networkID])
            {
                /*
                 * GOODBYE MESSAGE
                 */
                if ([[msgData objectForKey:@"Message"] isEqual: @"Goodbye"])
                {
                    NSLog(@"Other player disconnected");
                          
                    // Kill my connection to end the game
                    _ctn = nil;

                    // Don't use eventData
                    [msgData release];

                    // Don't push the disconnection event
                    return;
                }
                
                /*
                 * UPDATE OTHER PLAYER COORD
                 */
                id x = [msgData objectForKey:@"x"];
                id y = [msgData objectForKey:@"y"];
                
                // Given x/y was in message
                if (x != nil && y != nil)
                {
                    // Ask model to update the other player
                    [_gameModel updateOtherPlayerToX:[x intValue] andY:[y intValue]];
                }
                
            }
            
            [msgData release];
            
            // Clear all messages
            [_ctn clearMessageQueue];
        }
    }
}

/**
 * @brief   Sends a string over the network by packaging it and sending
 *          it over the network as a string (i.e. an outgoing event
 *          to a network string)
 * @param   msg
 *          String to send over the network
 */
 -(void) sendMessageWithString:(NSString*) msg
{
    // Process only if still connected
    if (self.isConnected)
    {
        NSMutableString *data = [NSMutableString stringWithString:msg];
        
        // Append the network id to this message to be sent
        [data appendFormat:@"Network-ID:%@,", _networkID];
        
        // SwinGame API returns the connection on a failed sent message
        if ([_ctn sendTCPMessage:data] == _ctn)
        {
            NSLog(@"Cannot send a message! Check connection!");
        }
    }
}
@end