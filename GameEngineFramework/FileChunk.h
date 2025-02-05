#ifndef FILECHUNK_H
#define FILECHUNK_H

#include "Resource.h"

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
	virtual void Serialize(std::ostream& _stream);
	virtual void Deserialize(std::istream& _stream);
	virtual void ToString();
	virtual void AssignNonDefaultValues();

	static ObjectPool <FileChunk>* Pool;

private:
	Asset* m_chunk;
};
#endif

