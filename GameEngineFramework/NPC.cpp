#include "NPC.h"

NPC::NPC() {
    m_pos = { 0, 0 };
    m_speed = 0.0f;
    m_scale = 0.0f;
    m_facingLeft = 0;
    m_tagged = 0;
    m_taggedTimer = 0.0f;
}

NPC::~NPC() {

}

void NPC::Serialize(std::ostream& _stream) {
    _stream.write(reinterpret_cast<char*>(&m_pos), sizeof(m_pos));
    _stream.write(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
    _stream.write(reinterpret_cast<char*>(&m_scale), sizeof(m_scale));
    _stream.write(reinterpret_cast<char*>(&m_facingLeft), sizeof(m_facingLeft));
    _stream.write(reinterpret_cast<char*>(&m_tagged), sizeof(m_tagged));
    _stream.write(reinterpret_cast<char*>(&m_taggedTimer), sizeof(m_taggedTimer));
}

void NPC::Deserialize(std::istream& _stream) {
    _stream.read(reinterpret_cast<char*>(&m_pos), sizeof(m_pos));
    _stream.read(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
    _stream.read(reinterpret_cast<char*>(&m_scale), sizeof(m_scale));
    _stream.read(reinterpret_cast<char*>(&m_facingLeft), sizeof(m_facingLeft));
    _stream.read(reinterpret_cast<char*>(&m_tagged), sizeof(m_tagged));
    _stream.read(reinterpret_cast<char*>(&m_taggedTimer), sizeof(m_taggedTimer));
}

void NPC::ToString() {
    cout << "NPC" << endl;
    Resource::ToString();
}

void NPC::AssignValues(glm::vec2 _pos, float _speed, float _scale) {
    m_pos = _pos;
    m_speed = _speed;
    m_scale = _scale;
}

void NPC::Update(float deltaTime, glm::vec2 playerPos) {
    if (!m_tagged) {
        glm::vec2 direction = playerPos - m_pos;
        if (direction.x < 0) {
            m_facingLeft = 1;
        }
        else {
            m_facingLeft = 0;
        }
        if (glm::length(direction) < 140) {
            m_pos -= glm::normalize(direction) * m_speed * deltaTime;
        }
        else if (glm::length(direction) > 160) {
            m_pos += glm::normalize(direction) * m_speed * deltaTime;
        }
    }
    else {
        if (m_taggedTimer < 1.0f) {
            m_taggedTimer += deltaTime;
        }
        else {
            if (m_pos.x != -999) {
                m_pos.x = -999;
            }
        }
    }
}

glm::vec2 NPC::GetPos() {
    return m_pos;
}


bool NPC::IsFacingLeft() {
    return m_facingLeft;
}

bool NPC::IsTagged() {
    return m_tagged;
}

void NPC::SetTagged(bool _tagged) {
    m_tagged = _tagged;
}

int NPC::GetTaggedCount() {
    return m_taggedTimer;
}