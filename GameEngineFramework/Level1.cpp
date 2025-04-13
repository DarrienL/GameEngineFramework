#include "Level1.h"
#include "TTFont.h"
#include "Level2.h"
#include "Renderer.h"
#include "Texture.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timing.h"
#include "AudioController.h"

Level1::Level1() {
	m_sdlEvent = { };
	m_quit = false;
	m_playerNames[0] = "";
	m_playerNames[1] = "";
	m_currentName = 0;
	m_playLevel = false;
	m_displayError = false;
	m_level2 = nullptr;
	m_fArial20 = nullptr;
	m_fArial40 = nullptr;
	m_texture = nullptr;
}

Level1::~Level1() {
	Shutdown();
}

void Level1::Initialize() {
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_fArial40 = new TTFont();
	m_fArial40->Initialize(40);
	Texture::Pool = new ObjectPool<Texture>();
	m_texture = Texture::Pool->GetResource();
	m_texture->Load("../Assets/Textures/Background.tga");
	ToString();
}

void Level1::Shutdown() {
	if (m_fArial20 != nullptr) {
		delete m_fArial20;
		m_fArial20 = nullptr;
	}

	if (m_fArial40 != nullptr) {
		delete m_fArial40;
		m_fArial40 = nullptr;
	}

	if (Texture::Pool != nullptr) {
		delete Texture::Pool;
		Texture::Pool = nullptr;
	}
}

void Level1::HandleInput(SDL_Event _event) {
	string temp;
	if ((m_sdlEvent.type == SDL_QUIT) || (InputController::Instance().KB()->KeyUp(_event, SDLK_ESCAPE))) {
		m_quit = true;
	}
	else if ((temp = InputController::Instance().KB()->TextInput(_event)) != "") {
		m_playerNames[m_currentName] += temp;
		m_displayError = false;
	}
	else if (InputController::Instance().KB()->KeyUp(_event, SDLK_BACKSPACE)) {
		if (!m_playerNames[m_currentName].empty()) {
			m_playerNames[m_currentName].pop_back();
		}
	}
	else if (InputController::Instance().KB()->KeyUp(_event, SDLK_RETURN)) {
		if (m_playerNames[m_currentName].length() == 0 || m_playerNames[m_currentName].length() > 20) {
			m_displayError = true;
		}
		else {
			if (m_currentName == 0) {
				m_currentName = 1;
			}
			else if (m_currentName == 1) {
				m_playLevel = true;
				m_quit = true;
			}
		}
	}

	InputController::Instance().MS()->ProcessButtons(_event);
}

void Level1::Run(Renderer* _renderer) {
	Initialize();

	while (!m_quit) {
		Timing::Instance().Tick();

		_renderer->SetDrawColor(Color(100, 100, 100, 255));
		_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0) {
			HandleInput(m_sdlEvent);
		}

		// Render texture
		_renderer->RenderTexture(m_texture, Rect(0, 0, 1920, 1080));

		// Display names
		string label1 = "Enter Player 1 Nickname:";
		string label2 = "Enter Player 2 Nickname:";
		m_fArial20->Write(_renderer->GetRenderer(), label1.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 10, 10 });
		m_fArial20->Write(_renderer->GetRenderer(), label2.c_str(), SDL_Color{ 0, 0, 0 }, SDL_Point{ 10, 80 });
		m_fArial40->Write(_renderer->GetRenderer(), m_playerNames[0].c_str(), SDL_Color{ 255, 255, 0}, SDL_Point{ 20, 25 });
		m_fArial40->Write(_renderer->GetRenderer(), m_playerNames[1].c_str(), SDL_Color{ 255, 255, 0 }, SDL_Point{ 20, 95 });

		// Display error
		string errorText = "Nickname must not be empty and must have less than 21 characters";
		if (m_displayError) {
			m_fArial40->Write(_renderer->GetRenderer(), errorText.c_str(), SDL_Color{ 255, 0, 0 }, SDL_Point{ 10, 150 });
		}

		// Info
		string info = "Quit [ESC]    Next Nickname [RETURN]";
		m_fArial20->Write(_renderer->GetRenderer(), info.c_str(), SDL_Color{ 255, 255, 255 }, SDL_Point{ 0, 1060 });

		// FPS cap
		Timing::Instance().CapFPS();
	}

	if (m_playLevel) {
		m_level2 = new Level2;
		m_level2->Run(_renderer, m_fArial20, m_playerNames);
		delete m_level2;
	}
}

void Level1::ToString() {
	cout << "LEVEL 1" << endl;
	Level::ToString();
}