#include "GameController.h"

GameController::GameController() {

}

GameController::~GameController() { 

}

void GameController::RunGame() {
    Level* level1 = new Level(); // Create new level
    level1->ToString(); // Write values to console
    level1->SetDefaultValues(10); // Set default values (set number of NPCs to 10)
    level1->RunLevel(); // Run level
    delete level1; // Delete level
}
