#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "RenderTarget.h"

GameController::GameController() {
    m_sdlEvent = { };
}

GameController::~GameController() { }

void GameController::RunGame() {
    Renderer* r = &Renderer::Instance();
    Timing* t = &Timing::Instance();
    r->Initialize();
    r->EnumerateDisplayModes();

    TTFont* font20 = new TTFont();
    font20->Initialize(20);

    while (m_sdlEvent.type != SDL_QUIT) {
        t->Tick();

        r->SetDrawColor(Color(255, 255, 255, 255));
        r->ClearScreen();
        
        std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
        font20->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });
        vector<SDL_DisplayMode> nodes = r->GetResolutions();
        for (int count = 0; count < nodes.size(); count++) {
            stringstream s;
            s << nodes[count].w << "x" << nodes[count].h << " " << nodes[count].refresh_rate << "hz";
            font20->Write(r->GetRenderer(), s.str().c_str(), SDL_Color{ 255, 128,0 }, SDL_Point{ 0, 20 + count * 20 });
        }

        SDL_RenderPresent(r->GetRenderer());

        t->CapFPS();
    }

    font20->Shutdown();
    r->Shutdown();
}
