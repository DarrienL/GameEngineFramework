#ifndef PLAYER_1_STATE_H
#define PLAYER_1_STATE_H

#include "StandardIncludes.h"

class Player1;
class IdleState;
class RollingState;
class PaperState;
class ScissorsState;
class RockState;

class Player1State
{
public:
	// Constructors / Destructors
	Player1State() {}
	virtual ~Player1State() {}

	// Accessors
	static IdleState* GetIdleState() { return &m_idle; }
	static RollingState* GetRollingState() { return &m_rolling; }
	static PaperState* GetPaperState() { return &m_paper; }
	static ScissorsState* GetScissorsState() { return &m_scissors; }
	static RockState* GetRockState() { return &m_rock; }

	// Methods
	virtual void HandleInput(Player1* _player, SDL_Event _event);
	virtual void Update(Player1* _player, float _deltaTime) = 0;

private:
	// Members
	static IdleState m_idle;
	static RollingState m_rolling;
	static PaperState m_paper;
	static ScissorsState m_scissors;
	static RockState m_rock;
	Point m_mPos;
};

class IdleState : public Player1State
{
public:
	// Constructors / Destructors
	IdleState() {}
	virtual ~IdleState() {}

	// Methods
	void HandleInput(Player1* _player, SDL_Event _event) override;
	void Update(Player1* _player, float _deltaTime) override;
};

class RollingState : public Player1State
{
public:
	// Constructors / Destructors
	RollingState() {}
	virtual ~RollingState() {}

	// Methods
	void HandleInput(Player1* _player, SDL_Event _event) override;
	void Update(Player1* _player, float _deltaTime) override;
};

class PaperState : public Player1State
{
public:
	// Constructors / Destructors
	PaperState() {}
	virtual ~PaperState() {}

	// Methods
	void HandleInput(Player1* _player, SDL_Event _event) override;
	void Update(Player1* _player, float _deltaTime) override;
};

class ScissorsState : public Player1State
{
public:
	// Constructors / Destructors
	ScissorsState() {}
	virtual ~ScissorsState() {}

	// Methods
	void HandleInput(Player1* _player, SDL_Event _event) override;
	void Update(Player1* _player, float _deltaTime) override;
};

class RockState : public Player1State
{
public:
	// Constructors / Destructors
	RockState() {}
	virtual ~RockState() {}

	// Methods
	void HandleInput(Player1* _player, SDL_Event _event) override;
	void Update(Player1* _player, float _deltaTime) override;
};

#endif
