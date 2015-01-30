#include "stdafx.h"
#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "BallButton.h"

using namespace cocos2d;

#define	TAG_BTM_BG		1000
#define	TAG_SHADOW		1001
#define	TAG_PAUSE		1002
#define	TAG_SILENT		1003
#define	TAG_PAUSE_I		1004
#define	TAG_SOUND_I		1005
#define	TAG_GAMEOVER_BG 1006
#define	TAG_GAMEOVER_IC 1007
#define	TAG_RESTART_BG  1008
#define	TAG_RESTART_IC  1009
#define	TAG_RETURN_BG   1010
#define	TAG_RETURN_IC	1011

void S_MainGame::initAnim(){
	// create solid color background
	auto bg = BallButton::create(E::C50);
	bg->setScale(0.3f);
	bg->setPosition(E::visibleWidth/2, 128+(-9/15.0f)*128);
	bg->setTag(TAG_BTM_BG);
	// add the wheel to the layer
	this->addChild(bg, 0);

	// create solid color background
	auto bgTop = LayerColor::create(C4B(E::C100));
	bgTop->setContentSize(Size(E::visibleWidth, E::visibleHeight*0.7));
	bgTop->setPosition(0, E::visibleHeight*0.3);
	this->addChild(bgTop, 0);


	auto pauseButton = BallButton::create(E::C700, E::C200, CC_CALLBACK_1(S_MainGame::menuCallback, this));
	pauseButton->setScale(0.15f);
	pauseButton->setPosition(0, E::visibleHeight * 0.5 );
	pauseButton->setTag(TAG_PAUSE);
	this->addChild(pauseButton, 1000);

	auto pauseIcon = Sprite::create("b_pause.png");
	pauseIcon->setScale(0.25f);
	pauseIcon->setPosition(E::visibleWidth-36, E::visibleHeight * 0.5);
	pauseIcon->setTag(TAG_PAUSE_I);
	pauseIcon->setOpacity(0);
	this->addChild(pauseIcon, 1000);

	auto silentButton = BallButton::create(E::C700, E::C200);
	silentButton->setScale(0.15f);
	silentButton->setPosition(0, E::visibleHeight * 0.5 - 80);
	silentButton->setTag(TAG_SILENT);
	this->addChild(silentButton, 1000);

	auto soundIcon = Sprite::create("b_sound.png");
	soundIcon->setScale(0.25f);
	soundIcon->setPosition(E::visibleWidth-36, E::visibleHeight * 0.5- 80);
	soundIcon->setTag(TAG_SOUND_I);
	soundIcon->setOpacity(0);
	this->addChild(soundIcon, 1000);
	
	// create the shadow
    auto shadow = Sprite::create("shadow.png");
    shadow->setScale(1.0f);
	shadow->setAnchorPoint(Vec2(0, 1));
	shadow->setScaleX(E::visibleWidth / DESIGNED_WIDTH);
	shadow->setPosition(0, E::visibleHeight * 0.3);
	shadow->setTag(TAG_SHADOW);
	shadow->setOpacity(0);
    this->addChild(shadow, 0);

	// game over background
	auto bgGameOver = BallButton::create(E::C700);
	bgGameOver->setTag(TAG_GAMEOVER_BG);
	bgGameOver->setScale(0.3f);
	bgGameOver->setPosition(E::visibleWidth/2, 0);
	bgGameOver->setVisible(false);
	this->addChild(bgGameOver, 1000);

	// game over icon
	auto gameOverIcon = Sprite::create("gameover.png");
	gameOverIcon->setScale(0.5f);
	gameOverIcon->setTag(TAG_GAMEOVER_IC);
	gameOverIcon->setPosition(E::visibleWidth/2, E::visibleHeight/2);
	gameOverIcon->setVisible(false);
	gameOverIcon->setOpacity(0);
	this->addChild(gameOverIcon, 1000);

	// restart background
	auto bgRestart = BallButton::create(E::C400, E::C200, CC_CALLBACK_1(S_MainGame::menuCallback, this));
	bgRestart->setTag(TAG_RESTART_BG);
	bgRestart->setScale(0.2f);
	bgRestart->setPosition(E::visibleWidth*0.3, 0);
	bgRestart->setVisible(false);
	this->addChild(bgRestart, 1000);

	// restart icon
	auto restartIcon = Sprite::create("b_restart.png");
	restartIcon->setScale(0.6f);
	restartIcon->setTag(TAG_RESTART_IC);
	restartIcon->setPosition(E::visibleWidth*0.3, E::visibleHeight*0.3);
	restartIcon->setVisible(false);
	restartIcon->setOpacity(0);
	this->addChild(restartIcon, 1000);

	// return background
	auto bgReturn = BallButton::create(E::C400, E::C200, CC_CALLBACK_1(S_MainGame::menuCallback, this));
	bgReturn->setTag(TAG_RETURN_BG);
	bgReturn->setScale(0.2f);
	bgReturn->setPosition(E::visibleWidth*0.7, 0);
	bgReturn->setVisible(false);
	this->addChild(bgReturn, 1000);

	// return icon
	auto returnIcon = Sprite::create("b_leave.png");
	returnIcon->setScale(0.6f);
	returnIcon->setTag(TAG_RETURN_IC);
	returnIcon->setPosition(E::visibleWidth*0.7, E::visibleHeight*0.3);
	returnIcon->setVisible(false);
	returnIcon->setOpacity(0);
	this->addChild(returnIcon, 1000);
}

#define ANI_SCALING_BG		30.0f
#define ANI_PAUSE_MOVING	30.0f
#define ANI_PAUSE_SCALING	15.0f
#define ANI_PAUSE_OPACING	15.0f
#define ANI_GO_MOVING		15.0f
#define ANI_GO_SCALING		15.0f
#define ANI_GO_OPACING		15.0f
void S_MainGame::updateAnim(){
	if(m_close > 0){
		m_tick = m_tick - 1;
	}
	else{
		m_tick ++;
	}

	if(m_tick < 0){
		Director::getInstance()->replaceScene(S_Welcome::createScene());
	}

	if(m_tick <= ANI_SCALING_BG){
		this->getChildByTag(TAG_BTM_BG)->setScale(1 + (m_tick/ANI_SCALING_BG)*3.0f);
		this->getChildByTag(TAG_SHADOW)->setOpacity((m_tick/ANI_SCALING_BG)*255);
	}

	if(m_tick <= ANI_PAUSE_MOVING){
		this->getChildByTag(TAG_PAUSE)->setPositionX((m_tick/ANI_PAUSE_MOVING)*(E::visibleWidth-36));
		this->getChildByTag(TAG_SILENT)->setPositionX((m_tick/ANI_PAUSE_MOVING)*(E::visibleWidth-36));
	}
	if(m_tick >= ANI_PAUSE_MOVING && m_tick <= ANI_PAUSE_MOVING+ANI_PAUSE_SCALING){
		this->getChildByTag(TAG_PAUSE)->setScale(0.15 + ((m_tick-ANI_PAUSE_MOVING)/ANI_PAUSE_SCALING)*0.1f);
		this->getChildByTag(TAG_SILENT)->setScale(0.15 + ((m_tick-ANI_PAUSE_MOVING)/ANI_PAUSE_SCALING)*0.1f);
		this->getChildByTag(TAG_PAUSE_I)->setOpacity(0);
		this->getChildByTag(TAG_SOUND_I)->setOpacity(0);
	}

	if(m_tick >= ANI_PAUSE_MOVING+ANI_PAUSE_SCALING  && m_tick <= ANI_PAUSE_MOVING+ANI_PAUSE_SCALING+ANI_PAUSE_OPACING){
		this->getChildByTag(TAG_PAUSE_I)->setOpacity(((m_tick-ANI_PAUSE_MOVING-ANI_PAUSE_OPACING)/ANI_PAUSE_SCALING)*255);
		this->getChildByTag(TAG_SOUND_I)->setOpacity(((m_tick-ANI_PAUSE_MOVING-ANI_PAUSE_OPACING)/ANI_PAUSE_SCALING)*255);
	}
	if(m_isGameOver)
	{
		if(m_close > 0 || m_isRestarting){
			m_tick2 --;
		}else{
			m_tick2 ++;
		}

		if(m_tick2 <= ANI_GO_MOVING)
		{
			this->getChildByTag(TAG_GAMEOVER_BG)->setVisible(true);
			this->getChildByTag(TAG_GAMEOVER_BG)->setPositionY(((m_tick2)/ANI_GO_MOVING)*(E::visibleHeight/2));
			this->getChildByTag(TAG_RESTART_BG)->setVisible(true);
			this->getChildByTag(TAG_RESTART_BG)->setPositionY(((m_tick2)/ANI_GO_MOVING)*(E::visibleHeight*0.3));
			this->getChildByTag(TAG_RETURN_BG)->setVisible(true);
			this->getChildByTag(TAG_RETURN_BG)->setPositionY(((m_tick2)/ANI_GO_MOVING)*(E::visibleHeight*0.3));
		}
		if(m_tick2 >= ANI_GO_MOVING && m_tick2 <= ANI_GO_MOVING + ANI_GO_SCALING)
		{
			this->getChildByTag(TAG_GAMEOVER_BG)->setScale(0.3+((m_tick2-ANI_GO_MOVING)/ANI_GO_SCALING)*1.5);
			this->getChildByTag(TAG_RESTART_BG)->setScale(0.2+((m_tick2-ANI_GO_MOVING)/ANI_GO_SCALING)*0.4);
			this->getChildByTag(TAG_RETURN_BG)->setScale(0.2+((m_tick2-ANI_GO_MOVING)/ANI_GO_SCALING)*0.4);
		}
		if(m_tick2 >= ANI_GO_MOVING + ANI_GO_SCALING && m_tick2 <= ANI_GO_MOVING + ANI_GO_SCALING + ANI_GO_OPACING)
		{
			this->getChildByTag(TAG_GAMEOVER_IC)->setVisible(true);
			this->getChildByTag(TAG_GAMEOVER_IC)->setOpacity(((m_tick2-ANI_GO_MOVING-ANI_GO_SCALING)/ANI_GO_SCALING)*255);
			this->getChildByTag(TAG_RESTART_IC)->setVisible(true);
			this->getChildByTag(TAG_RESTART_IC)->setOpacity(((m_tick2-ANI_GO_MOVING-ANI_GO_SCALING)/ANI_GO_SCALING)*255);
			this->getChildByTag(TAG_RETURN_IC)->setVisible(true);
			this->getChildByTag(TAG_RETURN_IC)->setOpacity(((m_tick2-ANI_GO_MOVING-ANI_GO_SCALING)/ANI_GO_SCALING)*255);
		}
		if(m_tick2 < 0){
			
			this->getChildByTag(TAG_RETURN_IC)->setVisible(false);
			this->getChildByTag(TAG_RESTART_IC)->setVisible(false);
			this->getChildByTag(TAG_GAMEOVER_IC)->setVisible(false);
			this->getChildByTag(TAG_GAMEOVER_BG)->setVisible(false);
			this->getChildByTag(TAG_RESTART_BG)->setVisible(false);
			this->getChildByTag(TAG_RETURN_BG)->setVisible(false);
			restartGame();
		}
	}
}

void S_MainGame::menuCallback(Ref* pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	auto tag = pMenuItem->getTag();
	switch(tag)
	{
	case TAG_PAUSE:
		{
			m_close = 1;
			m_tick = ANI_PAUSE_MOVING + ANI_PAUSE_SCALING;
			break;
		}

	case TAG_SILENT:
		{
			break;
		}
	case TAG_RESTART_BG:
		{
			m_isRestarting = true;
			m_tick2 = ANI_GO_MOVING + ANI_GO_SCALING  +ANI_GO_OPACING;
			break;
		}
	case TAG_RETURN_BG:
		{
			m_close = 1;
			m_tick2 = ANI_GO_MOVING + ANI_GO_SCALING  +ANI_GO_OPACING;
			m_tick = ANI_PAUSE_MOVING + ANI_PAUSE_SCALING;
			break;
		}
	}

}
