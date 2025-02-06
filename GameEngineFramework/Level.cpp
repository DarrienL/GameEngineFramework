#include "Level.h"

Level::Level() {
	AssetController::Instance().Initialize(100000000);
	FileChunk::Pool = new ObjectPool<FileChunk>();

	m_chunks.clear();
	m_imageBuffer = nullptr;
	m_imageBufferSize = 0;
	m_currentChunkIndex = 0;
}

Level::~Level() {
	m_chunks.clear();
	delete FileChunk::Pool;
	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {
	for (int count = 0; count < 7; count++) {
		FileChunk* chunk = FileChunk::Pool->GetResource();
		chunk->LoadChunk(count);
		m_chunks.push_back(chunk);
		cout << "Allocating asset chunk" + to_string(count) + ".bin" << endl;
	}
	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
	int numberOfUnits = m_chunks.size();
	_stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++) {
		SerializePointer(_stream, m_chunks[count]);
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	int numberOfUnits;
	_stream.read(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++) {
		FileChunk* chunk;
		DeserializePointer(_stream, chunk);
		m_chunks.push_back(chunk);
	}
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}

void Level::SaveImageBuffer() {
	if (m_imageBufferSize == 0) {
		cout << "No image buffer to save." << endl;
		return;
	}
	ofstream writeStream("NewImage.tga", ios::out | ios::binary);
	writeStream.write(reinterpret_cast<char*>(m_imageBuffer), m_imageBufferSize);
	writeStream.close();
	cout << "Saveing image NewImage.tga" << endl;
}

void Level::CreateImageBuffer() {
	m_imageBufferSize = 0;
	for (FileChunk* chunk : m_chunks) {
		if (chunk->GetChunk()) {
			m_imageBufferSize += chunk->GetChunk()->GetDataSize();
		}
	}
	M_ASSERT((m_imageBufferSize != 0), "No chunks loaded")
	m_imageBuffer = new char[m_imageBufferSize];
	memset(m_imageBuffer, 0, m_imageBufferSize);
	cout << "Executing: CommandCreateImageBuffer" << endl;
	SaveImageBuffer();
}

void Level::DeleteImageBuffer() {
	delete[] m_imageBuffer;
	m_imageBuffer = nullptr;
	m_imageBufferSize = 0;
	m_currentChunkIndex = 0;
	cout << "Executing: CommandDeleteImageBuffer" << endl;
}

void Level::AddChunkToBuffer() {
	FileChunk* chunk = m_chunks[m_currentChunkIndex];
	size_t chunkSize = chunk->GetChunk()->GetDataSize();
	size_t offset = 0;
	for (size_t i = 0; i < m_currentChunkIndex; i++) {
		offset += m_chunks[i]->GetChunk()->GetDataSize();
	}
	memcpy(m_imageBuffer + offset, chunk->GetChunk()->GetData(), chunkSize);
	m_currentChunkIndex++;
	cout << "Executing: CommandAddChunk" << endl;
}

void Level::RemoveChunkFromBuffer() {
	m_currentChunkIndex--;
	FileChunk* chunk = m_chunks[m_currentChunkIndex];
	size_t chunkSize = chunk->GetChunk()->GetDataSize();
	size_t offset = 0;
	for (size_t i = 0; i < m_currentChunkIndex; i++) {
		offset += m_chunks[i]->GetChunk()->GetDataSize();
	}
	memset(m_imageBuffer + offset, 0, chunkSize);
	SaveImageBuffer();
	cout << "Executing: CommandRemoveChunk" << endl;
}