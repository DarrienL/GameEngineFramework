#ifndef LEVEL_H
#define LEVEL_H

#include "FileChunk.h"

class Level : public Resource
{
public:
	// Constructors/Destructors
	Level();
	virtual ~Level();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void CreateImageBuffer();
	void DeleteImageBuffer();
	void AddChunkToBuffer();
	void RemoveChunkFromBuffer();

private:
	// Members
	vector<FileChunk*> m_chunks;
	char* m_imageBuffer;
	size_t m_imageBufferSize;
};

#endif
