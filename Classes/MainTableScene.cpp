//
//  MainTableScene.cpp
//  Technopoly
//
//  Created by Олег Ермаков on 11.05.15.
//
//

#include "MainTableScene.h"
USING_NS_CC;
Scene* MainTable::createScene()
{
    auto scene = Scene::create();
    auto layer = MainTable::create();
    
    scene->addChild(layer);
    Director::getInstance()->getTextureCache()->addImage("1.png");
    Director::getInstance()->getTextureCache()->addImage("2.png");
    Director::getInstance()->getTextureCache()->addImage("3.jpg");
    Director::getInstance()->getTextureCache()->addImage("4.jpg");
    Director::getInstance()->getTextureCache()->addImage("5.jpg");
    Director::getInstance()->getTextureCache()->addImage("6.jpg");
    return scene;
}

//
bool MainTable::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    //размеры окна
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //для объединения карточек
    table = Node::create();
    table->setContentSize(Size(visibleSize.height, visibleSize.height));
    table->setPosition(Vec2(origin.x + table->getContentSize().width/2, origin.y + table->getContentSize().height/2));
    table->setAnchorPoint(Vec2(0.5,0.5));
    createTable(table);
    //закрывающее меню
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainTable::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    //рандом
    boost::random::mt11213b rng;
    unsigned int seed = 0;
    rng.seed((++seed) + time(NULL));
    boost::random::uniform_int_distribution<> six(1,6);
    int random_num1 = six(rng);

    cube1 = Sprite::create("1.png");
    switch (random_num1) {
        case (2): cube1 = Sprite::create("2.png"); break;
        case (3): cube1 = Sprite::create("3.jpg"); break;
        case (4): cube1 = Sprite::create("4.jpg"); break;
        case (5): cube1 = Sprite::create("5.jpg"); break;
        case (6): cube1 = Sprite::create("6.jpg"); break;
        default: break;
    }
    
    // position the sprite on the center of the screen
    
    int random_num2 = six(rng);
    
    cube2 = Sprite::create("1.png");
    switch (random_num2) {
        case (2): cube2 = Sprite::create("2.png"); break;
        case (3): cube2 = Sprite::create("3.jpg"); break;
        case (4): cube2 = Sprite::create("4.jpg"); break;
        case (5): cube2 = Sprite::create("5.jpg"); break;
        case (6): cube2 = Sprite::create("6.jpg"); break;
        default: break;
    }
    
    float MenuWidth = visibleSize.width - (table->getPosition().x + table->getContentSize().width/2);
    
    
    auto StepButtonLabel = Label::createWithTTF("Сделать ход", "isotextpro/PFIsotextPro-Regular.ttf", 34);
    StepButtonLabel -> setColor(Color3B::BLACK);
    auto StepButton = MenuItemLabel::create(StepButtonLabel, CC_CALLBACK_1(MainTable::onStepQlick, this));
    StepButton->setPosition(Vec2(table->getPosition().x + table->getContentSize().width/2 + MenuWidth/2,
                              origin.y + visibleSize.height/2));
    
    
    //направо, налево
    auto RotateRight = Label::createWithTTF("Направо", "isotextpro/PFIsotextPro-Regular.ttf", 34);
    RotateRight -> setColor(Color3B::BLACK);
    auto RotateRightButton = MenuItemLabel::create(RotateRight, CC_CALLBACK_1(MainTable::onRotateRight, this));
    RotateRightButton->setPosition(Vec2(table->getPosition().x + table->getContentSize().width/2 + MenuWidth/2,
                                 origin.y + visibleSize.height/2 - StepButton->getContentSize().height - 5));
    
    auto RotateLeft = Label::createWithTTF("Налево", "isotextpro/PFIsotextPro-Regular.ttf", 34);
    RotateLeft -> setColor(Color3B::BLACK);
    auto RotateLeftButton = MenuItemLabel::create(RotateLeft, CC_CALLBACK_1(MainTable::onRotateLeft, this));
    RotateLeftButton->setPosition(Vec2(table->getPosition().x + table->getContentSize().width/2 + MenuWidth/2,
                                        origin.y + visibleSize.height/2 - StepButton->getContentSize().height - RotateRightButton->getContentSize().height - 10));

    
    
    Vector<MenuItem*> MenuItems;
    MenuItems.pushBack(StepButton);
    MenuItems.pushBack(closeItem);
    MenuItems.pushBack(RotateRightButton);
    MenuItems.pushBack(RotateLeftButton);
  //  menu->setPosition(Vec2::ZERO);
    
    auto sprite = Sprite::create("paper.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);

    
    cube1->setPosition(Vec2(table->getPosition().x + table->getContentSize().width/2 + MenuWidth/2 + cube1->getContentSize().width,
                            origin.y + visibleSize.height - cube1->getContentSize().height));
    
    
    cube2->setPosition(Vec2(table->getPosition().x + table->getContentSize().width/2 + MenuWidth/2 - cube2->getContentSize().width,
                            origin.y + visibleSize.height - cube2->getContentSize().height));
    
    
    this->addChild(cube2, 1);
    this->addChild(cube1, 1);
    
    this->addChild(sprite, 0);
    this->addChild(table,1);
    this->addChild(menu, 2);
   // this->addChild(lol,2);
    return true;
}

void MainTable::onStepQlick(Ref *pSender)
{
    rng.seed((++seed) + time(NULL));
    boost::random::uniform_int_distribution<> six(1,6);
    
    random_num1 = six(rng);
    random_num2 = six(rng);
    
    std::string string_random_num1= std::to_string(random_num1);
    std::string string_random_num2= std::to_string(random_num2);

    
    cube1 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("1.png"));
    switch (random_num1) {
        case (2): cube1 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("2.png")); break;
        case (3): cube1 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("3.jpg")); break;
        case (4): cube1 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("4.jpg")); break;
        case (5): cube1 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("5.jpg")); break;
        case (6): cube1 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("6.jpg")); break;
        default: break;
    }
    
    cube2 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("1.png"));
    switch (random_num2) {
        case (2): cube2 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("2.png")); break;
        case (3): cube2 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("3.jpg")); break;
        case (4): cube2 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("4.jpg")); break;
        case (5): cube2 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("5.jpg")); break;
        case (6): cube2 -> setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("6.jpg")); break;
        default: break;
    }
}

void MainTable::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainTable::onRotateRight(Ref* pSender)
{
    float current_rotation = table->getRotation();
    table->setRotation(current_rotation + 90);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainTable::onRotateLeft(Ref* pSender)
{
    float current_rotation = table->getRotation();
    table->setRotation(current_rotation - 90);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void MainTable::createTable(Node* Table)
{
    auto visibleSize = Table->getContentSize();
    std::string name = "";
    for(int i = 0; i < 40; i++)
    {
        name = std::to_string(i);
        cards[i] = Sprite::create("cards/" + name + ".jpg");
    }
    
    //первая карта
    cards[0]->setAnchorPoint(Vec2(0.5,0.5));
    auto size_card = cards[0]->getContentSize();
    float height_k = size_card.width/visibleSize.width;
    cards[0]->setScale(1/(height_k*Height_K));
    cards[0]->setPosition(Vec2(visibleSize.width - cards[0]->getContentSize().width/(2*(height_k*Height_K)),
                           cards[0]->getContentSize().height/(2*(height_k*Height_K))));
    
    //нижний ряд
    addLeft(cards[1], cards[0]->getContentSize().width/(2*height_k*Height_K), cards[0]->getPosition(), visibleSize);
    for(int i = 2; i <= 10; i++)
        addLeft(cards[i], cards[i-1]->getContentSize().width/(2*height_k*Height_K), cards[i-1]->getPosition(), visibleSize);
    
    //левый ряд
    addTop(cards[11], cards[10]->getContentSize().height/(2*height_k*Height_K), cards[10]->getPosition(), visibleSize);
    for(int i = 12; i <= 20; i++)
        addTop(cards[i], cards[i-1]->getContentSize().width/(2*height_k*Height_K), cards[i-1]->getPosition(), visibleSize);
    
    //верхний ряд
    addRight(cards[21], cards[20]->getContentSize().width/(2*height_k*Height_K), cards[20]->getPosition(), visibleSize);
    for(int i = 22; i <= 30; i++)
        addRight(cards[i], cards[i-1]->getContentSize().width/(2*height_k*Height_K), cards[i-1]->getPosition(), visibleSize);
    
    //правый ряд
    addBottom(cards[31], cards[30]->getContentSize().height/(2*height_k*Height_K), cards[30]->getPosition(), visibleSize);
    for(int i = 32; i < 40; i++)
        addBottom(cards[i], cards[i-1]->getContentSize().width/(2*height_k*Height_K), cards[i-1]->getPosition(), visibleSize);
    
    auto BaseSprite = Sprite::create("cards/Base.jpg");
    BaseSprite->setAnchorPoint(Vec2(0.5,0.5));
    size_card = BaseSprite->getContentSize();
    height_k = size_card.width/visibleSize.width;
    BaseSprite->setScale(1/(height_k));
    BaseSprite->setPosition(Vec2(visibleSize.width/2,
                               visibleSize.height/2));
    
    for(int i = 0; i < 40; i++)
    {
    Table->addChild(cards[i],2);
    }
    Table->addChild(BaseSprite);
    

}

void MainTable::addTop(Node* spr, float position_delta, Vec2 old_position, Size table)
{
    float k = spr->getContentSize().height/table.height;
    auto new_width = spr->getContentSize().width/(k * Height_K);
    
    spr->setPosition(old_position.x, old_position.y + position_delta + new_width/2);
    spr->setRotation(90);
    spr->setAnchorPoint(Vec2(0.5,0.5));
    spr->setScale(1/(k*Height_K));
}

void MainTable::addRight(Node* spr, float position_delta, Vec2 old_position, Size table)
{
    float k = spr->getContentSize().height/table.height;
    auto new_width = spr->getContentSize().width/(k * Height_K);
    
    spr->setPosition(old_position.x + position_delta + new_width/2, old_position.y);
    spr->setRotation(180);
    spr->setAnchorPoint(Vec2(0.5,0.5));
    spr->setScale(1/(k*Height_K));
}

void MainTable::addLeft(Node* spr, float position_delta, Vec2 old_position, Size table)
{
    float k = spr->getContentSize().height/table.height;
    auto new_width = spr->getContentSize().width/(k * Height_K);
    
    spr->setPosition(old_position.x - position_delta - new_width/2, old_position.y);
    spr->setRotation(0);
    spr->setAnchorPoint(Vec2(0.5,0.5));
    spr->setScale(1/(k*Height_K));}

void MainTable::addBottom(Node* spr, float position_delta, Vec2 old_position, Size table)
{
    float k = spr->getContentSize().height/table.height;
    auto new_width = spr->getContentSize().width/(k * Height_K);
    
    spr->setPosition(old_position.x, old_position.y - position_delta - new_width/2);
    spr->setRotation(270);
    spr->setAnchorPoint(Vec2(0.5,0.5));
    spr->setScale(1/(k*Height_K));}