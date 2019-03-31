#include "Game.h"

AI* com = nullptr;
Button* btn1 = nullptr;
Button* btn2 = nullptr;

//public function
Game::Game() :
	gameStatus(CREATE),
	playerNum(2),
	size(5),
	stepMax(size*size),
	whoTurn(0),
	whoWin(0),
	board(new board_t*[size]),
	players(new void*[playerNum])
{
	mIns = this;
	for (int i = 0; i < size; ++i) {
		board[i] = new board_t[size];
	}
	cleanBoard();
}

Game::Game(int _playerNum, int _size) :
    gameStatus(CREATE),
	playerNum(_playerNum),
	size(_size),
	stepMax(_size*_size),
    whoTurn(0),
    whoWin(0),
    board(new board_t*[_size]),
	players(new void*[_playerNum])
{
	mIns = this;
	for (int i = 0; i < size; ++i) {
		board[i] = new board_t[size];
    }
    cleanBoard();
}

Game::~Game()
{
	for (int i = 0; i < size; ++i) {
        delete[] board[i];
		delete[] mSqrBtn[i];
    }
    delete[] board;
    delete[] players;
	delete[] mSqrBtn;
	delete mUndoBtn;
}

bool Game::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Square Button
	mSqrBtn = new Button**[size];
	for (int i = 0; i < size; i++) {
		mSqrBtn[i] = new Button*[size];
		for (int j = 0; j < size; j++) {
			mSqrBtn[i][j] = Button::create("1.1.png");
			mSqrBtn[i][j]->setPosition(Vec2(origin.x + 100 + j * 65, origin.y + visibleSize.height - 35 - i * 62));
			mSqrBtn[i][j]->addTouchEventListener(CC_CALLBACK_2(Game::SqrBtnTouch, Game::mIns));
			mSqrBtn[i][j]->setVisible(false);
			mSqrBtn[i][j]->setUserData(&board[i][j]);
			this->addChild(mSqrBtn[i][j], 5);
		}
	}

	// Undo Button
	mUndoBtn = Button::create();
	mUndoBtn->setTitleText("Undo");
	mUndoBtn->setTitleFontSize(35);
	mUndoBtn->setVisible(false);
	mUndoBtn->addTouchEventListener(CC_CALLBACK_2(Game::UndoBtnTouch, Game::mIns));
	mUndoBtn->setTitleColor(Color3B::RED);
	mUndoBtn->setPosition(Vec2(435, 300));
	this->addChild(mUndoBtn, 1);

	return true;
}

void Game::SqrBtnTouch(Ref * sender, Widget::TouchEventType event_type)
{
	if (event_type == Widget::TouchEventType::ENDED) {
		btn1 = (Button*)sender;
		mUndoBtn->setEnabled(true);

		btn1->setEnabled(false);
		if (whoTurn == 0) {

		}
	}
	else {
	}
}

void Game::startPVP(int _whoTurn=-1) {
    if(gameStatus == END) {
        cleanBoard();
        while(!allSteps.isEmpty())
			allSteps.pop();
    }
    assert(gameStatus == INITIAL);
    gameStatus = START;
    if(_whoTurn == -1) {
        srand(time(nullptr));
		whoTurn = rand() % playerNum;
    }
	else {
		assert(_whoTurn > -1 && _whoTurn < playerNum);
        whoTurn = _whoTurn;
    }

	mUndoBtn->setVisible(true);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mSqrBtn[i][j]->setVisible(true);
		}
	}
    return;
}

void Game::startPVC(int _whoTurn=-1)
{
	if (gameStatus == END) {
		cleanBoard();
		while (!allSteps.isEmpty())
			allSteps.pop();
	}
	assert(gameStatus == INITIAL);
	gameStatus = START;
	if (_whoTurn == -1) {
		srand(time(nullptr));
		whoTurn = rand() % playerNum;
	}
	else {
		assert(_whoTurn > -1 && _whoTurn < playerNum);
		whoTurn = _whoTurn;
	}

	mUndoBtn->setVisible(true);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mSqrBtn[i][j]->setVisible(true);
		}
	}
	com = new AI(this);
	return;
}

void Game::move(int _x, int _y){
	assert(gameStatus == START);
    assert(allSteps.size() < stepMax);
    if(board[_x][_y] != NONE){
        throw Invalid_Position("The position is already in use.");
    }
    step_t aStep(whoTurn, cordin(_x, _y));
    allSteps.push(aStep);
    board[_x][_y] = whoTurn;
    if(allSteps.size() == stepMax - 1){
        for(int i=0;i < size;++i){
            for(int j=0;j < size;++j){
                if(board[i][j] == NONE){
                    board[i][j] = whoTurn;
                    goto exit;
                }
            }
        }
        exit:
        whoWin = 0;
        int maxLine = getLinesOf(whoWin);
        for(int i=1;i < playerNum;++i){
            int curLine = getLinesOf(i);
            if(maxLine < curLine){
                maxLine = curLine;
                whoWin = i;
            }
        }
        gameStatus = END;
    }
}

int Game::nextTurn(){
    whoTurn = (whoTurn + 1)%playerNum;
    return whoTurn;
}

int** Game::getBoard(){
    assert(gameStatus != CREATE);
    return board;
}

const steps_t& Game::getAllSteps() const{
    return allSteps;
}

bool Game::undo(){
    if(!allSteps.isEmpty()){
        step_t aStep = allSteps.peek();
        int x = aStep.ss.ff, y = aStep.ss.ss;
        assert(board[x][y] != NONE);
        board[x][y] = NONE;
        whoTurn = aStep.ff;
        allSteps.pop();
        return true;
    }
    return false;
}    

int Game::getWinner(){
    assert(gameStatus==END);
    return whoWin;
}

step_t Game::getCurStep(){
    assert(gameStatus==START || gameStatus==END);
    return allSteps.peek();
}

int Game::getLinesOf(int player){
    int lineNum = 0;
    int numInLine;
    for(int i=0;i<size;++i){
        numInLine = 0;
        for(int j=0;j<size;++j){
            numInLine += (board[i][j] == player);
            if(numInLine == SCORE){
                lineNum++;
                break;
            }
        }
        numInLine = 0;
		for (int j = 0; j < size; ++j) {
            numInLine += (board[j][i] == player);
            if(numInLine == SCORE){
                lineNum++;
                break;
            }
        }
    }
    numInLine = 0;
	for (int i = 0; i < size; ++i) {
        numInLine += (board[i][i] == player);
        if(numInLine == SCORE){
            lineNum++;
            break;
        }
    }
    numInLine = 0;
	for (int i = 0; i < size; ++i) {
        numInLine += (board[i][size - 1 - i] == player);
        if(numInLine == SCORE){
            lineNum++;
            break;
        }
    }
    return lineNum;
}

int Game::getWhoTurn(){
    return whoTurn;
}

// private function
void Game::cleanBoard(){
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			board[i][j] = NONE;
        }
    }
    gameStatus = INITIAL;
}
