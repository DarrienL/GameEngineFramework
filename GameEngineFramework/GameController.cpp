#include "GameController.h"
#include "Renderer.h"
#include "InputController.h"
#include "Timing.h"
#include "PhysicsController.h"
#include "Level1.h"

GameController::GameController() {
    m_renderer = nullptr;
    m_audio = nullptr;
    m_input = nullptr;
    m_physics = nullptr;
    m_timing = nullptr;
    m_level1 = nullptr;
    m_song = nullptr;
}

GameController::~GameController() {
    ShutDown();
}

void GameController::Initialize() {
    AssetController::Instance().Initialize(20000000); // Allocate 20MB
    m_renderer = &Renderer::Instance();
    m_renderer->Initialize();
    m_audio = &AudioController::Instance();
    m_input = &InputController::Instance();
    m_physics = &PhysicsController::Instance();
    m_timing = &Timing::Instance();
    m_level1 = new Level1;
    m_song = m_audio->LoadSong("../Assets/Audio/Music/Track1.mp3");
}

void GameController::ShutDown() {
    if (m_level1 != nullptr) {
        delete m_level1;
        m_level1 = nullptr;
    }

    if (m_song != nullptr) {
        delete m_song;
        m_song = nullptr;
    }
}

void GameController::RunGame() {
    Initialize();
    m_audio->Play(m_song);
    m_level1->Run(m_renderer);
    m_audio->StopMusic();
    ShutDown();
}
