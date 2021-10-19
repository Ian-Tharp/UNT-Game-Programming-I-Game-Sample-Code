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
	m_fRotSpeed = 0;
}

//Look towards the enemy that passes through the radius of the tower
void CTower::RotateTowards(const Vector2& position) {
	//do something here
}

void CTower::move() {

}

void CTower::draw() {

}
