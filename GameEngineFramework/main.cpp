#include "Level.h"


int main() {
	Level* level = new Level();
	level->AssignNonDefaultValues();
	level->ToString();

	bool loopActive = 1;
	while (loopActive) {
		char userInput;
		cout << endl;
		cout << "[Q]uit [S]ave level [L]oad Level [Z] Undo [Y] Redo" << endl;
		cout << "[C]reate image buffer [D]elete image buffer [A]dd chunk [R]emove chunk" << endl;
		cout << "Index (0) Undo Count (0) Redo Count (0)" << endl;
		cout << endl;
		cin >> userInput;
		cout << endl;
		
		switch (toupper(userInput)) {
		case 'Q':
		{
			loopActive = 0;
			break;
		}
		case 'S': 
		{
			ofstream writeStream("level.bin", ios::out | ios::binary);
			level->Serialize(writeStream);
			writeStream.close();
			cout << "Level Saved: ";
			level->ToString();
			delete level;
			cout << endl;
			break;
		}
		case 'L':
		{
			Level* level = new Level();
			ifstream readStream("level.bin", ios::in | ios::binary);
			level->Deserialize(readStream);
			readStream.close();
			cout << "Loaded Level: ";
			level->ToString();
			break;
		}
		case 'Z':
		{
			cout << "Not currently implemented." << endl;
			break;
		}
		case 'Y':
		{
			cout << "Not currently implemented." << endl;
			break;
		}
		case 'C':
		{
			level->CreateImageBuffer();
			break;
		}
		case 'D':
		{
			level->DeleteImageBuffer();
			break;
		}
		case 'A':
		{
			level->AddChunkToBuffer();
			break;
		}
		case 'R':
		{
			level->RemoveChunkFromBuffer();
			break;
		}
		}

	}

	delete level;

}