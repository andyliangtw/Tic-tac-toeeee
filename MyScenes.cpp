#include<iostream>
#include"ui\UIButton.h"
//#include"MyScenes.h"
#include"MyUI.h"
#include"GameLogic.h"
#include"string"
USING_NS_CC;
using namespace ui;
using namespace std;

//MyScenes* MyScenes::mIns = nullptr;

bool MyScenes::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
}

void MyScenes::GameStart() {

}
