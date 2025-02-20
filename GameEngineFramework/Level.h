#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <ctime>
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"

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
	void AssignNonDefaultValues(Color backgroundColor, bool hasRocks, bool autosaved);
	void RunLevel();
	float GetRandomFloat(float min, float max);
	void SetAutosaved(bool autosaved);

private:
	// Members
	SDL_Event m_sdlEvent;
	Color m_backgroundColor = Color(0, 0, 0, 255);
	bool m_hasRocks;
	bool m_autosaved;
	float m_warriorXPos[10];
	float m_warriorSpeed[10];
	float m_elapsedTime;
	int m_elapsedTimeSeconds;
	float m_rockYPos[10];
	float m_rockSpeed[10];
	bool m_warriorIsAlive[10];
	bool m_rockExists[10];
	float m_warriorDeathTimer[10];
};

#endif
