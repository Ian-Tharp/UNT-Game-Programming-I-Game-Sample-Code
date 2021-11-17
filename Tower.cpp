/// \file Tower.cpp
/// \brief Code for the tower object class CTower

#include "Tower.h"
#include "Common.h"
#include "Game.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "Player.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize a tower object given its position
/// \param p Position of Tower

CTower::CTower(const Vector2& p) : CObject(eSprite::Tower, p) {
	m_bStatic = true; //towers are static
} //constructor

CTower::CTower(int type, int i, int j, Vector2& p) : CObject(eSprite::Tower, p) {
	m_bStatic = true;
	yPos = j;
	xPos = i;
	TowerType = type;
	desc.m_vPos = m_vPos;

	m_nSpriteIndex = UINT(eSprite::Tower);
	switch (TowerType) {
	case 1:
		m_nCurrentFrame = 0;
		break;
	case 2:
		m_nCurrentFrame = 1;
		break;
	case 3:
		m_nCurrentFrame = 2;
		break;
	case 4:
		m_nCurrentFrame = 3;
		break;
	case 5:
		m_nCurrentFrame = 4;
		break;
	case 6:
		m_nCurrentFrame = 5;
		break;
	case 7:
		m_nCurrentFrame = 6;
		break;
	case 8:
		m_nCurrentFrame = 7;
		break;
	case 9:
		m_nCurrentFrame = 8;
		break;
	case 10:
		m_nCurrentFrame = 9;
		break;
	case 11:
		m_nCurrentFrame = 10;
		break;
	case 12:
		m_nCurrentFrame = 11;
		break;
	case 13:
		m_nCurrentFrame = 12;
		break;
	case 14:
		m_nCurrentFrame = 13;
		break;
	case 15:
		m_nCurrentFrame = 14;
		break;
	case 16:
		m_nCurrentFrame = 15;
		break;
	}

	m_vPos = Vector2((xPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f),
		(8 - yPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f));
}

void CTower::move() {
	if (m_pPlayer) {
		const float radius = ((CTower*)m_pPlayer)->m_fRadius;

		if (enemies.front() != NULL) {
			if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, radius) && enemies.size() != 0) {
				RotateTowards(enemies.front()->m_vPos);
			}
		}
		/*//Check if the player is visible
		if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, radius)) {
			RotateTowards(m_pPlayer->m_vPos);
		}*/
	}
	m_fRoll += 0.2f * m_fRotSpeed* XM_2PI * m_pTimer->GetFrameTime(); //rotate
	NormalizeAngle(m_fRoll);
}

//Look towards the enemy that passes through the radius of the tower
void CTower::RotateTowards(const Vector2& position) {
	const Vector2 v = position - m_vPos; //vector from target to tower
	const float theta = atan2f(v.y, v.x); //orientation of that vector
	float diff = m_fRoll - theta;
	NormalizeAngle(diff); //normalizing to [-pi, pi]

	float fAngleDelta = 0.05f; //allowable angle discrepancy
	float fTrackingSpeed = 2.0f; //rotation speed when tracking

	//Changing rotate speed and angle discrepancy from bullets depending on tower type
	switch (TowerType) {
	case 1:
		fAngleDelta = 0.07f;
		fTrackingSpeed = 2.0f;
		break;
	case 2:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 2.1f;
		break;
	case 3:
		fAngleDelta = 0.06f;
		fTrackingSpeed = 2.5f;
		break;
	case 4:
		fAngleDelta = 0.15f;
		fTrackingSpeed = 1.98f;
		break;
	case 5:
		fAngleDelta = 0.10f;
		fTrackingSpeed = 2.2f;
		break;
	case 6:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 2.3f;
		break;
	case 7:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.85f;
		break;
	case 8:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.9f;
		break;
	case 9:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 2.0f;
		break;
	case 10:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.4f;
		break;
	case 11:
		fAngleDelta = 0.04f;
		fTrackingSpeed = 2.5f;
		break;
	case 12:
		fAngleDelta = 0.09f;
		fTrackingSpeed = 2.6f;
		break;
	case 13:
		fAngleDelta = 0.08f;
		fTrackingSpeed = 2.15f;
		break;
	case 14:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 2.7f;
		break;
	case 15:
		fAngleDelta = 0.07f;
		fTrackingSpeed = 2.8f;
		break;
	case 16:
		fAngleDelta = 0.05f;
		fTrackingSpeed = 2.9f;
		break;
	}

	if (diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
	else if (diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwsise
	else m_fRotSpeed = 0; //stop rotating


	if (fabsf(diff) < fAngleDelta && m_pGunFireEvent->Triggered()) {
		switch (TowerType) {
		case 1:
			m_pObjectManager->FireGun(this, eSprite::Bullet);
			break;
		case 2:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			//m_pObjectManager->FireGun(this, eSprite::Bullet2);
			//m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 3:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 4:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 5:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 6:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 7:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 8:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 9:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 10:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 11:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			m_pPlayer->AddCurrency(2);
			break;
		case 12:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 13:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 14:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 15:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		case 16:
			m_pObjectManager->FireGun(this, eSprite::Bullet2);
			break;
		}
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
