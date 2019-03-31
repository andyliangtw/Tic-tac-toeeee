#include "MyUI.h"
#include "Game.h"

MyUI* MyUI::mIns = nullptr;

bool MyUI::init() {
	if (!Layer::init()) {
		return false;
	}

	ccColor4B color = ccc4(0, 248, 248, 255);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景色
	CCLayerColor *color_layer = CCLayerColor::create(color);
	this->addChild(color_layer, 1);

	//標題
	mTitle = Label::createWithTTF("Tic-tac-toeeee", "fonts/consola.ttf", 60);
	mTitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - mTitle->getContentSize().height - 20));
	this->addChild(mTitle, 1);

	//副標題
	mSubtitle = Label::createWithTTF("Group 4 Produced", "fonts/consola.ttf", 14);
	mSubtitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - 135));
	mSubtitle->setColor(Color3B::BLACK);
	this->addChild(mSubtitle, 1);
	
	//PVP
	mBtnStartP = Button::create();
//	mBtnStartP->setZoomScale(-0.4f);
	mBtnStartP->setTitleText("v.s. People");
	mBtnStartP->setTitleFontName("fonts/arial.ttf");
	mBtnStartP->setTitleFontSize(24);
	mBtnStartP->setTitleColor(Color3B::RED);
	mBtnStartP->setPosition(Vec2(origin.x + visibleSize.width / 2,
						origin.y + visibleSize.height / 2 - 20));
	mBtnStartP->addTouchEventListener(CC_CALLBACK_2(MyUI::StartBtnPTouch, MyUI::mIns));
	this->addChild(mBtnStartP, 1);

	//PVC
	mBtnStartC = Button::create();
//	mBtnStartC->setZoomScale(-0.4f);
	mBtnStartC->setTitleText("v.s. Computer");
	mBtnStartC->setTitleFontName("fonts/arial.ttf");
	mBtnStartC->setTitleFontSize(24);
	mBtnStartC->setTitleColor(Color3B::RED);
	mBtnStartC->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 60));
	mBtnStartC->addTouchEventListener(CC_CALLBACK_2(MyUI::StartBtnCTouch, MyUI::mIns));
	this->addChild(mBtnStartC, 1);

	//結束鍵
	mBtnQuit = Button::create();
	mBtnQuit->setTitleText("Quit");
	mBtnQuit->setTitleFontName("fonts/arial.ttf");
	mBtnQuit->setTitleFontSize(24);
	mBtnQuit->setTitleColor(Color3B::RED);
	mBtnQuit->setPosition(Vec2(origin.x + visibleSize.width / 2,
						origin.y + visibleSize.height / 2 - 100));
	mBtnQuit->addTouchEventListener(CC_CALLBACK_2(MyUI::QuitBtnTouch, MyUI::mIns));
	this->addChild(mBtnQuit, 1);
	
	return true;
}

void MyUI::StartBtnPTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		visAllBtn(false);
		visAllTitle(false);
		Game::mIns->startPVP(0);
	}
	else {
	}
}

void MyUI::StartBtnCTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		visAllBtn(false);
		visAllTitle(false);
		Game::mIns->startPVC(0);
	}
	else {
	}
}

void MyUI::QuitBtnTouch(Ref* sender, Widget::TouchEventType event_type) {
	if (event_type == Widget::TouchEventType::ENDED) {
		Director::getInstance()->end();
	}
	else {
	}
}

void MyUI::visAllBtn(bool vis) {
	mBtnStartP->setVisible(vis);
	mBtnStartC->setVisible(vis);
	mBtnQuit->setVisible(vis);
}

void MyUI::visAllTitle(bool vis) {
	mTitle->setVisible(vis);
	mSubtitle->setVisible(vis);
}

void MyUI::setTitleWord(string str) {
	mTitle->setString(str);
}

void MyUI::setSubtitleWord(string str) {
	mSubtitle->setString(str);
}

void MyUI::setStartBtnWord(string str) {
	mBtnStartP->setTitleText(str);
}