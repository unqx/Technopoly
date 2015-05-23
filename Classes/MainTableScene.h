//
//  MainTableScene.h
//  Technopoly
//
//  Created by Олег Ермаков on 11.05.15.
//
//

#ifndef __Technopoly__MainTableScene__
#define __Technopoly__MainTableScene__

#include "cocos2d.h"
#include "boost/random.hpp"
#include "Gameplay.h"

#define Height_K 7.3

class MainTable : public cocos2d::Layer
{
public:
    
    cocos2d::Sprite* cards [40];
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    //
    void createTable(cocos2d::Node* Table);
    void addRight(cocos2d::Node*, float, cocos2d::Vec2, cocos2d::Size k);
    void addLeft(cocos2d::Node*, float, cocos2d::Vec2, cocos2d::Size k);
    void addTop(cocos2d::Node*, float, cocos2d::Vec2, cocos2d::Size k);
    void addBottom(cocos2d::Node*, float, cocos2d::Vec2, cocos2d::Size k);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    cocos2d::Sprite* cube1;
    cocos2d::Sprite* cube2;
    
    boost::random::mt11213b rng;
    unsigned int seed = 0;
    
    int random_num1;
    int random_num2;

    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onStepQlick(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainTable);
};


#endif /* defined(__Technopoly__MainTableScene__) */