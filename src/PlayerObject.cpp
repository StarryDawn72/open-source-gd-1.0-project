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

void PlayerObject::stopRotation()
{
    stopActionByTag(kTagRotateAction);

    if (getRotation() != 0.0f) {
        float clamped = getRotation() % 360;

        float rotation = (flipMod() == 1)
            ? roundf(clamped / 90.0f) * 90
            : roundf(clamped / -90.0f) * -90;

        setRotation(rotation);
    }
}

void PlayerObject::runRotateAction()
{
  stopRotation();
  
  CCRotateBy* rotateAction = CCRotateBy::create(26.0f / 60.0f, 180 * flipMod());
  rotateAction->setTag(kTagRotateAction);

  runAction(rotateAction);
}

void PlayerObject::spawnCircle()
{
    CCCircleWave* circle = CCCircleWave::create(70.0f, 2.0f, 0.3f, true);

    circle->setColor(getColor());
    circle->setPosition(getPosition());

    gameLayer_->addChild(circle, 0);

    circle->followObject(this);
    circle->setCircleMode(CircleMode::Outline);
}

void PlayerObject::pushButton(PlayerButton button)
{
    if (!isLocked_ && button == PlayerButton::Jump) {
        upKeyDown_ = true;
        canRingJump_ = true;
    }
}

void PlayerObject::releaseButton(PlayerButton button)
{
    if (button == PlayerButton::Jump) {
        upKeyDown_ = false;
        canRingJump_ = false;
    }
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

void PlayerObject::hitGround(bool noParticle)
{
    yVelocity_ = 0.0f;

    if (!onGround_ && !noParticle) {

        CCParticleSystemQuad* particles = useFirstLandParticles_
            ? landParticles1_
            : landParticles2_;

        useFirstLandParticles_ = !useFirstLandParticles_;

        CCPoint offset = ccp(0.0f, flipMod() * -15.0f);
        particles->setPosition(cppAdd(particles->getPosition(), ));

        CCParticleSystem::resetSystem(particles);
    }

    onGround_ = true;
    canJump_ = true;

    if (getActionByTag(kTagRotateAction))
        stopRotation();

    lastGroundPos_ = getPosition();

    if (!flyMode_)
        deactivateStreak();

    if (!flyMode_)
        tryPlaceCheckpoint();

    unk355_ = false;
}

CCPoint PlayerObject::getRealPosition()
{
    return getPosition();
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