#ifndef FILECHUNK_H
#define FILECHUNK_H

#include "Resource.h"

class Asset;

class FileChunk : public Resource
{
public:
	// Constructor/Destructor
	FileChunk();
	virtual ~FileChunk();

	// Accessor
	Asset* GetChunk() { return m_chunk; }
	void SetChunk(Asset* _part) { m_chunk = _part; }

	// Methods
	virtual void Serialize(std::ostream& _stream) override;
	virtual void Deserialize(std::istream& _stream) override;
	virtual void ToString() override;
	virtual void AssignNonDefaultValues() override;
	void LoadChunk(int chunkNumber);

	static ObjectPool <FileChunk>* Pool;

private:
	Asset* m_chunk;
};
#endif

