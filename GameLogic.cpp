#include<cstdlib>
#include<ctime>
#include"GameLogic.h"
#include"string"
#include<iostream>
#include"Stack.h"
#include<utility>

USING_NS_CC;
using namespace ui;
using namespace std;
int num = 0;
bool secondTime = false;
Card* c1 = nullptr;
Card* c2 = nullptr;
Button* btn1 = nullptr;
Button* btn2 = nullptr;
Button* undo_btn = nullptr;
Label* chess = nullptr;
Table* Table::mIns = nullptr;
LinkedStack<Button*> loca;
#define SCORE 4
Card::Card() {
	m_iIndex = num++;
}

Table::Table() {
	srand(time(nullptr));
	time_counter = 0;
	move_counter = 0;
	mIns = this;
	m_iRow = 5;
	m_iColumn = 5;
	c1 = nullptr;
	c2 = nullptr;
	m_iCorrectCnt = 0;

	m_cCardCnt = new Card*[m_iRow];
	for (int i = 0; i < m_iRow; i++) {
		m_cCardCnt[i] = new Card[m_iColumn];
	}
}

bool Table::init() {
	if (!Layer::init()) {
		return false;
	}

	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			swap(m_cCardCnt[i][j], m_cCardCnt[rand() % m_iRow][rand() % m_iColumn]);
		}
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Undo Button
	undo_btn = Button::create();
	undo_btn->setTitleText("Undo");
	undo_btn->setTitleFontSize(35);
	undo_btn->setVisible(false);
	undo_btn->addTouchEventListener(CC_CALLBACK_2(Table::undoBtnTouch, Table::mIns));
	undo_btn->setTitleColor(Color3B::RED);
	undo_btn->setPosition(Vec2(435,300));
	this->addChild(undo_btn, 1);

	//卡片 O必定先手
	m_CardBtn = new Button**[m_iRow];
	for (int i = 0; i < m_iRow ; i++) {
		m_CardBtn[i] = new Button*[m_iColumn];
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j] = Button::create("1.1.png");
			m_CardBtn[i][j]->setPosition(Vec2(origin.x + 100 + j * 65, origin.y + visibleSize.height - 35 - i * 62));
			m_CardBtn[i][j]->addTouchEventListener(CC_CALLBACK_2(Table::CardBtnTouch, Table::mIns));
			m_CardBtn[i][j]->setVisible(false);
			m_CardBtn[i][j]->setUserData(&m_cCardCnt[i][j]);
			this->addChild(m_CardBtn[i][j], 5);
		}
	}

	return true;
}
/**/
void Table::CardBtnTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		btn1 = (Button*)sender;
		undo_btn->setEnabled(true);
		
		btn1->setEnabled(false);
		if (move_counter != 11)
		{
			if (time_counter < 2 && move_counter % 2 == 1)
			{
				btn1->setTitleText("X");
				btn1->setTitleColor(Color3B::BLACK);
			}
			else if (time_counter < 2 && move_counter % 2 != 1)
			{
				btn1->setTitleText("O");
				btn1->setTitleColor(Color3B::RED);
			}
			else if (time_counter >= 2 && move_counter % 2 != 1)
			{
				btn1->setTitleText("X");
				btn1->setTitleColor(Color3B::BLACK);
				time_counter = 0;
				move_counter++;
			}
			else if (time_counter >= 2 && move_counter % 2 == 1)
			{
				btn1->setTitleText("O");
				btn1->setTitleColor(Color3B::RED);
				time_counter = 0;
				move_counter++;
			}
		}
		else
		{
			btn1->setTitleText("X");
			btn1->setTitleColor(Color3B::BLACK);
			if (time_counter == 2)
				this->whowin();
		}
		btn1->setTitleFontSize(60);
		btn1->setTitleFontName("fonts/arial.ttf");
		time_counter++;
		loca.push(btn1);
	}
}
void Table::undoBtnTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		btn2 = (Button*)sender;
		if (loca.isEmpty())
		{
			btn2->setEnabled(false);
			return;
		}
		//btn2->setEnabled(false);
		loca.peek()->setTitleText("");
		loca.peek()->setEnabled(true);
		if (time_counter >= 1) {
			time_counter--;
			loca.pop();
		}
		else if (move_counter >= 1)
		{
			move_counter--;
			time_counter = 1;
			loca.pop();
		}
	}
}
void Table::whowin(){
	int lineNum = 0;
	int numInLine;
	for (int i = 0; i<m_iRow; ++i) {
		numInLine = 0;
		for (int j = 0; j<m_iColumn; ++j) {
			numInLine += (m_CardBtn[i][j]->getTitleText() == "O");
			if (numInLine == SCORE) {
				lineNum++;
				break;
			}
		}
		numInLine = 0;
		for (int j = 0; j<m_iColumn; ++j) {
			numInLine += (m_CardBtn[j][i]->getTitleText() == "O");
			if (numInLine == SCORE) {
				lineNum++;
				break;
			}
		}
	}
	numInLine = 0;
	for (int i = 0; i<m_iRow; ++i) {
		numInLine += (m_CardBtn[i][i]->getTitleText() == "O");
		if (numInLine == SCORE) {
			lineNum++;
			break;
		}
	}
	numInLine = 0;
	for (int i = 0; i<< m_iRow; ++i) {
		numInLine += (m_CardBtn[i][m_iRow - 1 - i]->getTitleText() == "O");
		if (numInLine == SCORE) {
			lineNum++;
			break;
		}
	}
	int O_S = lineNum;
	lineNum = 0;
	for (int i = 0; i<m_iRow; ++i) {
		numInLine = 0;
		for (int j = 0; j<m_iColumn; ++j) {
			numInLine += (m_CardBtn[i][j]->getTitleText() == "X");
			if (numInLine == SCORE) {
				lineNum++;
				break;
			}
		}
		numInLine = 0;
		for (int j = 0; j<m_iColumn; ++j) {
			numInLine += (m_CardBtn[j][i]->getTitleText() == "X");
			if (numInLine == SCORE) {
				lineNum++;
				break;
			}
		}
	}
	numInLine = 0;
	for (int i = 0; i<m_iRow; ++i) {
		numInLine += (m_CardBtn[i][i]->getTitleText() == "X");
		if (numInLine == SCORE) {
			lineNum++;
			break;
		}
	}
	numInLine = 0;
	for (int i = 0; i << m_iRow; ++i) {
		numInLine += (m_CardBtn[i][m_iRow - 1 - i]->getTitleText() == "X");
		if (numInLine == SCORE) {
			lineNum++;
			break;
		}
	}
	int X_S = lineNum;
	startPVPGame(false);
	if (O_S > X_S) {
		MyUI::mIns->setTitleWord("O Win!!");
	}
	else if(O_S < X_S) {
		MyUI::mIns->setTitleWord("X Win!!");
	}
	else {
		MyUI::mIns->setTitleWord("Draw");
	}
	MyUI::mIns->setSubtitleWord("Congratulations~");
	MyUI::mIns->setStartBtnWord("Again?");
	MyUI::mIns->visAllTitle(true);
	MyUI::mIns->visAllBtn(true);
}
void Table::startPVPGame(bool swi) {
	time_counter = 0;
	move_counter = 0;
	while (!loca.isEmpty())
		loca.pop();
	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j]->setVisible(swi);
			undo_btn->setVisible(swi);
			m_CardBtn[i][j]->setEnabled(swi);
			m_CardBtn[i][j]->setTitleText("");
		}
	}
}
void Table::startPVCGame(bool swi) {
	time_counter = 0;
	move_counter = 0;
	while (!loca.isEmpty())
		loca.pop();
	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j]->setVisible(swi);
			undo_btn->setVisible(swi);
			m_CardBtn[i][j]->setEnabled(swi);
			m_CardBtn[i][j]->setTitleText("");
		}
	}
}
void Table::UpdateTimer(float dt) {
	if (c1->m_iIndex / 2 == c2->m_iIndex / 2) {
		m_iCorrectCnt++;

		if (win()) {
			m_iCorrectCnt = 0;
			startPVPGame(false);
			MyUI::mIns->setTitleWord("You Win!!");
			MyUI::mIns->setSubtitleWord("Congratulations~");
			MyUI::mIns->setStartBtnWord("Again?");
			MyUI::mIns->visAllTitle(true);
			MyUI::mIns->visAllBtn(true);
		}
	}
	else {
		btn1->setEnabled(true);
		btn2->setEnabled(true);
	}
	TouchEnabledAllCardBtn(true);
}

void Table::TouchEnabledAllCardBtn(bool ena) {
	for (int i = 0; i < m_iRow; i++) {
		for (int j = 0; j < m_iColumn; j++) {
			m_CardBtn[i][j]->setTouchEnabled(ena);
		}
	}
}

bool Table::win() {
	if (m_iCorrectCnt == m_iRow * m_iColumn / 2)
		return true;
	else
		return false;
}