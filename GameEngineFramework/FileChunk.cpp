#include "FileChunk.h"

ObjectPool<FileChunk>* FileChunk::Pool = nullptr;

FileChunk::FileChunk() {
	m_chunk = nullptr;
}

FileChunk::~FileChunk() {}

void FileChunk::AssignNonDefaultValues() {
	m_chunk = AssetController::Instance().GetAsset("chunk0.bin");
	Resource::AssignNonDefaultValues();
}

void FileChunk::Serialize(std::ostream& _stream) {
	SerializeAsset(_stream, m_chunk);
	Resource::Serialize(_stream);
}

void FileChunk::Deserialize(std::istream& _stream) {
	DeserializeAsset(_stream, m_chunk);
	Resource::Deserialize(_stream);
}

void FileChunk::ToString() {
	cout << "CHUNK" << endl;
	Resource::ToString();
}

void FileChunk::LoadChunk(int chunkNumber) {
	m_chunk = AssetController::Instance().GetAsset("chunk" + to_string(chunkNumber) + ".bin");
	// Resource::AssignNonDefaultValues();
}