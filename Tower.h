#ifndef __L4RC_GAME_TOWER_H__
#define __L4RC_GAME_TOWER_H__
//Tower Variables H File

#include "Object.h"

/*
	This is the base class for our towers. Utilizing modularity, we are
	able to easily create child towers from this base class.
*/
class CTower : public CObject {
public:
	CTower(const Vector2& p); ///< Constructor.
	virtual void move(); ///< Move turret.
	virtual void draw(); ///< Draw turret.

protected:
	void RotateTowards(const Vector2&); ///< Swivel towards position.
	void ShootAtTarget(const Vector2& position);

	//Removed health for now, the implementation of enemies to potentially
	//die or get destroyed could be added later
	//const UINT m_MaxHealth = 8; ///< Maximum health.
	//UINT m_Health = m_MaxHealth; ///< Current health.
	const UINT m_TowerCost = 0;

};

#endif //__L$RC_GAME_TOWER_H__
