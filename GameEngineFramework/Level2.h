#ifndef LEVEL_2_H
#define LEVEL_2_H

#include "Level.h"

class Player1;
class Player2;
class TTFont;
class Renderer;
class PhysicsController;

class Level2 : public Level
{
public:
	// Constructors/Destructors
	Level2();
	virtual ~Level2();

	// Methods
	virtual void Initialize(TTFont* _font, string _names[]);
	virtual void Shutdown();
	virtual void HandleInput(SDL_Event _event);
	virtual void Run(Renderer* _renderer, TTFont* _font, string _names[]);
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;

private:
	// Members
	SDL_Event m_sdlEvent;
	PhysicsController* m_physics;
	bool m_quit;
	int m_saves;
	int m_loads;
	float m_elapsedTime;
	Player1* m_player1;
	Player2* m_player2;
};

#endif

