#ifndef PLAYER_1_H
#define PLAYER_1_H

#include "Resource.h"
#include "Player1State.h"
#include "RigidBody.h"
#include "StandardIncludes.h"
#include "AudioController.h"

class SpriteSheet;
class SoundEffect;
class TTFont;

class Player1 : public Resource
{
public:
	// Constructors / Destructors
	Player1();
	virtual ~Player1();

	// Accessors
	void SetOutcome(string _outcome) { m_outcome = _outcome; }
	int GetStatus() { return m_status; }
	void SetStatus(int _status) { m_status = _status; }
	Player1State* GetState() { return m_state; }
	void SetState(Player1State* _state) { m_state = _state; }
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
	void PlayRollSound();
	void PlayGunSound();


private:
	string m_playerName;
	string m_outcome;
	int m_wins;
	int m_losses;
	int m_status;
	Player1State* m_state;
	RigidBody* m_rigidBody;
	SpriteSheet* m_animations;
	Rect m_srcRect;
	SoundEffect* m_effects[MaxEffectChannels];
	TTFont* m_fArial20;
};

#endif

