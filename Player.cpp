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

bool CPlayer::isAlive() {
	if (CurrentLives <= 0) {
		return false;
	}
	else {
		return true;
	}
}

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
//-------------------------------------------------------------------------------
//gets
std::string CPlayer::GetCurrency() {
	std::string currency = std::to_string(CurrentCurrency);
	return currency;
}

std::string CPlayer::GetLives() {
	std::string lives = std::to_string(CurrentLives);
	return lives;
}

//-------------------------------------------------------------------------------
bool CPlayer::PlaceTower(int Tower) {
	switch (Tower) {
		//Tower 1 Placement
		case 1:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 15 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 2 Placement
		case 2:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 25 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 3 Placement
		case 3:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 40 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 4 Placement
		case 4:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 60 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 5 Placement
		case 5:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 75 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 6 Placement
		case 6:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 100 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 7 Placement
		case 7:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 150 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 8 Placement
		case 8:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 200 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 9 Placement
		case 9:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 275 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 10 Placement
		case 10:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 345 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 11 Placement
		case 11:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 400 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		//Tower 12 Placement
		case 12:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 475 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 13 Placement
		case 13:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 555 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 14 Placement
		case 14:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 645 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 15 Placement
		case 15:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 750 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
		//Tower 16 Placement
		case 16:
			if (m_bGodMode == false) {
				if (CurrentCurrency - 850 >= 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
			break;
	}
}
//-------------------------------------------------------------------------------
std::string CPlayer::GetTAmount(std::vector<CTower*> amount) {
	int size = amount.size();
	std::string num = to_string(size);
	return num;
}
