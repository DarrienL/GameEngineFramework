#include "FileChunk.h"

ObjectPool<FileChunk>* FileChunk::Pool = nullptr;

FileChunk::FileChunk() {
	m_chunk = nullptr;
}

FileChunk::~FileChunk() {}

void FileChunk::AssignNonDefaultValues() {
	// m_soundEffect = SoundEffect::Pool->GetResource();
	// m_soundEffect->AssignNonDefaultValues();
	// Resource::AssignNonDefaultValues();
}

void FileChunk::Serialize(std::ostream& _stream) {
	SerializePointer(_stream, m_chunk);
	Resource::Serialize(_stream);
}

void FileChunk::Deserialize(std::istream& _stream) {
	DeserializePointer(_stream, m_chunk);
	Resource::Deserialize(_stream);
}

void FileChunk::ToString() {
	cout << "test" << endl;
	Resource::ToString();
}