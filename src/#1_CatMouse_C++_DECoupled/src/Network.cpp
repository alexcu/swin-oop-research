/**
 * @class   Network View
 * @author  Alex Cummaudo
 * @date    7 Oct 2013
 * @brief   Packages up data recieved from the controller
 *          and passes it to a given network.
 */

// Include SwinGame Framework
#include "SwinGame.h"

// Include my header
#include "Network.h"

// Include used classes
#include "EventManager.h"

// Include event class
#include "Event.h"


/**
 * @brief   Constructor initiates a connection
 *          as a host
 */
Network::Network()
{
    // Close all former connections
    close_all_connections();
    close_all_sockets();
    
    // Make _ctn a nullptr until created as a connection
    _ctn = nullptr;
    
    // Generate random number for network ID
    // This is a workaround for SwinGame's my_IP
    // function---my_IP just returns localhost
    // 127.0.0.1, which is the same for every PC
    int idVal = rnd_upto(2048);
    _networkID = to_string(idVal);
    this->announce_event("Network ID set to "+_networkID);
    
    // Initialise with connection initialiser
    _ctn = this->new_connection();
}

/**
 * @brief   Constructor initiates a connection
 *          to a given ip address (as a client)
 * @param   ipAddr
 *          The IP Address of the host this client
 *          will connect to
 */
Network::Network(string ipAddr)
{
    // Close all former connections
    close_all_connections();
    close_all_sockets();
    
    // Make _ctn a nullptr until created as a connection
    _ctn = nullptr;
    
    // Generate random number for network ID
    // This is a workaround for SwinGame's my_IP
    // function---my_IP just returns localhost
    // 127.0.0.1, which is the same for every PC
    int idVal = rnd_upto(2048);
    _networkID = to_string(idVal);
    this->announce_event("Network ID set to "+_networkID);
    
    // Initialise with connection initialiser
    _ctn = this->new_connection(ipAddr);
}

/**
 * @brief   Destructor closes all connections
 *          and announces Goodbye message
 */
Network::~Network()
{
    this->announce_event("Goodbye");
    
    close_all_connections();
    close_all_sockets();
}

/**
 * @brief   The timeout connection; runs the passed function success on
 *          a success, and error function on error; allow passing of two
 *          functors so that lambda expressions can be passed in as parameters
 *          to the timeout.
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
void Network::timeout(string msgPrompt,
                      string msgSucc,
                      string msgFail,
                      int timeoutSecs,
                      function<void(void)> countdownBody,
                      function<bool(void)> breakCondition)
{
    // Create and start timeout timer
    timer timeout = create_timer();
    start_timer(timeout);
    
    // New stringstream for messages to announce
    stringstream message;
    message << msgPrompt << ": A timeout will occur after " << timeoutSecs << " seconds.";
    
    this->announce_event(message.str());
    
    // While timeout is less than timeoutSecs * 1000 (in s)
    while (timer_ticks(timeout) < timeoutSecs * 1000)
    {
        // Run the countdownBody and check to break
        countdownBody();
        if (breakCondition()) { this->announce_event("SUCCESS! "+msgSucc); return; }
    }
    // Outside while loop means a fail
    this->announce_event("FAILURE! "+msgFail);
}

/**
 * @brief   Initiates the connection as a host, returning true
 *          or false on a success or error
 * @return  A new host connection to work with
 */
connection Network::new_connection()
{
    connection newConnection = NULL; //@todo: null may break!
    
    // Create a host port at 25585
    bool hostOk = create_tcphost(25585);
    // If creating the host was not successful...
    if (!hostOk)
    {
        this->announce_event
        ("Couldn't create open port at port 25585. Ensure nothing else is using that port!");
    }
    
    // Otherwise, call timeout and...
    else
    {
        // On each timeout countdown, accept TCP connections while we wait (C++ Lambdas)
        auto const countdownBody     = []{accept_tcpconnection();};
        
        // Break timeout condition when we get a connection (C++ Lambdas)
        auto const breakCondition    = [&newConnection]
        {
            // Attempt to fetch a client connection
            newConnection =  fetch_connection();
            // Return true/false from lambda expr. on existance of connection
            if (newConnection != nullptr)
            {
                //! Force break condition to be true
                return true;
            }
            else return false;

        };
        // Pass everything to timeout
        this->timeout("Waiting for client to connect",
                      "A client has connected!",
                      "No clients connected.",
                      30, countdownBody, breakCondition);
    }
    
    return newConnection;
    
}

/**
 * @brief   Initiates the connection as a client, returning true or false
 *          on a success or error
 * @param   ip_addr
 *          IP Address that this client should connect to
 * @return  A new client connection to work with
 */
connection Network::new_connection(string ip_addr)
{
    connection newConnection = NULL;
    
    // Do nothing on each timeout countdown (C++ Lambdas)
    auto const countdownBody = []{ /* do nothing */ };
    
    // Break timeout condition when we get a connection (C++ Lambdas)
    auto const breakCondition = [&newConnection, &ip_addr]
    {
        // Attempt to create a connection
        newConnection = create_tcpconnection(ip_addr.c_str(), 25585);
        // Return true/false from lambda expr. on existance of connection
        if (newConnection != nullptr) return true; else return false;
    };
    // Pass everything to timeout
    this->timeout("Attempting to connect to " + ip_addr,
                  "Successfully connected to " + ip_addr,
                  "Couldn't connect to " + ip_addr,
                  10, countdownBody, breakCondition);
    
    return newConnection;
}

/**
 * @brief   Process messages that are being recieved (i.e.
 *          incoming network string to an outgoing event)
 */
void Network::process_messages()
{
    string msg     = "";
    // Process only if still connected
    if (this->is_connected())
    {
        if (tcpmessage_received())
        {
            // SwinGame's recieve_message() may be broken?
            // It always returned a NULL; this works though...
            msg = _ctn->first_msg->data;
            
            /**
             * @note    Messages recieved in the format:
             *              key:value,key:value| etc.
             *          Hence we want to parse the msg back
             *          into its event kind
             */
            
            // Declare a section string and stringstream of the message to parse
            string sect;
            stringstream streamKey(msg);
            
            // Declare a map for event we're going to create from this message
            map<string, string> eventData;
            
            // Get key
            while ( getline(streamKey, sect, ',') )
            {
                // Chop off everything after the : in the key
                string key = sect.substr(0, sect.find(":"));
                
                stringstream streamValue(sect);
                string value;
                
                // Get value for this key
                while ( getline(streamValue, sect, ':') )
                {
                    value = sect;
                }
                
                // Lastly, insert the key and value
                eventData.insert(pair<string, string>(key, value));
                
            }
            
            // Push to eventData to say this event originated from the network view
            eventData["Source"] = "Network";
            eventData["Network-ID"] = _networkID;
            
            // Before we push event, check if it was a goodbye message
            if (eventData.find("Message")->second == "Goodbye")
            {
                announce_event("Other player disconnected");
                
                // Kill my connection to end the game
                _ctn = nullptr;
                
                // Don't push disconnection event
                return;
            }
            
            // Push an event out with this information
            Event* result = new Event(eventData);
            
            // Notify publishers of the new result
            EventManager::publish_event(result);
            
            // Clear all messages
            clear_message_queue(_ctn);
            
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
void Network::process_event(Event *eData)
{
    // Only process where a connection is established
    if (this->is_connected())
    {
        stringstream data;
        
        map<string, string> eventData = eData->get_data();
        
        // For every key/value pair in the event data map
        for (auto i = eventData.begin(); i != eventData.end(); ++i)
        {
            // Push data out as key:value, pairs
            data << i->first << ":" << i->second << ",";
            
            // If this network message has originated from myself
            // there is a KeyDown message for this event (i.e. from myself)
            if ((i->first == "Network-ID" && i->second == _networkID) ||
                (i->first == "KeyDown"))
            {
                // Stop processing this event and ignore it
                return;
            }
        }
        
        const char *msgChar = data.str().c_str();
        
        // SwinGame API returns the connection on a failed sent message
        // (and announce couldn't send given that there is a connection)
        if (send_tcpmessage(msgChar, _ctn) == _ctn)
        {
            this->announce_event("Cannot send a message! Check connection!");
        }
    }
}

/**
 * @brief   Sends an event to all subscribers with the given message
 * @param   msg
 *          Message to announce when creating an Event
 */
void Network::announce_event(string msg)
{
    map<string, string> eventData;
    
    // Push to eventData to say this event originated from the network view
    eventData["Message"] = msg;
    eventData["Source"] = "Network";
    
    // Push an event out with this information
    Event *event = new Event(eventData);
    
    // Notify publishers of the new event
    EventManager::publish_event(event);
}
