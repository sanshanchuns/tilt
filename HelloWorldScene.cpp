#include "HelloWorldScene.h"
#include "VisibleRect.h"

USING_NS_CC;

#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)        \
_pos = _min;        \
else if (_pos > _max)   \
_pos = _max;        \

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    //添加事件
    layer->addMoveObject();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = LabelTTF::create("Hello World", "Arial", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Point(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
    
    //add background
    
    auto background = Sprite::create("background-568h.jpg");
    background->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    addChild(background);
    
    _isFirstLaunch = true;
    
//    addMushroom();
    
    return true;
}

void HelloWorld::addMushroom(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto mushroom1 = Sprite::create("mushroom128.png");
    mushroom1->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + mushroom1->getContentSize().height));
    addChild(mushroom1, 0);
    
    auto mushroom2 = Sprite::create("mushroom128.png");
    mushroom2->setPosition(Point(visibleSize.width/2 + origin.x - mushroom2->getContentSize().width, visibleSize.height/2 + origin.y));
    addChild(mushroom2, 0);
    
    auto mushroom3 = Sprite::create("mushroom128.png");
    mushroom3->setPosition(Point(visibleSize.width/2 + origin.x + mushroom3->getContentSize().width, visibleSize.height/2 + origin.y));
    addChild(mushroom3, 0);
    
    
}

void HelloWorld::addMoveObject(){
    
    Device::setAccelerometerEnabled(true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("mushroom128.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto listener = EventListenerAcceleration::create([=](Acceleration* acc, Event* event){
        
        if (_isFirstLaunch) {
            wait(1);
            _isFirstLaunch = false;
        }
        
        auto ballSize  = sprite->getContentSize();
        
        auto ptNow  = sprite->getPosition();
        
        //        log("acc: x = %lf, y = %lf", acc->x, acc->y);
        
        ptNow.x += acc->x * 9.81f * 0.5;
        ptNow.y += acc->y * 9.81f * 0.5;
        
        FIX_POS(ptNow.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
        FIX_POS(ptNow.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
        sprite->setPosition(ptNow);
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
    
}

//sleep for t seconds
void HelloWorld::wait(int t)
{
    std::chrono::milliseconds dura( t * 1000 );
    std::this_thread::sleep_for( dura );
}
//void HelloWorld::onEnter(){
//    
//    Point origin = Director::getInstance()->getVisibleOrigin();
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    
//    Device::setAccelerometerEnabled(true);
//    
//    auto sprite = Sprite::create("mushroom.png");
//    sprite->setPosition(origin + Point(visibleSize.width/2, visibleSize.height/2));
//    addChild(sprite, 1);
//    
//    auto listener = EventListenerAcceleration::create([=](Acceleration* acc, Event* event){
//        auto ballSize  = sprite->getContentSize();
//        
//        auto ptNow  = sprite->getPosition();
//        
//        log("acc: x = %lf, y = %lf", acc->x, acc->y);
//        
//        ptNow.x += acc->x * 9.81f;
//        ptNow.y += acc->y * 9.81f;
//        
//        FIX_POS(ptNow.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
//        FIX_POS(ptNow.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
//        sprite->setPosition(ptNow);
//    });
//    
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
//    
//}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
