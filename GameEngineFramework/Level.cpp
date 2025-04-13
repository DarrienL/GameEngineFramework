#include "Level.h"

Level::Level() {

}

Level::~Level() {

}

void Level::Serialize(std::ostream& _stream) {

}

void Level::Deserialize(std::istream& _stream) {

}

void Level::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}