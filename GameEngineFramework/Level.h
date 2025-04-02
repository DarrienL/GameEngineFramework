#ifndef LEVEL_H
#define LEVEL_H

#include "NPC.h"
#include "Player.h"
#include "AudioController.h"

class Renderer;
class TTFont;
class InputController;
class AudioController;
class SoundEffect;


class Level : public Resource
{
public:
	// Constructors/Destructors
	Level();
	virtual ~Level();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	float GetRandomFloat(float min, float max);
	void SetDefaultValues(int _numberOfNPCs);
	void HandleInput(SDL_Event _event, float deltaTime);
	void RunLevel();

private:
	// Members
	bool m_quit;
	SDL_Event m_sdlEvent;
	Renderer* m_renderer;
	TTFont* m_fArial20;
	InputController* m_input;
	AudioController* m_audio;
	SoundEffect* m_effects[10];

	float m_playerSpeed;
	float m_NPCSpeed;
	float m_playerScale;
	float m_NPCScale;
	int m_numberOfNPCs;
	int m_enemiesTagged;

	Player* m_player;
	vector<NPC*> m_npcs;
};

#endif
