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

CTower::CTower(int i, int j, Vector2& p) : CObject(eSprite::Turret, p) {
	yPos = j;
	xPos = i;
	//Vector2 location(yPos, xPos);
	m_bStatic = true;
	m_vPos = Vector2((xPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f),
		(8 - yPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f));
}

void CTower::move() {
	if (m_pPlayer) {
		const float radius = ((CTower*)m_pPlayer)->m_fRadius;
	}
}

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

const Vector2& CTower::GetPosition(int x, int y) {
	return Vector2(x, y);
}

int CTower::GetXPos() {
	return xPos;
}

int CTower::GetYPos() {
	return yPos;
}

void CTower::SetXPos(int x) {
	xPos = x;
}

void CTower::SetYPos(int y) {
	yPos = y;
}
