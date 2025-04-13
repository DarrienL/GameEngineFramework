#include "Player2.h"
#include "SpriteSheet.h"
#include "Renderer.h"
#include "PhysicsController.h"
#include "TTFont.h"

Player2::Player2() {
	m_playerName = "";
	m_outcome = "";
	m_wins = 0;
	m_losses = 0;
	m_status = 0;
	m_state = nullptr;
	m_rigidBody = nullptr;
	m_animations = nullptr;
	m_fArial20 = nullptr;
}

Player2::~Player2() {

}

void Player2::Initialize(TTFont* _font, string _name) {
	m_playerName = _name;
	m_outcome = "Waiting to start...";
	m_state = Player2State::GetIdleState();
	m_rigidBody = PhysicsController::Instance().AddRigidBody(glm::vec2{ 20, 330 }, glm::vec2(0, 0), 40);
	m_animations = SpriteSheet::Pool->GetResource();
	m_animations->Load("../Assets/Textures/RockPaperScissors.tga");
	m_animations->SetSize(4, 4, 280, 170);
	m_animations->AddAnimation(EN_AN_RPS_IDLE, 0, 1, 1.0f);
	m_animations->AddAnimation(EN_AN_RPS_ROLL, 0, 4, 1.0f);
	m_animations->AddAnimation(EN_AN_RPS_PAPER, 4, 4, 1.0f);
	m_animations->AddAnimation(EN_AN_RPS_SCISSORS, 8, 4, 1.0f);
	m_animations->AddAnimation(EN_AN_RPS_ROCK, 12, 4, 1.0f);
	m_animations->SetBlendMode(SDL_BLENDMODE_BLEND);
	m_fArial20 = _font;
}

void Player2::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_playerName), sizeof(m_playerName));
	_stream.write(reinterpret_cast<char*>(&m_outcome), sizeof(m_outcome));
	_stream.write(reinterpret_cast<char*>(&m_wins), sizeof(m_wins));
	_stream.write(reinterpret_cast<char*>(&m_losses), sizeof(m_losses));
	_stream.write(reinterpret_cast<char*>(&m_status), sizeof(m_status));
	SerializePointer(_stream, m_animations);
}

void Player2::Deserialize(std::istream& _stream) {
	_stream.read(reinterpret_cast<char*>(&m_playerName), sizeof(m_playerName));
	_stream.read(reinterpret_cast<char*>(&m_outcome), sizeof(m_outcome));
	_stream.read(reinterpret_cast<char*>(&m_wins), sizeof(m_wins));
	_stream.read(reinterpret_cast<char*>(&m_losses), sizeof(m_losses));
	_stream.read(reinterpret_cast<char*>(&m_status), sizeof(m_status));
	DeserializePointer(_stream, m_animations);
}

void Player2::ToString() {
	cout << "PLAYER 2" << endl;
	Resource::ToString();
}

void Player2::HandleInput(SDL_Event _event, float _deltaTime) {
	m_state->HandleInput(this, _event);
}

void Player2::Update(float _deltaTime) {
	m_state->Update(this, _deltaTime);
}

void Player2::Render(Renderer* _renderer) {
	glm::vec2 p = m_rigidBody->GetPosition();
	Rect destRect = Rect(p.x, p.y, p.x + 280, p.y + 170);
	_renderer->RenderTexture(m_animations, m_srcRect, destRect);
	m_fArial20->Write(_renderer->GetRenderer(), m_playerName.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ (int)p.x, (int)p.y });
	m_fArial20->Write(_renderer->GetRenderer(), m_outcome.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ (int)p.x, (int)p.y + 20 });
	string ws = "Wins: " + to_string(m_wins);
	string ls = "Losses: " + to_string(m_losses);
	m_fArial20->Write(_renderer->GetRenderer(), ws.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ (int)p.x, (int)p.y + 40 });
	m_fArial20->Write(_renderer->GetRenderer(), ls.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ (int)p.x, (int)p.y + 60 });
}

void Player2::Draw() {
	m_status = 0;
	m_outcome = "DRAW!";
}

void Player2::Win() {
	m_wins++;
	m_status = 0;
	m_outcome = "WINNER!";
}

void Player2::Lose() {
	m_losses++;
	m_status = 0;
	m_outcome = "LOSER!";
}

int Player2::RNG() {
	return 1 + static_cast<int>(rand()) / RAND_MAX * (3 - 1);
}
