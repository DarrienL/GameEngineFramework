#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Level.h"

class GameController : public Singleton<GameController>
{
public: 
	// Constructors/Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void RunGame();
};

#endif

