# [[Reversi](project3-reversi.pdf)]
## A two-person network game of Reversi with text-based user interface:
* using the Ncurses library for TUI
* using socket for network communication

### Reversi
• A turn-based board game with an 8x8 square board, and black and white 
stones

## Dependency
* [Ncurses](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html)
	* Installation command: ```$ sudo apt-get install libncurses5-dev libncursesw5-dev```

## Command Sequence: Steps to build and run the program.
### Server Side
1. ```$ make```
2. ```$ cd ./bin/```
3. ```$ ./server <port>```

### Client 1 Side
1. ```$ make```
2. ```$ cd ./bin/```
3. ```$ ./client <ip address> <port>```

### Client 2 Side
1. ```$ make```
2. ```$ cd ./bin/```
3. ```$ ./client <ip address> <port>```