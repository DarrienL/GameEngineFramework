#ifndef NPC_H
#define NPC_H

#include "Resource.h"

class NPC : public Resource
{
public:
	NPC();
	virtual ~NPC();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignValues(glm::vec2 _pos, float _speed, float _scale);
	void Update(float deltaTime, glm::vec2 playerPos);
	glm::vec2 GetPos();
	bool IsFacingLeft();
	bool IsTagged();
	void SetTagged(bool _tagged);
	int GetTaggedCount();

private:
	glm::vec2 m_pos;
	float m_speed;
	float m_scale;
	bool m_facingLeft;
	bool m_tagged;
	float m_taggedTimer;
};

#endif

