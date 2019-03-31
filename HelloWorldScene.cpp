#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui\UIButton.h"
#include "MyUI.h"
#include "Game.h"
USING_NS_CC;
using namespace ui;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    if (closeItem == nullptr ||
//        closeItem->getContentSize().width <= 0 ||
//        closeItem->getContentSize().height <= 0)
//    {
//        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
//    }
//    else
//    {
//        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;//x軸 (現在是右下)
//        float y = origin.y + closeItem->getContentSize().height/2;//y軸 (現在是右下)
//        closeItem->setPosition(Vec2(x,y));
//    }
//
    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

//    auto title = Label::createWithTTF("Card Memory", "fonts/Chalkduster.ttf", 60);
//    if (title == nullptr)
//    {
//        problemLoading("'fonts/Chalkduster.ttf'");
//    }
//    else
//    {
//        // position the label on the center of the screen
//		title->setPosition(Vec2(origin.x + visibleSize.width / 2,
//			origin.y + visibleSize.height - title->getContentSize().height - 20));
//
//        // add the label as a child to this layer
//        this->addChild(title, 1);
//    }

//	auto subtitle = Label::createWithTTF("Group 10 Produced", "fonts/Chalkduster.ttf", 14);
//	if (subtitle == nullptr)
//	{
//		problemLoading("'fonts/Chalkduster.ttf'");
//	}
//	else
//	{
		// position the label on the center of the screen
//		subtitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
//			origin.y + visibleSize.height - 130));
//		subtitle->setColor(Color3B::RED);
//		// add the label as a child to this layer
//		this->addChild(subtitle, 1);
//	}

    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//    if (sprite == nullptr)
//    {
//        problemLoading("'HelloWorld.png'");
//    }
//    else
//    {
//        // position the sprite on the center of the screen
//        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));//中間
//
//       // add the sprite as a child to this layer
//        this->addChild(sprite, 0);
//    }

	auto ui_interface = new MyUI;
	if (ui_interface->init() == false) {
		return false;
	}
	this->addChild(ui_interface, 2);

	auto ui_game = new Game;
	if (ui_game->init() == false) {
		return false;
	}
	this->addChild(ui_game, 2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}