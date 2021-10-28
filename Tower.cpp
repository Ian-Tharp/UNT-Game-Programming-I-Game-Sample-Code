/// \file Tower.cpp
/// \brief Code for the tower object class CTower

#include "Tower.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "Player.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize a tower object given its position
/// \param p Position of Tower

CTower::CTower(const Vector2& p) : CObject(eSprite::Turret, p) {
	m_bStatic = true; //towers are static
} //constructor

//Look towards the enemy that passes through the radius of the tower
void CTower::RotateTowards(const Vector2& position) {
	const Vector2 v = position - m_vPos; //vector from target to player
	const float theta = atan2f(v.y, v.x); //orientation of that vector
	float diff = m_fRoll - theta;
	NormalizeAngle(diff); //normalizing to [-pi, pi]

	const float fAngleDelta = 0.05f; //allowable angle discrepancy
	const float fTrackingSpeed = 2.0f; //rotation speed when tracking

	if (diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
	else if (diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwsise
	else m_fRotSpeed = 0; //stop rotating

	if (fabsf(diff) < fAngleDelta && m_pGunFireEvent->Triggered()) {
		m_pObjectManager->FireGun(this, eSprite::Bullet2);
	} //Rotate Towards target

}

void CTower::move() {

}

void CTower::draw() {

}
