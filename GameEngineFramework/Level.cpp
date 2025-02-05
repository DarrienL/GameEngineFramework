#include "Level.h"

Level::Level() {
	AssetController::Instance().Initialize(10000000);
	FileChunk::Pool = new ObjectPool<FileChunk>();

	m_chunks.clear();
	m_imageBuffer = nullptr;
	m_imageBufferSize = 0;
}

Level::~Level() {
	m_chunks.clear();
	delete FileChunk::Pool;
	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {
	for (int count = 0; count < 7; count++) {
		FileChunk* chunk = FileChunk::Pool->GetResource();
		chunk->AssignNonDefaultValues();
		m_chunks.push_back(chunk);
	}
	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.write(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));
	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	int numberOfUnits = m_units.size();
	_stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++) {
		SerializePointer(_stream, m_units[count]);
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	_stream.read(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.read(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));
	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	int numberOfUnits;
	_stream.read(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++) {
		Unit* unit;
		DeserializePointer(_stream, unit);
		m_units.push_back(unit);
	}
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;
	cout << "MapSizeX: " << m_mapSizeX << endl;
	cout << "MapSizeY: " << m_mapSizeY << endl;
	cout << "GameTime: " << m_gameTime << endl;
	for (int count = 0; count < m_units.size(); count++) {
		m_units[count]->ToString();
	}
	Resource::ToString();
}