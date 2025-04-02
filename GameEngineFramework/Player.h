#ifndef PLAYER_H
#define PLAYER_H

#include "Resource.h"

class Player : public Resource
{
public:
	Player();
	virtual ~Player();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignValues(glm::vec2 _pos, float _speed, float _scale);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	glm::vec2 GetPos();
	bool IsFacingLeft();

	static ObjectPool<Player>* Pool;

private:
	glm::vec2 m_pos;
	float m_speed;
	float m_scale;
	bool m_facingLeft;
};

#endif

