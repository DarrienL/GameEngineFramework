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
	void AssignValues(float _posX, float _posY, float _speed, float _scale);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	float GetPosX();
	float GetPosY();
	bool IsFacingLeft();

private:
	float m_posX;
	float m_posY;
	float m_speed;
	float m_scale;
	bool m_facingLeft;
};

#endif

