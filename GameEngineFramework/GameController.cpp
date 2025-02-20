#include "GameController.h"
#include "Level.h"

using namespace std;

GameController::GameController() { }

GameController::~GameController() { }

void GameController::RunGame() {
    
    Level* level1 = new Level();
    level1->AssignNonDefaultValues(Color(128, 128, 128, 255), false, false);
    level1->RunLevel();

    
    ofstream writeStream("level1.bin", ios::out | ios::binary);
    level1->Serialize(writeStream);
    writeStream.close();
    delete level1;

    Level* level1Load = new Level();
    ifstream readStream("level1.bin", ios::in | ios::binary);
    level1Load->Deserialize(readStream);
    readStream.close();

    level1Load->SetAutosaved(true);
    level1Load->RunLevel();
    delete level1Load;

    Level* level2 = new Level();
    level2->AssignNonDefaultValues(Color(0, 128, 0, 255), true, false);
    level2->RunLevel();

    ofstream writeStream("level2.bin", ios::out | ios::binary);
    level2->Serialize(writeStream);
    writeStream.close();
    delete level2;

    Level* level2Load = new Level();
    ifstream readStream("level2.bin", ios::in | ios::binary);
    level2Load->Deserialize(readStream);
    readStream.close();

    level2Load->SetAutosaved(true);
    level2Load->RunLevel();
    delete level2Load;
}
