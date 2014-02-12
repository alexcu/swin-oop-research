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

// Include used classes
#include "CMEventManager.h"

// Include event class
#include "CMEvent.h"

@implementation CMNetwork

/**
 * @brief   Constructor initiates a connection
 *          as a host
 * @return  The self class pointer
 */
-(id) initAsHost
{
    // Close all former connections
    [SGNetworking closeAllConnections];
    [SGNetworking closeAllSockets];
    
    // Ask CMEventManager to start dealing with me
    [CMEventManager addSubscriber:self];
    
    if (self = [super init])
    {
        // Generate random number for network ID
        // This is a workaround for SwinGame's my_IP
        // function---my_IP just returns localhost
        // 127.0.0.1, which is the same for every PC
        _networkID = [NSString stringWithFormat:@"%d", [SGUtils rndUpto:2048]];
        [self announceEvent:[NSString stringWithFormat:@"Network ID set to %@", _networkID]];
        
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
 * @return  The self class pointer
 */
-(id) initAsClientWithIPAddress:(NSString *)ipAddr
{
    // Close all former connections
    [SGNetworking closeAllConnections];
    [SGNetworking closeAllSockets];
    
    // Ask CMEventManager to start dealing with me
    [CMEventManager addSubscriber:self];
    
    if (self = [super init])
    {
        // Generate random number for network ID
        // This is a workaround for SwinGame's my_IP
        // function---my_IP just returns localhost
        // 127.0.0.1, which is the same for every PC
        _networkID = [NSString stringWithFormat:@"%d", [SGUtils rndUpto:2048]];
        [self announceEvent:[NSString stringWithFormat:@"Network ID set to %@", _networkID]];
        
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
    [self announceEvent:@"Goodbye"];
    
    [SGNetworking closeAllConnections];
    [SGNetworking closeAllSockets];
 
    [CMEventManager forgetSubscriber:self];
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
    
    [self announceEvent:[NSString stringWithFormat:
                         @"%@: A timeout will occur after %d seconds.",
                         msgPrompt, timeoutSecs]];
    
    // While timeout is less than timeoutSecs * 1000 (in s)
    while ([timeout ticks] < timeoutSecs * 1000)
    {
        // Run the countdownBody and check to break
        countdownBody();
        if (breakCondition())
        {
            [self announceEvent:[NSString stringWithFormat:
                                 @"SUCCESS! %@",
                                 msgSuc]];
            return;
        }
    }

    // Outside while loop means a fail
    [self announceEvent:[NSString stringWithFormat:
                         @"FAILURE! %@",
                         msgFail]];
    
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
        [self announceEvent:[NSString stringWithFormat:@"%@ %@",
                             @"Couldn't create open port at port 25585.",
                             @"Ensure nothing else is using that port!"]];
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
            NSMutableDictionary* eventData = [[NSMutableDictionary alloc] init];
            
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
                    [eventData setObject:value forKey:key];
                }
            }
            
            // Declare source and network ID
            [eventData setObject:@"Network" forKey:@"Source"];
            [eventData setObject:_networkID forKey:@"Network-ID"];
            
            // Before we push event, check if it was a goodbye message
            if ([[eventData objectForKey:@"Message"] isEqual: @"Goodbye"])
            {
                [self announceEvent:@"Other player disconnected"];
                
                // Kill my connection to end the game
                _ctn = nil;
                
                // Don't use eventData
                [eventData release];
                
                // Don't push the disconnection event
                return;
            }
            
            // Push an event out with this information
            CMEvent *event = [[CMEvent alloc] initWithData:eventData];
            
            // Notify publishers of the new result
            [CMEventManager publishEvent:event];
            [event release];
            [eventData release];
            
            // Clear all messages
            [_ctn clearMessageQueue];
        }
    }
}

/**
 * @brief   Process the event data by packaging it and sending
 *          it over the network as a string (i.e. an outgoing event
 *          to a network string)
 * @param   eData
 *          Event Data to process
 */
-(void) processEvent:(CMEvent *)eData
{
    // Only process where a connection is established
    if ([self isConnected])
    {
        NSMutableString* data = [[NSMutableString alloc] init];
        
        // For every key/value pair in the event dictionary
        for (id key in eData.data)
        {
            // Push data out as key:value, pairs
            [data appendFormat:@"%@:%@,", key, [eData.data objectForKey:key]];
            
            // If this network message has originated from myself or
            // there is a KeyDown message for this event (i.e. from myself)
            if (([eData.data valueForKey:key] == _networkID) ||
                ([eData.data valueForKey:@"KeyDown"] != nil))
                
            {
                // Stop processing this event and ignore it
                [data release];
                return;
            }
        }
        
        // SwinGame API returns the connection on a failed sent message
        // (and announce couldn't send given that there is a connection)
        if ([_ctn sendTCPMessage:data] == _ctn)
        {
            [self announceEvent:@"Cannot send a message! Check connection!"];
        }
        
        // Release data
        [data release];
    }
}

/**
 * @brief   Sends an event to all subscribers with the given message
 * @param   message
 *          Message to announce when creating an Event
 */
-(void) announceEvent:(NSString *)message
{
    // Push an event out with msg information
    CMEvent *event = [[CMEvent alloc] initWithData:@{@"Message": message   ,
                                                     @"Source" : @"Network" }];
    
    // Notify publishers of the new event
    [CMEventManager publishEvent:event];
    
    [event release];
}

@end
