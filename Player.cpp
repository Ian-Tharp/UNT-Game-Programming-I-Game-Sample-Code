/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize an player object given its initial position.
/// \param p Initial position of player.

CPlayer::CPlayer(const Vector2& p): CObject(eSprite::Player, p){ 
  m_bStatic = true;
} //constructor

void CPlayer::move(){
  const float t = m_pTimer->GetFrameTime(); //time
  const Vector2 view = GetViewVector(); //view vector
    
  const Vector2 norm = VectorNormalCC(view); //normal to view vector
} //move

void CPlayer::draw() {

}

const Vector2& CPlayer::GetPos() const{
  return m_vPos;
} //GetPos

//Add Currency to Player's CurrentCurrency
void CPlayer::AddCurrency(int Amount) {
	CurrentCurrency += Amount;
	if (CurrentCurrency >= m_nMaxCurrency) {
		CurrentCurrency = m_nMaxCurrency;
	}
}

//Remove Currency from Player's CurrentCurrency
void CPlayer::RemoveCurrency(int Amount) {
	CurrentCurrency -= Amount;
	if (CurrentCurrency <= 0) {
		CurrentCurrency = 0;
	}
}

//Remove Player Lives by input amount
void CPlayer::RemoveLives(int Amount) {
	Lives -= Amount;
	if (Lives <= 0) {
		//Possibly do something here to signal that the player has died to end the game
	}
}

std::string CPlayer::GetCurrency() {
	std::string test = std::to_string(CurrentCurrency);
	return test;
}
