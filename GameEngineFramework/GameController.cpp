#include "GameController.h"
#include "Renderer.h"
#include "TTFont.h"
#include "InputController.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "SoundEffect.h"
#include "Song.h"
#include "WavDraw.h"

GameController::GameController() {

}

GameController::~GameController() { 

}

void GameController::RunGame() {
    Level* level1 = new Level();
    level1->ToString();
    level1->SetDefaultValues(10);
    level1->RunLevel();
    delete level1;
}
