#include "Player2State.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "Player2.h"
#include "SpriteSheet.h"

IdleState Player2State::m_idle;
RollingState Player2State::m_rolling;
PaperState Player2State::m_paper;
ScissorsState Player2State::m_scissors;
RockState Player2State::m_rock;

void Player2State::HandleInput(Player2* _player, SDL_Event _event) {
	// Keyboard Input
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_UP) && (_player->GetRigidBody()->GetPosition().y) <= 0) {
		_player->GetRigidBody()->SetPosition((_player->GetRigidBody()->GetPosition()) + glm::vec2(0, -10));
	}
	else if (InputController::Instance().KB()->KeyDown(_event, SDLK_LEFT) && (_player->GetRigidBody()->GetPosition().x) <= 0) {
		_player->GetRigidBody()->SetPosition((_player->GetRigidBody()->GetPosition()) + glm::vec2(-10, 0));
	}
	else if (InputController::Instance().KB()->KeyDown(_event, SDLK_DOWN) && (_player->GetRigidBody()->GetPosition().y) >= 910) {
		_player->GetRigidBody()->SetPosition((_player->GetRigidBody()->GetPosition()) + glm::vec2(0, 10));
	}
	else if (InputController::Instance().KB()->KeyDown(_event, SDLK_RIGHT) && (_player->GetRigidBody()->GetPosition().x) >= 1640) {
		_player->GetRigidBody()->SetPosition((_player->GetRigidBody()->GetPosition()) + glm::vec2(10, 0));
	}

	// Mouse Input
	InputController::Instance().MS()->ProcessButtons(_event);
	if (InputController::Instance().MS()->GetButRDown()) {
		if (InputController::Instance().MS()->Moved(_event, m_mPos)) {
			_player->GetRigidBody()->SetPosition(glm::vec2(m_mPos.X + 140, m_mPos.Y + 85));
		}
	}

	// Controller Input
	if (InputController::Instance().CT()->ProcessMotion(_event)) {
		// Get controller analog stick data and modify position
	}
}

void IdleState::HandleInput(Player2* _player, SDL_Event _event) {
	Player2State::HandleInput(_player, _event);
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE)) {
		_player->SetState(Player2State::GetRollingState());
		_player->SetOutcome("Rolling...");
	}
}

void IdleState::Update(Player2* _player, float _deltaTime) {
	_player->GetAnimations()->Update(EN_AN_RPS_IDLE, _deltaTime, _player->GetSrcRect());
}

void RollingState::HandleInput(Player2* _player, SDL_Event _event) {
	Player2State::HandleInput(_player, _event);
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE)) {
		int rolled = _player->RNG();
		_player->SetStatus(rolled);
		switch (rolled) {
		case 1:
			_player->SetState(Player2State::GetRockState());
			break;
		case 2:
			_player->SetState(Player2State::GetPaperState());
			break;
		case 3:
			_player->SetState(Player2State::GetScissorsState());
			break;
		}
	}
}

void RollingState::Update(Player2* _player, float _deltaTime) {
	_player->GetAnimations()->Update(EN_AN_RPS_ROLL, _deltaTime, _player->GetSrcRect());
}

void PaperState::HandleInput(Player2* _player, SDL_Event _event) {
	Player2State::HandleInput(_player, _event);
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE)) {
		_player->SetState(Player2State::GetIdleState());
		_player->SetOutcome("Waiting to start...");
	}
}

void PaperState::Update(Player2* _player, float _deltaTime) {
	_player->GetAnimations()->Update(EN_AN_RPS_PAPER, _deltaTime, _player->GetSrcRect());
}

void ScissorsState::HandleInput(Player2* _player, SDL_Event _event) {
	Player2State::HandleInput(_player, _event);
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE)) {
		_player->SetState(Player2State::GetIdleState());
		_player->SetOutcome("Waiting to start...");
	}
}

void ScissorsState::Update(Player2* _player, float _deltaTime) {
	_player->GetAnimations()->Update(EN_AN_RPS_SCISSORS, _deltaTime, _player->GetSrcRect());
}

void RockState::HandleInput(Player2* _player, SDL_Event _event) {
	Player2State::HandleInput(_player, _event);
	if (InputController::Instance().KB()->KeyDown(_event, SDLK_SPACE)) {
		_player->SetState(Player2State::GetIdleState());
		_player->SetOutcome("Waiting to start...");
	}
}

void RockState::Update(Player2* _player, float _deltaTime) {
	_player->GetAnimations()->Update(EN_AN_RPS_ROCK, _deltaTime, _player->GetSrcRect());
}
