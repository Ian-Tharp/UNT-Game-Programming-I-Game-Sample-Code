/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Common.h"

/// Create and initialize an player object given its initial position.
/// \param p Initial position of player.

CPlayer::CPlayer(const Vector2& p): CObject(eSprite::Player, p){ 
  m_bStatic = false;
} //constructor

void CPlayer::move() {

	if (Right && xPos < 15) {
		xPos++;
	}
    else if (Left && xPos > 0) {
	    xPos--;
    }
	else if (Up && yPos < 8) {
		yPos++;
	}
	else if (Down && yPos > 0) {
		yPos--;
	}

  m_vPos = Vector2((xPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f), 
	  (8 - yPos + 0.5f) * ((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * 0.5f));

} //move

const Vector2& CPlayer::GetPos() const {
  return m_vPos;
} //GetPos for sprite

std::string CPlayer::GetPlayerPosition() {
	XMFLOAT2 temp = GetPos();
	int x = temp.x;
	int y = temp.y;
	std::string tempStr = std::to_string(x);
	std::string tempStr2 = std::to_string(y);
	std::string Location = tempStr + tempStr2;
	return Location;
} //Get position of player itself

//Get functions for player position on map
int CPlayer::GetXPos() {
	return xPos;
}

int CPlayer::GetYPos() {
	return yPos;
}

//-------------------------------------------------------------------------------
//Add Currency to Player's CurrentCurrency
void CPlayer::AddCurrency(int Amount) {
	CurrentCurrency += Amount;
	//Safety clamp for calculations that result in greater than MaxCurrency
	if (CurrentCurrency >= MaxCurrency) {
		CurrentCurrency = MaxCurrency;
	}
}

//Add Lives to Player's CurrentLives
void CPlayer::AddLives(int Amount) {
	CurrentLives += Amount;
	//Safety clamp for calculations that result in greater than MaxLives
	if (CurrentLives >= MaxLives) {
		CurrentLives = MaxLives;
	}
}

//Remove Currency from Player's CurrentCurrency
void CPlayer::RemoveCurrency(int Amount) {
	CurrentCurrency -= Amount;
	//Safety clamp for calculations that result in less than 0
	if (CurrentCurrency <= 0) {
		CurrentCurrency = 0;
	}
}

//Remove Player Lives by input amount
void CPlayer::RemoveLives(int Amount) {
	CurrentLives -= Amount;
	if (CurrentLives <= 0) {
		//Possibly do something here to signal that the player has died to end the game
	}
}


//Bools to allow for directional movement of the player
void CPlayer::MoveRight() {
	Right = true;
}

void CPlayer::MoveLeft() {
	Left = true;
}

void CPlayer::MoveUp() {
	Up = true;
}

void CPlayer::MoveDown() {
	Down = true;
}

//Bools to stop directional movement of the player
void CPlayer::StopRight() {
	Right = false;
}

void CPlayer::StopLeft() {
	Left = false;
}

void CPlayer::StopUp() {
	Up = false;
}

void CPlayer::StopDown() {
	Down = false;
}

//gets
std::string CPlayer::GetCurrency() {
	std::string currency = std::to_string(CurrentCurrency);
	return currency;
}

std::string CPlayer::GetLives() {
	std::string lives = std::to_string(CurrentLives);
	return lives;
}

bool CPlayer::PlaceTower(int Tower) {
	switch (Tower) {
		case 1:
			if (CurrentCurrency - 10 >= 0) {
				RemoveCurrency(15);
				return true;
			}
			else {
				return false;
			}
			break;
		case 2:
			if (CurrentCurrency - 25 >= 0) {
				RemoveCurrency(25);
				return true;
			}
			else {
				return false;
			}
			break;
	}
}

std::string CPlayer::GetTAmount(std::vector<CTower*> amount) {
	int size = amount.size();
	std::string num = to_string(size);
	return num;
}
