#include "Player.h"

Player::Player() {
    m_posX = 0.0f;
    m_posY = 0.0f;
    m_speed = 0.0f;
    m_scale = 0.0f;
    m_facingLeft = 0;
}

Player::~Player(){

}

void Player::Serialize(std::ostream& _stream) {
    _stream.write(reinterpret_cast<char*>(&m_posX), sizeof(m_posX));
    _stream.write(reinterpret_cast<char*>(&m_posY), sizeof(m_posY));
    _stream.write(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
    _stream.write(reinterpret_cast<char*>(&m_scale), sizeof(m_scale));
    _stream.write(reinterpret_cast<char*>(&m_facingLeft), sizeof(m_facingLeft));
}

void Player::Deserialize(std::istream& _stream) {
    _stream.read(reinterpret_cast<char*>(&m_posX), sizeof(m_posX));
    _stream.read(reinterpret_cast<char*>(&m_posY), sizeof(m_posY));
    _stream.read(reinterpret_cast<char*>(&m_speed), sizeof(m_speed));
    _stream.read(reinterpret_cast<char*>(&m_scale), sizeof(m_scale));
    _stream.read(reinterpret_cast<char*>(&m_facingLeft), sizeof(m_facingLeft));
}

void Player::ToString() {
    cout << "PLAYER" << endl;
    Resource::ToString();
}

void Player::AssignValues(float _posX, float _posY, float _speed, float _scale) {
    m_posX = _posX;
    m_posY = _posY;
    m_speed = _speed;
    m_scale = _scale;
}

void Player::MoveUp(float deltaTime) {
    m_posY -= m_speed * deltaTime;
}

void Player::MoveDown(float deltaTime) {
    m_posY += m_speed * deltaTime;
}

void Player::MoveLeft(float deltaTime) {
    m_posX -= m_speed * deltaTime;
    m_facingLeft = 1;
}

void Player::MoveRight(float deltaTime) {
    m_posX += m_speed * deltaTime;
    m_facingLeft = 0;
}

float Player::GetPosX() {
    return m_posX;
}

float Player::GetPosY() {
    return m_posY;
}

bool Player::IsFacingLeft() {
    return m_facingLeft;
}