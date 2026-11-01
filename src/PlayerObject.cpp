#include "PlayerObject.h"

#define kTagRotateAction 0

USING_NS_CC;

bool PlayerObject::getFlyMode()
{
    return flyMode_;
}

bool PlayerObject::getGravityFlipped()
{
    return gravityFlipped_;
}

bool PlayerObject::getIsDead()
{
    return isDead_;
}

CCPoint PlayerObject::getLastP()
{
    return lastP_;
}

void PlayerObject::setLastP(CCPoint lastP)
{
    lastP_ = lastP;
}

CCPoint PlayerObject::getPortalP()
{
    return portalP_;
}

void PlayerObject::setPortalP(CCPoint portalP)
{
    portalP_ = portalP;
}

CCLayer* PlayerObject::getGameLayer()
{
    return gameLayer_;
}

void PlayerObject::setGameLayer(CCLayer* gameLayer)
{
    gameLayer_ = gameLayer;
}

bool PlayerObject::getOnGround()
{
    return onGround_;
}

void PlayerObject::setOnGround(bool onGround)
{
    onGround_ = onGround;
}

bool PlayerObject::getIsLocked()
{
    return isLocked_
}

CCPoint PlayerObject::getLastGroundPos()
{
  return lastGroundPos_;
}

GameObject* PlayerObject::getTouchedRing()
{
    return touchedRing_;
}

void PlayerObject::setTouchedRing(GameObject* touchedRing)
{
    touchedRing_ = touchedRing;
}

GameObject* PlayerObject::getPortalObject()
{
    return portalObject_;
}

void PlayerObject::setPortalObject(GameObject* portalObject)
{
    portalObject_ = portalObject;
}

bool PlayerObject::getHasJumped()
{
    return hasJumped_;
}

bool PlayerObject::getHasRingJumped()
{
    return hasRingJumped_;
}

void PlayerObject::runRotateAction(PlayerObject* this)
{
  stopRotation();
  
  CCRotateBy* rotateAction = CCRotateBy::create(26.0f / 60.0f, 180 * flipMod());
  rotateAction->setTag(kTagRotateAction);

  runAction(rotateAction);
}

int PlayerObject::flipMod()
{
    return gravityFlipped_ ? -1 : 1;
}

bool PlayerObject::playerIsFalling()
{
    return !gravityFlipped_
        ? yVelocity_ < gravity_ + gravity_
        : yVelocity_ > gravity_ + gravity_;
}

void PlayerObject::lockPlayer()
{
  isLocked_ = true;
  stopActionByTag(kTagRotateAction);
  releaseButton(PlayerButton::Jump);
  deactivateParticle();
  onGround_ = false;
}

void PlayerObject::activateStreak()
{
    playerStreak_->resumeStroke();
}

void PlayerObject::deactivateStreak()
{
    playerStreak_->stopStroke();
}

void PlayerObject::touchedObject(GameObject* object)
{

}

void PlayerObject::gravityUp()
{
    gravity_ += 0.000100000005f;
    logValues();
}

void PlayerObject::gravityDown()
{
    gravity_ -= 0.000100000005f;
    logValues();
}

void PlayerObject::speedUp()
{
    playerXVelocity_ += 0.0005f;
    logValues();
}

void PlayerObject::speedDown()
{
    playerXVelocity_ -= 0.0005f;
    logValues();
}

void PlayerObject::yStartUp()
{
    yStart_ += 0.001f;
    logValues();
}

void PlayerObject::yStartDown()
{
    yStart_ -= 0.001f;
    logValues();
}

void PlayerObject::logValues()
{
    CCLog("Gravity: %f, xVel: %f, Jump: %f", gravity_, playerXVelocity_, yStart_);
}