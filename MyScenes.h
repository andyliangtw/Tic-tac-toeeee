#ifndef _MY_SCENES_H_
#define _MY_SECNES_H_
#include"cocos2d.h"
#include"ui\UIButton.h"
#include"string"
USING_NS_CC;
using namespace std;

class MyScenes : public cocos2d::Layer {
public:
	static MyScenes* mIns;
public:
	MyScenes() {
		mIns = this;
	}
	~MyScenes() {
		mIns = nullptr;
	}
	virtual bool init();
	void GameStart();
private:
};

#endif