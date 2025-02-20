#include "Level.h"

Level::Level() {
	m_sdlEvent = { };
	AssetController::Instance().Initialize(10000000);
	m_backgroundColor = Color(0, 0, 0, 255);
	m_hasRocks = false;
	m_autosaved = false;
	m_elapsedTime = 0.0f;
	m_elapsedTimeSeconds = 0;
	for (int i = 0; i < 10; i++) {
		m_warriorXPos[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		m_warriorSpeed[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		m_rockYPos[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		m_rockSpeed[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		m_warriorIsAlive[i] = true;
	}
	for (int i = 0; i < 10; i++) {
		m_rockExists[i] = true;
	}
	for (int i = 0; i < 10; i++) {
		m_warriorDeathTimer[i] = 0;
	}
}

Level::~Level() {
	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues(Color backgroundColor, bool hasRocks, bool autosaved) {
	srand(static_cast<unsigned>(time(nullptr)));
	m_backgroundColor = backgroundColor;
	m_hasRocks = hasRocks;
	m_autosaved = autosaved;
	for (int i = 0; i < 10; i++) {
		m_warriorXPos[i] = 100;
	}
	for (int i = 0; i < 10; i++) {
		m_warriorSpeed[i] = Level::GetRandomFloat(4.8f, 6.0f);
	}
	for (int i = 0; i < 10; i++) {
		m_rockYPos[i] = 100;
	}
	for (int i = 0; i < 10; i++) {
		m_rockSpeed[i] = Level::GetRandomFloat(4.8f, 6.0f);
	}
}

void Level::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_backgroundColor), sizeof(m_backgroundColor));
	_stream.write(reinterpret_cast<char*>(&m_hasRocks), sizeof(m_hasRocks));
	_stream.write(reinterpret_cast<char*>(&m_autosaved), sizeof(m_autosaved));
	_stream.write(reinterpret_cast<char*>(&m_elapsedTime), sizeof(m_elapsedTime));
	_stream.write(reinterpret_cast<char*>(&m_elapsedTimeSeconds), sizeof(m_elapsedTimeSeconds));
	for (int i = 0; i < 10; i++) {
		_stream.write(reinterpret_cast<char*>(&m_warriorXPos[i]), sizeof(m_warriorXPos[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.write(reinterpret_cast<char*>(&m_warriorSpeed[i]), sizeof(m_warriorSpeed[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.write(reinterpret_cast<char*>(&m_rockYPos[i]), sizeof(m_rockYPos[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.write(reinterpret_cast<char*>(&m_warriorIsAlive[i]), sizeof(m_warriorIsAlive[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.write(reinterpret_cast<char*>(&m_rockExists[i]), sizeof(m_rockExists[i]));
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	_stream.read(reinterpret_cast<char*>(&m_backgroundColor), sizeof(m_backgroundColor));
	_stream.read(reinterpret_cast<char*>(&m_hasRocks), sizeof(m_hasRocks));
	_stream.read(reinterpret_cast<char*>(&m_autosaved), sizeof(m_autosaved));
	_stream.read(reinterpret_cast<char*>(&m_elapsedTime), sizeof(m_elapsedTime));
	_stream.read(reinterpret_cast<char*>(&m_elapsedTimeSeconds), sizeof(m_elapsedTimeSeconds));
	for (int i = 0; i < 10; i++) {
		_stream.read(reinterpret_cast<char*>(&m_warriorXPos[i]), sizeof(m_warriorXPos[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.read(reinterpret_cast<char*>(&m_warriorSpeed[i]), sizeof(m_warriorSpeed[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.read(reinterpret_cast<char*>(&m_rockYPos[i]), sizeof(m_rockYPos[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.read(reinterpret_cast<char*>(&m_warriorIsAlive[i]), sizeof(m_warriorIsAlive[i]));
	}
	for (int i = 0; i < 10; i++) {
		_stream.read(reinterpret_cast<char*>(&m_rockExists[i]), sizeof(m_rockExists[i]));
	}
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}

float Level::GetRandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

void Level::RunLevel() {
	
	// Renderer and timing
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	r->Initialize(1920, 1080);

	// Font
	TTFont* font20 = new TTFont();
	font20->Initialize(20);

	Point ws = r->GetWindowSize();

	// Object Pools
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

	// Warrior Sprite Sheet with Different Animation Speeds
	SpriteSheet* warriorSheet = SpriteSheet::Pool->GetResource();
	warriorSheet->Load("../Assets/Textures/Warrior.tga");
	warriorSheet->SetSize(17, 6, 69, 44);
	warriorSheet->AddAnimation(EN_AN_RUN0, 6, 8, m_warriorSpeed[0]);
	warriorSheet->AddAnimation(EN_AN_RUN1, 6, 8, m_warriorSpeed[1]);
	warriorSheet->AddAnimation(EN_AN_RUN2, 6, 8, m_warriorSpeed[2]);
	warriorSheet->AddAnimation(EN_AN_RUN3, 6, 8, m_warriorSpeed[3]);
	warriorSheet->AddAnimation(EN_AN_RUN4, 6, 8, m_warriorSpeed[4]);
	warriorSheet->AddAnimation(EN_AN_RUN5, 6, 8, m_warriorSpeed[5]);
	warriorSheet->AddAnimation(EN_AN_RUN6, 6, 8, m_warriorSpeed[6]);
	warriorSheet->AddAnimation(EN_AN_RUN7, 6, 8, m_warriorSpeed[7]);
	warriorSheet->AddAnimation(EN_AN_RUN8, 6, 8, m_warriorSpeed[8]);
	warriorSheet->AddAnimation(EN_AN_RUN9, 6, 8, m_warriorSpeed[9]);
	warriorSheet->AddAnimation(EN_AN_DEATH, 26, 11, 1);

	// Rock Sprite Sheet
	SpriteSheet* rockSheet = SpriteSheet::Pool->GetResource();
	rockSheet->Load("../Assets/Textures/Rock.tga");
	rockSheet->SetSize(1, 4, 20, 20);
	rockSheet->AddAnimation(ROCK, 0, 1, 1);

	// Game Loop
	while (m_sdlEvent.type != SDL_QUIT) {
		t->Tick();

		SDL_PollEvent(&m_sdlEvent);
		r->SetDrawColor(m_backgroundColor);
		r->ClearScreen();

		/*
		// Quit if Not Autosaved and Elapsed Time >= 5 Seconds
		if (!m_autosaved && m_elapsedTime >= 5.0f) {
			m_sdlEvent.type = SDL_QUIT;
		}*/

		// Quit if A Warrior Goes Off-Screen
		for (int i = 0; i < 10; i++) {
			if (m_warriorXPos[i] >= 1920) {
				m_sdlEvent.type = SDL_QUIT;
			}
		}

		// Quit if All Warriors Dead
		if (m_warriorXPos[0] == -9999 && m_warriorXPos[1] == -9999 && m_warriorXPos[2] == -9999 && m_warriorXPos[3] == -9999 && m_warriorXPos[4] == -9999 && m_warriorXPos[5] == -9999 && m_warriorXPos[6] == -9999 && m_warriorXPos[7] == -9999 && m_warriorXPos[8] == -9999 && m_warriorXPos[9] == -9999) {
			m_sdlEvent.type = SDL_QUIT;
		}

		// Frames Per Second
		std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
		font20->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 200, 70 });

		// Game Time
		m_elapsedTime += t->GetDeltaTime();
		m_elapsedTimeSeconds = static_cast<int>(m_elapsedTime);
		std::string gt = "Game Time: " + std::to_string(m_elapsedTimeSeconds);
		font20->Write(r->GetRenderer(), gt.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 500, 70 });
		
		// Auto Save Status
		std::string saved = "Auto Saved: " + std::string(m_autosaved ? "Yes" : "No");
		font20->Write(r->GetRenderer(), saved.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 700, 70 });

		// Warrior Movement
		for (int i = 0; i < 10; i++) {
			m_warriorXPos[i] += m_warriorSpeed[i] * 16.67f * t->GetDeltaTime();
		}

		// Render Warriors
		if (m_warriorIsAlive[0]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN0, t->GetDeltaTime()), Rect(m_warriorXPos[0], 110, m_warriorXPos[0] + 69 * 1.8, 110 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[0], 110, m_warriorXPos[0] + 69 * 1.8, 110 + 44 * 1.8));
			m_warriorDeathTimer[0] += t->GetDeltaTime();
			if (m_warriorDeathTimer[0] > 1.0f) {
				m_warriorXPos[0] = -9999;
			}
		}

		if (m_warriorIsAlive[1]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN1, t->GetDeltaTime()), Rect(m_warriorXPos[1], 210, m_warriorXPos[1] + 69 * 1.8, 210 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[1], 210, m_warriorXPos[1] + 69 * 1.8, 210 + 44 * 1.8));
			m_warriorDeathTimer[1] += t->GetDeltaTime();
			if (m_warriorDeathTimer[1] > 1.0f) {
				m_warriorXPos[1] = -9999;
			}
		}

		if (m_warriorIsAlive[2]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN2, t->GetDeltaTime()), Rect(m_warriorXPos[2], 310, m_warriorXPos[2] + 69 * 1.8, 310 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[2], 310, m_warriorXPos[2] + 69 * 1.8, 310 + 44 * 1.8));
			m_warriorDeathTimer[2] += t->GetDeltaTime();
			if (m_warriorDeathTimer[2] > 1.0f) {
				m_warriorXPos[2] = -9999;
			}
		}

		if (m_warriorIsAlive[3]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN3, t->GetDeltaTime()), Rect(m_warriorXPos[3], 410, m_warriorXPos[3] + 69 * 1.8, 410 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[3], 410, m_warriorXPos[3] + 69 * 1.8, 410 + 44 * 1.8));
			m_warriorDeathTimer[3] += t->GetDeltaTime();
			if (m_warriorDeathTimer[3] > 1.0f) {
				m_warriorXPos[3] = -9999;
			}
		}

		if (m_warriorIsAlive[4]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN4, t->GetDeltaTime()), Rect(m_warriorXPos[4], 510, m_warriorXPos[4] + 69 * 1.8, 510 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[4], 510, m_warriorXPos[4] + 69 * 1.8, 510 + 44 * 1.8));
			m_warriorDeathTimer[4] += t->GetDeltaTime();
			if (m_warriorDeathTimer[4] > 1.0f) {
				m_warriorXPos[4] = -9999;
			}
		}

		if (m_warriorIsAlive[5]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN5, t->GetDeltaTime()), Rect(m_warriorXPos[5], 610, m_warriorXPos[5] + 69 * 1.8, 610 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[5], 610, m_warriorXPos[5] + 69 * 1.8, 610 + 44 * 1.8));
			m_warriorDeathTimer[5] += t->GetDeltaTime();
			if (m_warriorDeathTimer[5] > 1.0f) {
				m_warriorXPos[5] = -9999;
			}
		}

		if (m_warriorIsAlive[6]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN6, t->GetDeltaTime()), Rect(m_warriorXPos[6], 710, m_warriorXPos[6] + 69 * 1.8, 710 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[6], 710, m_warriorXPos[6] + 69 * 1.8, 710 + 44 * 1.8));
			m_warriorDeathTimer[6] += t->GetDeltaTime();
			if (m_warriorDeathTimer[6] > 1.0f) {
				m_warriorXPos[6] = -9999;
			}
		}

		if (m_warriorIsAlive[7]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN7, t->GetDeltaTime()), Rect(m_warriorXPos[7], 810, m_warriorXPos[7] + 69 * 1.8, 810 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[7], 810, m_warriorXPos[7] + 69 * 1.8, 810 + 44 * 1.8));
			m_warriorDeathTimer[7] += t->GetDeltaTime();
			if (m_warriorDeathTimer[7] > 1.0f) {
				m_warriorXPos[7] = -9999;
			}
		}

		if (m_warriorIsAlive[8]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN8, t->GetDeltaTime()), Rect(m_warriorXPos[8], 910, m_warriorXPos[8] + 69 * 1.8, 910 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[8], 910, m_warriorXPos[8] + 69 * 1.8, 910 + 44 * 1.8));
			m_warriorDeathTimer[8] += t->GetDeltaTime();
			if (m_warriorDeathTimer[8] >= 1) {
				m_warriorXPos[8] = -9999;
			}
		}

		if (m_warriorIsAlive[9]) {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN9, t->GetDeltaTime()), Rect(m_warriorXPos[9], 1010, m_warriorXPos[9] + 69 * 1.8, 1010 + 44 * 1.8));
		}
		else {
			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_warriorXPos[9], 1010, m_warriorXPos[9] + 69 * 1.8, 1010 + 44 * 1.8));
			m_warriorDeathTimer[9] += t->GetDeltaTime();
			if (m_warriorDeathTimer[9] > 1.0f) {
				m_warriorXPos[9] = -9999;
			}
		}

		// Level 2 Logic
		if (m_hasRocks) {

			// Rock Movement
			for (int i = 0; i < 10; i++) {
				m_rockYPos[i] += m_rockSpeed[i] * 16.67f * t->GetDeltaTime();
			}

			// Render Rock + Check If Collision with Warrior
			for (int i = 0; i < 10; i++) {
				if (m_rockExists[i]) {
					r->RenderTexture(rockSheet, rockSheet->Update(ROCK, t->GetDeltaTime()), Rect((((i + 1) * 100) + 200), m_rockYPos[i], (((i + 1) * 100) + 200) + 40, m_rockYPos[i] + 40));
					for (int j = 0; j < 10; j++) {
						if (m_rockYPos[i] >= ((j * 100) + 110) && m_rockYPos[i] <= ((j * 100) + 130)) {
							if (m_warriorXPos[j] >= (((i + 1) * 100) + 180) && m_warriorXPos[j] <= (((i + 1) * 100) + 220)) {
								m_rockExists[i] = false;
								m_warriorSpeed[j] = 0;
								m_warriorIsAlive[j] = false;
								m_warriorDeathTimer[j] = 0;
							}
						}
					}
				}
			}
		}

		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font20->Shutdown();
	r->Shutdown();
}

void Level::SetAutosaved(bool autosaved) {
	m_autosaved = autosaved;
}