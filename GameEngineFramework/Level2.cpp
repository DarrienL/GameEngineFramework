#include "Level2.h"
#include "Player1.h"
#include "Player2.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timing.h"
#include "Renderer.h"
#include "PhysicsController.h"
#include "TTFont.h"

Level2::Level2() {
	m_sdlEvent = { };
	m_physics = nullptr;
	m_quit = false;
	m_saves = 0;
	m_loads = 0;
	m_elapsedTime = 0.0f;
	m_player1 = nullptr;
	m_player2 = nullptr;
}

Level2::~Level2() {
	Shutdown();
}

void Level2::Initialize(TTFont* _font, string _names[]) {
	m_physics = &PhysicsController::Instance();
	m_player1 = new Player1();
	m_player1->Initialize(_font, _names[0]);
	m_player2 = new Player2();
	m_player2->Initialize(_font, _names[1]);
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
}

void Level2::Shutdown() {
	if (m_player1 != nullptr) {
		delete m_player1;
		m_player1 = nullptr;
	}

	if (m_player2 != nullptr) {
		delete m_player2;
		m_player2 = nullptr;
	}

	if (SpriteAnim::Pool != nullptr) {
		delete SpriteAnim::Pool;
		SpriteAnim::Pool = nullptr;
	}

	if (SpriteSheet::Pool != nullptr) {
		delete SpriteSheet::Pool;
		SpriteSheet::Pool = nullptr;
	}
}

void Level2::HandleInput(SDL_Event _event) {
	if ((m_sdlEvent.type == SDL_QUIT) || (InputController::Instance().KB()->KeyUp(_event, SDLK_ESCAPE))) {
		m_quit = true;
	}
	else if (InputController::Instance().KB()->KeyUp(_event, SDLK_F5)) {
		ofstream writeStream("saveGame.bin", ios::out | ios::binary);
		Serialize(writeStream);
		writeStream.close();
	}
	else if (InputController::Instance().KB()->KeyUp(_event, SDLK_F7)) {
		ifstream readStream("saveGame.bin", ios::in | ios::binary);
		Deserialize(readStream);
		readStream.close();
	}

	m_player1->HandleInput(_event, Timing::Instance().GetDeltaTime());
	m_player2->HandleInput(_event, Timing::Instance().GetDeltaTime());
	InputController::Instance().MS()->ProcessButtons(_event);
}

void Level2::Run(Renderer* _renderer, TTFont* _font, string _names[]) {
	Initialize(_font, _names);

	while (!m_quit) {
		Timing::Instance().Tick();

		_renderer->SetDrawColor(Color(255, 255, 255, 255));
		_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0) {
			HandleInput(m_sdlEvent);
		}

		// Game logic
		if (m_player1->GetStatus() != 0) {
			if (m_player1->GetStatus() == m_player2->GetStatus()) {
				m_player1->Draw();
				m_player2->Draw();
			}
			else if (m_player1->GetStatus() == 1 && m_player1->GetStatus() == 2) {
				m_player1->Lose();
				m_player2->Win();
			}
			else if (m_player1->GetStatus() == 1 && m_player1->GetStatus() == 3) {
				m_player1->Win();
				m_player2->Lose();
			}
			else if (m_player1->GetStatus() == 2 && m_player1->GetStatus() == 1) {
				m_player1->Win();
				m_player2->Lose();
			}
			else if (m_player1->GetStatus() == 2 && m_player1->GetStatus() == 3) {
				m_player1->Lose();
				m_player2->Win();
			}
			else if (m_player1->GetStatus() == 3 && m_player1->GetStatus() == 1) {
				m_player1->Lose();
				m_player2->Win();
			}
			else if (m_player1->GetStatus() == 3 && m_player1->GetStatus() == 2) {
				m_player1->Win();
				m_player2->Lose();
			}
		}

		// Update physics and players
		m_physics->Update(Timing::Instance().GetDeltaTime());
		m_player1->Update(Timing::Instance().GetDeltaTime());
		m_player2->Update(Timing::Instance().GetDeltaTime());

		// Render players
		m_player1->Render(_renderer);
		m_player2->Render(_renderer);

		// Bottom info text
		string stats = "Frames Per Second: " + to_string(Timing::Instance().GetFPS());
		stats += "    Game Time: " + to_string(static_cast<int>(m_elapsedTime));
		stats += "    Saves: " + to_string(m_saves);
		stats += "    Loads: " + to_string(m_loads);
		_font->Write(_renderer->GetRenderer(), stats.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 1040 });
		string info = "Quit [ESC]    Next Game State [Space]    Save [F5]    Load [F7]";
		_font->Write(_renderer->GetRenderer(), info.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 1060 });

		SDL_RenderPresent(_renderer->GetRenderer());

		Timing::Instance().CapFPS();
	}
}
