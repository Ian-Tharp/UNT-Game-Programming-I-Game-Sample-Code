/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Object.h"
#include "mapGen.h"
#include "TileManager.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it does not move, but rather is a
/// controller that is able to manipulate the other objects in the game
/// via mouse control.

class CPlayer: public CObject{
  protected:  
	  const INT MaxCurrency = 1000; ///< Maximum amount of currency the player may hold at one time
	  int CurrentCurrency = 50; ///< Current currency the player has to purchase towers. Starts off with 50
	  int CurrentLives = 100; ///< Amount of lives that the player has to survive
	  const INT MaxLives = 100; ///< Maximum amount of lives the player can have at one time
	  bool Right = false;
	  bool Left = false;
	  bool Up = false;
	  bool Down = false;

	  int xPos = 0;
	  int yPos = 0;

  public:
    CPlayer(const Vector2& p); ///< Constructor.

    virtual void move(); ///< Move player object.

	//Player interaction to place towers
	bool PlaceTower(int Tower);

	//Player movement across grid tiles
	void MoveRight();
	void StopRight();
	void MoveLeft();
	void StopLeft();
	void MoveUp();
	void StopUp();
	void MoveDown();
	void StopDown();

	//Adding & subtracting member variables
	void RemoveLives(int Amount);
	void RemoveCurrency(int Amount);
	void AddLives(int Amount);
	void AddCurrency(int Amount);
    
	std::string GetCurrency();
	std::string GetLives();
	std::string GetTAmount(std::vector<CTower*> amount);

    const Vector2& GetPos() const; ///< Get position of sprite
	std::string GetPlayerPosition(); ///< Get position of player sprite

	//Get functions for player position on map
	int GetXPos();
	int GetYPos();
}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__
