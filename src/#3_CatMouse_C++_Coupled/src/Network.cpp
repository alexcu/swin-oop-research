/**
 * @class   Network View
 * @author  Alex Cummaudo
 * @date    2 Nov 2013
 * @brief   Packages up data recieved from the controller
 *          and passes it to a given network.
 */

// Include SwinGame Framework
#include "SwinGame.h"

// Include my header
#include "Network.h"

// Include game model class
#include "Game.h"


/**
 * @brief   Constructor initiates a connection
 *          as a host
 * @param   gameModel
 *          The game model to link to and update
 */
Network::Network(Game *gameModel)
{
    // Close all former connections
    close_all_connections();
    close_all_sockets();
    
    // Initilaise my game model to param
    _gameModel = gameModel;
    
    // Make _ctn a nullptr until created as a connection
    _ctn = nullptr;
    
    // Generate random number for network ID
    // This is a workaround for SwinGame's my_IP
    // function---my_IP just returns localhost
    // 127.0.0.1, which is the same for every PC
    int idVal = rnd_upto(2048);
    _networkID = to_string(idVal);
    cout << "Network ID set to " << _networkID << endl;
    
    // Initialise with connection initialiser
    _ctn = this->new_connection();
}

/**
 * @brief   Constructor initiates a connection
 *          to a given ip address (as a client)
 * @param   gameModel
 *          The game model to link to and update
 * @param   ipAddr
 *          The IP Address of the host this client
 *          will connect to
 */
Network::Network(Game *gameModel, string ipAddr)
{
    // Close all former connections
    close_all_connections();
    close_all_sockets();
    
    // Initilaise my game model to param
    _gameModel = gameModel;
    
    // Make _ctn a nullptr until created as a connection
    _ctn = nullptr;
    
    // Generate random number for network ID
    // This is a workaround for SwinGame's my_IP
    // function---my_IP just returns localhost
    // 127.0.0.1, which is the same for every PC
    int idVal = rnd_upto(2048);
    _networkID = to_string(idVal);
    cout << "Network ID set to " << _networkID << endl;
    
    // Initialise with connection initialiser
    _ctn = this->new_connection(ipAddr);
}

/**
 * @brief   Destructor closes all connections
 *          and announces Goodbye message
 */
Network::~Network()
{
    this->send_message("Message:Goodbye,");
    
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
    cout << msgPrompt << ": A timeout will occur after " << timeoutSecs << " seconds." << endl;
    
    
    // While timeout is less than timeoutSecs * 1000 (in s)
    while (timer_ticks(timeout) < timeoutSecs * 1000)
    {
        // Run the countdownBody and check to break
        countdownBody();
        if (breakCondition()) { cout << "SUCCESS! " << msgSucc << endl; return; }
    }
    // Outside while loop means a fail
    cout << "FAILURE! " << msgFail << endl;
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
        cout <<
        "Couldn't create open port at port 25585. Ensure nothing else is using that port!"
        << endl;
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
 * @note    Any incoming messages that suggests changes to
 *          the model will do so directly here.
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
            map<string, string> msgData;
            
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
                msgData.insert(pair<string, string>(key, value));
                
            }
            
            // Set the network id of the other message
            string incomingNetworkID = msgData.find("Network-ID")->second;
            
            /*
             * PARSE THROUGH DATA TO UPDATE MODEL AS REQUIRED
             */
            
            // Given im not about to process my own message
            if (incomingNetworkID != _networkID)
            {
                /*
                 * GOODBYE MESSAGE
                 */
                if (msgData.find("Message")->second == "Goodbye")
                {
                    cout << "Other player disconnected" << endl;
                    
                    // Kill my connection to end the game
                    _ctn = nullptr;
                    
                    // Don't push disconnection event
                    return;
                }
                /*
                 * UPDATE OTHER PLAYER COORD
                 */
                auto x = msgData.find("x");
                auto y = msgData.find("y");
                // Given x/y was in message
                if (x != msgData.end() && y != msgData.end())
                {
                    // Ask model to update the other player
                    _gameModel->update_other_player(stof(x->second), stof(y->second));
                }
            }
            
            // Clear all messages
            clear_message_queue(_ctn);
            
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
void Network::send_message(string msg)
{
    if (this->is_connected())
    {
        stringstream data;
        
        // Append the network id to this message to be sent
        data << msg << "Network-ID" << ":" << _networkID << ",";
        
        const char *msgChar = data.str().c_str();
        
        // SwinGame API returns the connection on a failed sent message
        // (and announce couldn't send given that there is a connection)
        if (send_tcpmessage(msgChar, _ctn) == _ctn)
        {
            cout << "Cannot send a message! Check connection!" << endl;
        }
    }
}
