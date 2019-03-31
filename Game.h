#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <stdexcept>
#include <utility>
#include "ui\UIButton.h"
#include "Stack.h"
#include "MyUI.h"
#include "AI.h"
USING_NS_CC;
using namespace ui;
using namespace std;

#define IOE InvalidOperationException
#define InvalidOperationException range_error
#define Invalid_Position invalid_argument

// some type definition
typedef LinkedStack<Button*> steps_t;

typedef int board_t;

// public function

// Game::Game(int _playerNum=2, int _size=5)
// create game with `_playerNum` players and `_size`*`_size` board 
// set `gameStatus` CREATE, and immediately set it INITIAL by call `cleanBoard`

// void Game::addPlayer(_player_t& aPlayer)
// unfinished feature, just skip

// void Game::start(int _whoTurn=-1)
// determine game start with `_whoTurn` turn, default as random

// void Game::move(int _x, int _y)
// place chess at position(_x, _y).
// If position status is not NONE, arise `Invalid_Position` exception.

// int Game::nextTurn()
// turn `whoTurn` to next player
// return `whoTurn`

// int** Game::getBoard()
// return current game board as a 2-dimension integer array.
// each entry represent which player own the entry.
// If nobody own the entry, it is NONE, defined as -1.

// const steps_t& Game::getAllSteps() const
// return all steps in past.

// bool Game::undo()
// undo last step, update board immediately.
// If success, return true; otherwise, false.

// int Game::getWinner()
// return the player that win the game.
// It can only call when the `gameStatus` is END

// step_t Game::getCurStep()
// return current step position in pair<int, int> form

// int Game::getLinesOf(int player)
// return lines of `player` in current game

// int Game::getWhoTurn()
// return whose turn

enum GameStatus {
	CREATE = 0,
	INITIAL = 2,
	START = 3,
	END = 4,
	NONE = -1,
	SCORE = 4
};

class Game : public cocos2d::Layer
{
private:
	GameStatus  gameStatus;
	int         playerNum; // default = 2
	int         size; // size*size, ex:5*5
	int         stepMax; // = size*size
	int         whoTurn;
	int         whoWin;
	steps_t     allSteps; // a stack that stores all steps
	board_t**   board;
	void**      players;
	Button***	mSqrBtn;
	Button*		mUndoBtn;
	
	// private member functions
	void        cleanBoard();
public:
	static Game* mIns;
	Game();
	Game(int _playerNum, int _size);
	~Game();

	virtual bool init();

	void startPVP(int _whoTurn);
	void startPVC(int _whoTurn);
	void SqrBtnTouch(Ref* sender, Widget::TouchEventType event_type);
	void UndoBtnTouch(Ref* sender, Widget::TouchEventType event_type);
	void move(int _x, int _y);
	int nextTurn();
	bool undo();
	int getWinner();
	int** getBoard();
	const steps_t& getAllSteps() const;
	step_t getCurStep();
	int getLinesOf(int player);
	int getWhoTurn();
};

#endif // !_GAME_H_
