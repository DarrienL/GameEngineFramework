#ifndef PLAYER_2_STATE_H
#define PLAYER_2_STATE_H

#include "StandardIncludes.h"

class Player2;
class IdleState2;
class RollingState2;
class PaperState2;
class ScissorsState2;
class RockState2;

class Player2State
{
public:
	// Constructors / Destructors
	Player2State() {}
	virtual ~Player2State() {}

	// Accessors
	static IdleState2* GetIdleState() { return &m_idle; }
	static RollingState2* GetRollingState() { return &m_rolling; }
	static PaperState2* GetPaperState() { return &m_paper; }
	static ScissorsState2* GetScissorsState() { return &m_scissors; }
	static RockState2* GetRockState() { return &m_rock; }

	// Methods
	virtual void HandleInput(Player2* _player, SDL_Event _event);
	virtual void Update(Player2* _player, float _deltaTime) = 0;

private:
	// Members
	static IdleState2 m_idle;
	static RollingState2 m_rolling;
	static PaperState2 m_paper;
	static ScissorsState2 m_scissors;
	static RockState2 m_rock;
	Point m_mPos;
};

class IdleState2 : public Player2State
{
public:
	// Constructors / Destructors
	IdleState2() {}
	virtual ~IdleState2() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class RollingState2 : public Player2State
{
public:
	// Constructors / Destructors
	RollingState2() {}
	virtual ~RollingState2() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class PaperState2 : public Player2State
{
public:
	// Constructors / Destructors
	PaperState2() {}
	virtual ~PaperState2() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class ScissorsState2 : public Player2State
{
public:
	// Constructors / Destructors
	ScissorsState2() {}
	virtual ~ScissorsState2() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

class RockState2 : public Player2State
{
public:
	// Constructors / Destructors
	RockState2() {}
	virtual ~RockState2() {}

	// Methods
	void HandleInput(Player2* _player, SDL_Event _event) override;
	void Update(Player2* _player, float _deltaTime) override;
};

#endif

