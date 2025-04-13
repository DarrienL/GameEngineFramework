#ifndef PLAYER_2_H
#define PLAYER_2_H

#include "Resource.h"
#include "Player2State.h"
#include "RigidBody.h"
#include "StandardIncludes.h"

class SpriteSheet;
class TTFont;

class Player2 : Resource
{
public:
	// Constructors / Destructors
	Player2();
	virtual ~Player2();

	// Accessors
	void SetOutcome(string _outcome) { m_outcome = _outcome; }
	int GetStatus() { return m_status; }
	void SetStatus(int _status) { m_status = _status; }
	Player2State* GetState() { return m_state; }
	void SetState(Player2State* _state) { m_state = _state; }
	SpriteSheet* GetAnimations() { return m_animations; }
	Rect* GetSrcRect() { return &m_srcRect; }
	RigidBody* GetRigidBody() { return m_rigidBody; }

	// Methods
	void Initialize(TTFont* _font, string _name);
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	virtual void HandleInput(SDL_Event _event, float _deltaTime);
	virtual void Update(float _deltaTime);
	virtual void Render(Renderer* _renderer);
	void Draw();
	void Win();
	void Lose();
	int RNG();


private:
	string m_playerName;
	string m_outcome;
	int m_wins;
	int m_losses;
	int m_status;
	Player2State* m_state;
	RigidBody* m_rigidBody;
	SpriteSheet* m_animations;
	Rect m_srcRect;
	TTFont* m_fArial20;
};

#endif


