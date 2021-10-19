/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Object.h"
#include <string>

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it does not move, but rather is a
/// controller that is able to manipulate the other objects in the game
/// via mouse control.

class CPlayer: public CObject{
  protected:  
	  const UINT m_nMaxCurrency = 1000; ///< Maximum amount of currency the player may hold at one time
	  int CurrentCurrency = 50; ///< Current currency the player has to purchase towers. Starts off with 50
	  int Lives = 100; ///< Amount of lives that the player has to survive
	  const char pchar = '30';

  public:
    CPlayer(const Vector2& p); ///< Constructor.

    virtual void move(); ///< Move player object.
	virtual void draw(); ///< Draw 

	void RemoveLives(int Amount);
	void RemoveCurrency(int Amount);
	void AddCurrency(int Amount);
    
	std::string GetCurrency();

    const Vector2& GetPos() const; ///< Get position.
}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__
