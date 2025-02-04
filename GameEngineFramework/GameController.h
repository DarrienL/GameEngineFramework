#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

class GameController : public Singleton<GameController>
{
public: 
	// Constructors/Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void RunGame();

private:
	SDL_Event m_sdlEvent;
};

#endif

