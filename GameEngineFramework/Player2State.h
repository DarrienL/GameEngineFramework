#ifndef PLAYER_2_STATE_H
#define PLAYER_2_STATE_H

#include "StandardIncludes.h"

class Player2;
class IdleState;
class RollingState;
class PaperState;
class ScissorsState;
class RockState;

class Player2State
{
public:
	// Constructors / Destructors
	Player2State() {}
	virtual ~Player2State() {}

	// Accessors
	static IdleState* GetIdleState() { return &m_idle; }
	static RollingState* GetRollingState() { return &m_rolling; }
	static PaperState* GetPaperState() { return &m_paper; }
	static ScissorsState* GetScissorsState() { return &m_scissors; }
	static RockState* GetRockState() { return &m_rock; }

	// Methods
	virtual void HandleInput(Player2* _player, SDL_Event _event);
	virtual void Update(Player2* _player, float _deltaTime) = 0;

private:
	// Members
	static IdleState m_idle;
	static RollingState m_rolling;
	static PaperState m_paper;
	static ScissorsState m_scissors;
	static RockState m_rock;
	Point m_mPos;
};

class IdleState : public Player2State
{
public:
	// Constructors / Destructors
	IdleState() {}
	virtual ~IdleState() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class RollingState : public Player2State
{
public:
	// Constructors / Destructors
	RollingState() {}
	virtual ~RollingState() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class PaperState : public Player2State
{
public:
	// Constructors / Destructors
	PaperState() {}
	virtual ~PaperState() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class ScissorsState : public Player2State
{
public:
	// Constructors / Destructors
	ScissorsState() {}
	virtual ~ScissorsState() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class RockState : public Player2State
{
public:
	// Constructors / Destructors
	RockState() {}
	virtual ~RockState() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

#endif

