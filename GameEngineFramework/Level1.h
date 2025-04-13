#ifndef LEVEL_1_H
#define LEVEL_1_H

#include "Level.h"
#include "Level2.h"

class TTFont;
class Renderer;
class Texture;

class Level1 : public Level
{
public:
	// Constructors/Destructors
	Level1();
	virtual ~Level1();

	// Methods
	virtual void Initialize();
	virtual void Shutdown();
	virtual void HandleInput(SDL_Event _event);
	virtual void Run(Renderer* _renderer);
	void ToString() override;

private:
	// Members
	SDL_Event m_sdlEvent;
	bool m_quit;
	string m_playerNames[2];
	int m_currentName;
	bool m_playLevel;
	bool m_displayError;
	Level2* m_level2;
	TTFont* m_fArial20;
	TTFont* m_fArial40;
	Texture* m_texture;
};

#endif

