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
	CTower(int i, int j, Vector2& p);
	virtual void move(); ///< Move turret.
	//virtual void draw(); ///< Draw turret.

	static const Vector2& GetPosition(int x, int y);

	int GetXPos();
	int GetYPos();
	void SetXPos(int x);
	void SetYPos(int y);

protected:
	void RotateTowards(const Vector2&); ///< Swivel towards position.

	//Removed health for now, the implementation of tower to potentially
	//die or get destroyed could be added later
	//const INT MaxHealth = 8; ///< Maximum health.
	//int Health = MaxHealth; ///< Current health initially.
	const INT TowerCost = 10;

	int xPos = 0;
	int yPos = 0;

};

#endif //__L4RC_GAME_TOWER_H__
