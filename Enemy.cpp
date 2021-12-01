#include "Enemy.h"

// Using turret as a temp value
CEnemy::CEnemy(int type, const Vector2& p) : CObject(eSprite::EnemyS, p)
{
	m_fRadius = 10;
	m_bStatic = false;
	m_bIsTarget = true;

	EnemyType = type;

	if (m_bNormalAssets) {
		m_nSpriteIndex = UINT(eSprite::EnemyS);
	}
	else {
		m_nSpriteIndex = UINT(eSprite::Student);
	}
	m_nCurrentFrame = EnemyType;

	if (pWave->getWaveNum() < 3)
	{
		EnemyHealth = 1.0f;
	}
	else
	{
		//do cases for 0-23 and this is where health can be set when enemy is created
		switch (EnemyType) {
		// Enemy variant 0
		case 0:
			EnemyHealth = EnemyHealth;
			EnemyWorth = EnemyWorth * 0.5f;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 1
		case 1:
			EnemyHealth = EnemyHealth + 1;
			EnemyWorth = EnemyWorth;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 2
		case 2:
			EnemyHealth = EnemyHealth + 2;
			EnemyWorth = EnemyWorth + 1;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 3
		case 3:
			EnemyHealth = EnemyHealth + 3;
			EnemyWorth = EnemyWorth + 2;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 4
		case 4:
			EnemyHealth = EnemyHealth + 4;
			EnemyWorth = EnemyWorth + 3;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 5
		case 5:
			EnemyHealth = EnemyHealth + 5;
			EnemyWorth = EnemyWorth + 3;
			EnemyMoveSpeed = EnemyMoveSpeed;
			if (pWave->getWaveNum() > 15) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 6
		case 6:
			EnemyHealth = EnemyHealth + 6;
			EnemyWorth = EnemyWorth + 3;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 20) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 35) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 7
		case 7:
			EnemyHealth = EnemyHealth + 7;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 20) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 35) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 8
		case 8:
			EnemyHealth = EnemyHealth + 9;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 40) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 60) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 9
		case 9:
			EnemyHealth = EnemyHealth + 11;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			break;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
		// Enemy variant 10
		case 10:
			EnemyHealth = EnemyHealth + 15;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 11
		case 11:
			EnemyHealth = EnemyHealth + 17;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 1;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 12
		case 12:
			EnemyHealth = EnemyHealth + 20;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 13
		case 13:
			EnemyHealth = EnemyHealth + 21;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 14
		case 14:
			EnemyHealth = EnemyHealth + 25;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 15
		case 15:
			EnemyHealth = EnemyHealth + 30;
			EnemyWorth = EnemyWorth + 4;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 16
		case 16:
			EnemyHealth = EnemyHealth + 40;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 17
		case 17:
			EnemyHealth = EnemyHealth + 50;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 18
		case 18:
			EnemyHealth = EnemyHealth + 60;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 19
		case 19:
			EnemyHealth = EnemyHealth + 70;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 20
		case 20:
			EnemyHealth = EnemyHealth + 80;
			EnemyWorth = EnemyWorth + 5;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 25) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 50) {
				EnemyHealth += 2;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 6;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 21
		case 21:
			EnemyHealth = EnemyHealth + 90;
			EnemyWorth = EnemyWorth + 6;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += 10;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum() / 2;
			}
			break;
		// Enemy variant 22
		case 22:
			EnemyHealth = EnemyHealth + 120;
			EnemyWorth = EnemyWorth + 7;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 30) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 70) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += 10;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum();
			}
			break;
		// Enemy variant 23
		case 23:
			EnemyHealth = EnemyHealth + 140;
			EnemyWorth = EnemyWorth + 8;
			EnemyMoveSpeed = EnemyMoveSpeed * 2;
			if (pWave->getWaveNum() > 40) {
				EnemyHealth += 3;
			}
			if (pWave->getWaveNum() > 80) {
				EnemyHealth += 5;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += 20;
			}
			if (pWave->getWaveNum() > 90) {
				EnemyHealth += pWave->getWaveNum();
			}
			break;
		// Default case
		default:
			EnemyHealth = EnemyHealth;
			EnemyWorth = EnemyWorth;
			EnemyMoveSpeed = EnemyMoveSpeed;
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//
//	Removed the rest of the code from the file because it was not mine, but my groupmates portion of the code.
//
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
