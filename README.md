# Tic-tac-toeeee
Final Project of "Data Structures and Advanced Program Design" in 106-2, taught by Professor Chien Chin Chen and Professor Ling-Chieh Kung.  
## Description & Rules
This is a different version of "Tic-tac-toe".  
There is a 5x5 table (different from original 3x3 table), and every player can select **2** places to put his/her mark(O/X) every round.  
Since there's 25 places, the player who is in the defensive position(select places after the other player) can get the No.23, 24, 25 places.  
For example, O starts. After 11 rounds, there are 22 places selected and 3 places remain unmarked, and it's X's round. So X would get the last 3 places.  
For 5 rows, 5 columns, and 2 diagonals, if there're at least 4 same marks in the 5 places, the player who use that mark would get 1 point.  
The one who get higher point wins. (if the points are the same, the game ended in a tie.  

## How-to build the game
This game is developed by cocos2d, and here are source codes instead of released executive files. So, if you want to play this game, you have to download [Cocos2d-x](https://cocos2d-x.org/download) and settle the developing environment.
Here I won't teach you how to set the environment, sorry for the inconvenience. Please Google it by yourself.

First Written in 2019/04/06
Updated in 2019/04/06
