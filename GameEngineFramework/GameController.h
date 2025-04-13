#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "AudioController.h"

class Renderer;
class InputController;
class Timing;
class PhysicsController;
class Level1;
class Song;

class GameController : public Singleton<GameController>
{
public:
	// Constructors/Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void RunGame();
	void Initialize();
	void ShutDown();

private:
	// Members
	Renderer* m_renderer;
	AudioController* m_audio;
	InputController* m_input;
	PhysicsController* m_physics;
	Timing* m_timing;
	Level1* m_level1;
	Song* m_song;
};

#endif


