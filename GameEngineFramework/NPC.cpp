#include "NPC.h"

ObjectPool<NPC>* NPC::Pool;

NPC::NPC() {
    m_pos = { 0, 0 };
    m_speed = 0.0f;
    m_scale = 0.0f;
    m_facingLeft = 0;
    m_tagged = 0;
    m_taggedTimer = 0.0f;
    m_orientation = 0.0f;
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

// Apply changable values
void NPC::AssignValues(glm::vec2 _pos, float _speed, float _scale) {
    m_pos = _pos;
    m_speed = _speed;
    m_scale = _scale;
}

// Update NPC position/tagged timer/orientation
void NPC::Update(float deltaTime, glm::vec2 playerPos) {
    if (!m_tagged) { // If not tagged
        glm::vec2 direction = playerPos - m_pos; // Direction to player
        if (direction.x < 0) {
            m_facingLeft = 1; // Set facing left to true (player is to the left)
        }
        else {
            m_facingLeft = 0; // Set facing left to false (player is to the right)
        }
        if (glm::length(direction) < 140) { // If distance less than 140
            m_pos -= glm::normalize(direction) * m_speed * deltaTime; // Move away from player
        }
        else if (glm::length(direction) > 160) { // If distance greater than 160
            m_pos += glm::normalize(direction) * m_speed * deltaTime; // Move towards player
        }
        m_orientation = acos(glm::dot({ 0, 0 }, direction)); // Calculate angle to orientate NPC towards player
    }
    else { // If tagged
        if (m_taggedTimer < 1.0f) { // If taggedTimer less than 1.0
            m_taggedTimer += deltaTime; // Add deltaTime to taggedTimer
        }
        else { // If taggedTimer >= 1.0
            if (m_pos.x != -999) { // If position.x isn't already -999
                m_pos.x = -999; // Set to -999 (offscreen)
            }
        }
    }
}

// Return NPC position
glm::vec2 NPC::GetPos() {
    return m_pos;
}

// Return if NPC should be facing left
bool NPC::IsFacingLeft() {
    return m_facingLeft;
}

// Return if NPC has been tagged
bool NPC::IsTagged() {
    return m_tagged;
}

// Set NPC tagged bool
void NPC::SetTagged(bool _tagged) {
    m_tagged = _tagged;
}

// Return NPC tagged timer
float NPC::GetTaggedTimer() {
    return m_taggedTimer;
}

// Set NPC speed
void NPC::SetSpeed(float _speed) {
    m_speed = _speed;
}

// Return NPC orientation
float NPC::GetOrientation() {
    return m_orientation;
}