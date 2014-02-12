# Balancing Design with Performance (Research Article) - CatMouse Target

- Research conducted as a part of Swinburne University unit HIT2302 Object Oriented Programming.
- This project includes the source included as a part of the research paper - _Balancing Design with Performance_
- Research article: [https://www.dropbox.com/s/rx0puf7xqfj9829/2013-S2-ResearchPaper.pdf](https://www.dropbox.com/s/rx0puf7xqfj9829/2013-S2-ResearchPaper.pdf)

## Synopsis

This project includes the source of the target that was tested and analysed as a part of the research undertaken in HIT2302. There are four components:

- decoupled class design implemented in C++
- decoupled class design implemented in Objective-C
- coupled class design implemented in C++
- coupled class design implemented in Objective-C

Attached also includes the analysis reports recorded in Xcode's instruments testing tools used for assessing system performance, the results of which are discussed in the paper.

### SwinGame

This project makes use of the [SwinGame](http://swingame.com/) SDK.

## Screenshots

![](http://imgur.com/Q9PrAtz.png)

## Sample Output
__Note:__ The following output was captured from a connection between a Loosely Coupled CatMouse target in C++ (v1) compared to a Loosely Coupled CatMouse target in Obj-C (v2)

````
*** EVENT OCCURED ***
{
    Message: Welcome to Cat Mouse - C++ - Loosely Coupled Classes (#1)
    Source: Main
}
2014-02-12 14:29:21.199 CatMouse[3084:507] 
*** EVENT OCCURED ***
{
    Message: Are you hosting? [y/n]
    Source: Main
}
^C2014-02-12 14:29:25.066 CatMouse[3084:507] 
*** EVENT OCCURED ***
{
    Message: Network ID set to 474
    Source: Network
}
2014-02-12 14:29:25.066 CatMouse[3084:507] 
*** EVENT OCCURED ***
{
    Message: Waiting for client to connect: A timeout will occur after 30 seconds.
    Source: Network
}
2014-02-12 14:29:55.066 CatMouse[3084:507] 
*** EVENT OCCURED ***
{
    y: 10
    Time: 0.00
    Message: Game started! You're the Cat
    x: 200
    Source: Game
    Character: Cat
}
*** EVENT OCCURED ***
{
    Character: Mouse
    Message: Game started! You're the Mouse
    Network-ID: 570
    Source: Network
    Time: 0.00
    x: 600
    y: 545
}
*** EVENT OCCURED ***
{
    KeyDown: right_key
    Source: Keyboard
}
*** EVENT OCCURED ***
{
    Character: Cat
    Message: Animal Moved
    Source: Game
    Time: 20.079000
    x: 203
    y: 369
}
*** EVENT OCCURED ***
{
    Character: Mouse
    Message: Animal Moved
    Network-ID: 570
    Source: Network
    Time: 25.55
    x: 138
    y: 344
}
*** EVENT OCCURED ***
{
    Message: Other player disconnected
    Source: Network
}
*** EVENT OCCURED ***
{
    Message: Goodbye
    Source: Network
}
*** EVENT OCCURED ***
{
    Character: Cat
    Message: Game has ended at 466s
    Source: Game
    Time: 466.528992
    x: 275
    y: 498
}
````

## Usage

Run a target using the `./run.sh` command. Select one of the designs as mentioned above. 

__Note:__ Two networked computers must be connected and running the game (any version) for the game to run.

## Copyright Notice

Copyright &copy; Alex Cummaudo 2014. All rights reserved.