#ifndef _MY_UI_h_
#define _MY_UI_h_
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "ui\UIButton.h"
USING_NS_CC;
using namespace ui;
using namespace std;

class MyUI : public cocos2d::Layer {
public:
	static MyUI* mIns;
public:
	MyUI() : m_iScore(0) {
		mIns = this;
	}
	~MyUI() {
		mIns = nullptr;
	}

	virtual bool init();
	void StartBtnPTouch(Ref* sender, Widget::TouchEventType event_type);
	void StartBtnCTouch(Ref* sender, Widget::TouchEventType event_type);
	void QuitBtnTouch(Ref* sender, Widget::TouchEventType event_type);
	void visAllBtn(bool vis);
	void visAllTitle(bool vis);
	void setTitleWord(string str);
	void setSubtitleWord(string str);
	void setStartBtnWord(string str);
private:
	int m_iScore;
	Label* mTitle;
	Label* mSubtitle;
	Button* mBtnStartP;
	Button* mBtnStartC;
	Button* mBtnQuit;
};
#endif