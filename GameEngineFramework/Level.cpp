#include "Level.h"
#include "GameController.h"
#include "Renderer.h"
#include "TTFont.h"
#include "InputController.h"
#include "Keyboard.h"
#include "SoundEffect.h"
#include "Timing.h"
#include "SpriteSheet.h"
#include "SpriteAnim.h"
#include "SoundEffect.h"
#include "AudioController.h"

Level::Level() {
	AssetController::Instance().Initialize(10000000);
	m_quit = false;
	m_sdlEvent = { };
	m_renderer = nullptr;
	m_fArial20 = nullptr;
	m_input = nullptr;
	m_audio = nullptr;
	m_effect = nullptr;

	m_playerSpeed = 0.0f;
	m_NPCSpeed = 0.0f;
	m_playerScale = 0.0f;
	m_NPCScale = 0.0f;
	m_numberOfNPCs = 0;
	m_enemiesTagged = 0;
	m_isMoving = false;

	m_player = nullptr;
	m_npcs.clear();
	
	NPC::Pool = new ObjectPool<NPC>();
}

Level::~Level() {
	m_npcs.clear();
	delete NPC::Pool;
	if (m_player) {
		delete m_player;
		m_player = nullptr;
	}
	if (m_fArial20) {
		delete m_fArial20;
		m_fArial20 = nullptr;
	}
	AssetController::Instance().Clear();
}

void Level::SetDefaultValues(int _numberOfNPCs) {
	srand(static_cast<unsigned>(time(nullptr)));
	
	m_playerSpeed = 1000.0f;
	m_NPCSpeed = 600.0f;
	m_playerScale = 1.25f;
	m_NPCScale = 1.25f;
	m_numberOfNPCs = 10;
	m_enemiesTagged = 0;
	m_isMoving = false;

	glm::vec2 centre = { 960, 540 };

	m_player = new Player();
	m_player->AssignValues(centre, m_playerSpeed, m_playerScale);

	for (int i = 0; i < m_numberOfNPCs; i++) {
		NPC* npc = NPC::Pool->GetResource();
		float npcX = Level::GetRandomFloat(0.0f, 1920.0f);
		float npcY = Level::GetRandomFloat(0.0f, 1080.0f);
		glm::vec2 startingPos = { npcX, npcY };
		glm::vec2 direction = centre - startingPos;
		if (glm::length(centre - startingPos) > 150) {
			startingPos = glm::normalize(startingPos) * 150;
			startingPos += centre;
		}
		npc->AssignValues(startingPos, m_NPCSpeed, m_NPCScale);
		m_npcs.push_back(npc);
	}
}

void Level::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_playerSpeed), sizeof(m_playerSpeed));
	_stream.write(reinterpret_cast<char*>(&m_NPCSpeed), sizeof(m_NPCSpeed));
	_stream.write(reinterpret_cast<char*>(&m_playerScale), sizeof(m_playerScale));
	_stream.write(reinterpret_cast<char*>(&m_NPCScale), sizeof(m_NPCScale));
	_stream.write(reinterpret_cast<char*>(&m_numberOfNPCs), sizeof(m_numberOfNPCs));
	_stream.write(reinterpret_cast<char*>(&m_enemiesTagged), sizeof(m_enemiesTagged));
	SerializePointer(_stream, m_player);
	int numberOfNPCs = m_npcs.size();
	_stream.write(reinterpret_cast<char*>(&numberOfNPCs), sizeof(numberOfNPCs));
	for (int count = 0; count < numberOfNPCs; count++) {
		SerializePointer(_stream, m_npcs[count]);
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	_stream.read(reinterpret_cast<char*>(&m_playerSpeed), sizeof(m_playerSpeed));
	_stream.read(reinterpret_cast<char*>(&m_NPCSpeed), sizeof(m_NPCSpeed));
	_stream.read(reinterpret_cast<char*>(&m_playerScale), sizeof(m_playerScale));
	_stream.read(reinterpret_cast<char*>(&m_NPCScale), sizeof(m_NPCScale));
	_stream.read(reinterpret_cast<char*>(&m_numberOfNPCs), sizeof(m_numberOfNPCs));
	_stream.read(reinterpret_cast<char*>(&m_enemiesTagged), sizeof(m_enemiesTagged));
	DeserializePointer(_stream, m_player);
	int numberofNPCS;
	_stream.read(reinterpret_cast<char*>(&numberofNPCS), sizeof(numberofNPCS));
	for (int count = 0; count < numberofNPCS; count++) {
		NPC* npc = NPC::Pool->GetResource();
		DeserializePointer(_stream, npc);
		m_npcs.push_back(npc);
	}
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;
	cout << "Player Speed: " << m_playerSpeed << endl;
	cout << "NPC Speed: " << m_NPCSpeed << endl;
	cout << "Player Scale: " << m_playerScale << endl;
	cout << "NPC Scale: " << m_NPCScale << endl;
	cout << "Number of NPCS: " << m_numberOfNPCs << endl;
	cout << "Enemies tagged: " << m_enemiesTagged << endl;
	for (int count = 0; count < m_npcs.size(); count++) {
		m_npcs[count]->ToString();
	}
	Resource::ToString();
}

float Level::GetRandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

void Level::HandleInput(SDL_Event _event, float deltaTime) {
	if ((m_sdlEvent.type == SDL_QUIT) || (m_input->KB()->KeyUp(_event, SDLK_ESCAPE))) {
		m_quit = true;
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_i)) {
		if (m_NPCSpeed < 600) {
			m_NPCSpeed += 100;
			for (int i = 0; i < m_npcs.size(); i++) {
				m_npcs[i]->SetSpeed(m_NPCSpeed);
			}
		}
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_d)) {
		if (m_NPCSpeed > 0) {
			m_NPCSpeed -= 100;
			for (int i = 0; i < m_npcs.size(); i++) {
				m_npcs[i]->SetSpeed(m_NPCSpeed);
			}
		}
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_s)) {
		ofstream writeStream("level.bin", ios::out | ios::binary);
		Serialize(writeStream);
		writeStream.close();
	}
	else if (m_input->KB()->KeyUp(_event, SDLK_l)) {
		ifstream readStream("level.bin", ios::in | ios::binary);
		Deserialize(readStream);
		readStream.close();
	}

	if (m_input->KB()->KeyDown(_event, SDLK_UP)) {
		m_player->MoveUp(deltaTime);
		m_isMoving = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_DOWN)) {
		m_player->MoveDown(deltaTime);
		m_isMoving = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_LEFT)) {
		m_player->MoveLeft(deltaTime);
		m_isMoving = true;
	}
	else if (m_input->KB()->KeyDown(_event, SDLK_RIGHT)) {
		m_player->MoveRight(deltaTime);
		m_isMoving = true;
	}
	else {
		m_isMoving = false;
	}
}

void Level::RunLevel() {
	m_renderer = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	m_renderer->Initialize();
	
	m_fArial20 = new TTFont();
	m_fArial20->Initialize(20);
	m_input = &InputController::Instance();
	m_audio = &AudioController::Instance();

	m_effect = m_audio->LoadEffect("../Assets/Audio/Effects/Whoosh.wav");

	// Object Pools
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

	SpriteSheet* warriorSheet = SpriteSheet::Pool->GetResource();
	warriorSheet->Load("../Assets/Textures/Warrior.tga");
	warriorSheet->SetSize(17, 6, 69, 44);
	warriorSheet->AddAnimation(EN_AN_IDLE, 0, 6, 1);
	warriorSheet->AddAnimation(EN_AN_RUN, 6, 8, 1);
	warriorSheet->AddAnimation(EN_AN_DEATH, 26, 11, 1);

	int totalEnemies = m_numberOfNPCs;

	// Game Loop
	while (!m_quit) {
		t->Tick();

		m_renderer->SetDrawColor(Color(255, 255, 255, 255));
		m_renderer->ClearScreen();

		while (SDL_PollEvent(&m_sdlEvent) != 0) {
			HandleInput(m_sdlEvent, t->GetDeltaTime());
		}

		for (int i = 0; i < m_npcs.size(); i++) {
			if (!m_npcs[i]->IsTagged()) {
				glm::vec2 distance = m_npcs[i]->GetPos() - m_player->GetPos();
				if (glm::length(distance) < 30) {
					m_npcs[i]->SetTagged(true);
					m_audio->Play(m_effect);
					m_enemiesTagged++;
				}
			}
		}

		for (int i = 0; i < m_npcs.size(); i++) {
			if (m_npcs[i]->IsTagged()) {
				if (m_npcs[i]->GetTaggedTimer() >= 1.0f) {
					m_numberOfNPCs--;
				}
			}
		}

		if (m_enemiesTagged >= totalEnemies) {
			m_quit = 1;
		}

		for (int i = 0; i < m_npcs.size(); i++) {
			m_npcs[i]->Update(t->GetDeltaTime(), m_player->GetPos());
		}

		string keyPressInfoTest = "[D]ecrease speed [I]ncrease speed [S]ave [L]oad [ESC] Quit";
		m_fArial20->Write(m_renderer->GetRenderer(), keyPressInfoTest.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 100, 20 });

		string playerSpeedText = "Player speed: " + to_string(m_playerSpeed/10);
		m_fArial20->Write(m_renderer->GetRenderer(), playerSpeedText.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 100, 40 });

		string enemySpeedText = "Enemy speed: " + to_string(m_NPCSpeed/10);
		m_fArial20->Write(m_renderer->GetRenderer(), enemySpeedText.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 100, 60 });

		string enemiesTaggedText = "Enemies tagged: " + to_string(m_enemiesTagged);
		m_fArial20->Write(m_renderer->GetRenderer(), enemiesTaggedText.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 100, 80 });

		if (m_isMoving) {
			m_renderer->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().x + 69 * m_playerScale, m_player->GetPos().y + 44 * m_playerScale));
		}
		else {
			m_renderer->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().x + 69 * m_playerScale, m_player->GetPos().y + 44 * m_playerScale));
		}
		
		for (int i = 0; i < m_npcs.size(); i++) {
			if (m_npcs[i]->IsTagged() && m_npcs[i]->GetTaggedTimer() < 1.0f) {
				m_renderer->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(m_npcs[i]->GetPos().x, m_npcs[i]->GetPos().y, m_npcs[i]->GetPos().x + 69 * m_NPCScale, m_npcs[i]->GetPos().y + 44 * m_NPCScale));
			}
			else {
				if (m_isMoving) {
					m_renderer->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(m_npcs[i]->GetPos().x, m_npcs[i]->GetPos().y, m_npcs[i]->GetPos().x + 69 * m_NPCScale, m_npcs[i]->GetPos().y + 44 * m_NPCScale));
				}
				else {
					m_renderer->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(m_npcs[i]->GetPos().x, m_npcs[i]->GetPos().y, m_npcs[i]->GetPos().x + 69 * m_NPCScale, m_npcs[i]->GetPos().y + 44 * m_NPCScale));
				}
			}
		}

		SDL_RenderPresent(m_renderer->GetRenderer());
		t->CapFPS();
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	m_fArial20->Shutdown();
	m_renderer->Shutdown();
}