#include "Player.h"

ObjectPool<Player>* Player::Pool;

Player::Player() {
    m_pos = { 0, 0 };
    m_speed = 0.0f;
    m_scale = 0.0f;
    m_facingLeft = 0;
}

Player::~Player(){

}

void Player::Serialize(std::ostream& _stream) {
    _stream.write(reinterpret_cast<char*>(&m_pos), sizeof(m_pos));
    _stream.write(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
    _stream.write(reinterpret_cast<char*>(&m_scale), sizeof(m_scale));
    _stream.write(reinterpret_cast<char*>(&m_facingLeft), sizeof(m_facingLeft));
}

void Player::Deserialize(std::istream& _stream) {
    _stream.read(reinterpret_cast<char*>(&m_pos), sizeof(m_pos));
    _stream.read(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
    _stream.read(reinterpret_cast<char*>(&m_scale), sizeof(m_scale));
    _stream.read(reinterpret_cast<char*>(&m_facingLeft), sizeof(m_facingLeft));
}

void Player::ToString() {
    cout << "PLAYER" << endl;
    Resource::ToString();
}

void Player::AssignValues(glm::vec2 _pos, float _speed, float _scale) {
    m_pos = _pos;
    m_speed = _speed;
    m_scale = _scale;
}

void Player::MoveUp(float deltaTime) {
    m_pos.y -= m_speed * deltaTime;
}

void Player::MoveDown(float deltaTime) {
    m_pos.y += m_speed * deltaTime;
}

void Player::MoveLeft(float deltaTime) {
    m_pos.x -= m_speed * deltaTime;
    m_facingLeft = 1;
}

void Player::MoveRight(float deltaTime) {
    m_pos.x += m_speed * deltaTime;
    m_facingLeft = 0;
}

glm::vec2 Player::GetPos() {
    return m_pos;
}


bool Player::IsFacingLeft() {
    return m_facingLeft;
}