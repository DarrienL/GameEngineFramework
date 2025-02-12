#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"

GameController::GameController() {
    m_sdlEvent = { };
}

GameController::~GameController() {}

void GameController::RunGame() {
    AssetController::Instance().Initialize(10000000); // Allocate 10MB
    Renderer* r = &Renderer::Instance();
    r->Initialize(800, 600);

    TTFont* font20 = new TTFont();
    font20->Initialize(20);

    Point ws = r->GetWindowSize();

    SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
    SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
    SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
    sheet->Load("../Assets/Textures/Warrior.tga");
    sheet->SetSize(17, 6, 69, 44);
    sheet->AddAnimation(EN_AN_IDLE, 0, 6, 0.01f);
    sheet->AddAnimation(EN_AN_RUN, 6, 8, 0.005f);

    while (m_sdlEvent.type != SDL_QUIT) {
        SDL_PollEvent(&m_sdlEvent);
        r->SetDrawColor(Color(255, 255, 255, 255));
        r->ClearScreen();
        r->RenderTexture(sheet, sheet->Update(EN_AN_IDLE), Rect(0, 0, 69 * 3, 44 * 3));
        r->RenderTexture(sheet, sheet->Update(EN_AN_RUN), Rect(0, 150, 69 * 3, 150 + 44 * 3));
        font20->Write(r->GetRenderer(), "Testing 123!", SDL_Color{ 0, 255, 0 }, SDL_Point{ 150, 50 });
        SDL_RenderPresent(r->GetRenderer());
    }

    delete SpriteAnim::Pool;
    delete SpriteSheet::Pool;

    font20->Shutdown();
    r->Shutdown();
}
