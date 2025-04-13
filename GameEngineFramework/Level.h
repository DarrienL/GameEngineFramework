#ifndef LEVEL_H
#define LEVEL_H

#include "Resource.h"

class Level : public Resource
{
public:
	// Constructors/Destructors
	Level();
	virtual ~Level();

	// Methods
	virtual void Initialize() { };
	virtual void Shutdown() { };
	virtual void HandleInput(SDL_Event _event) { };
	virtual void Run() { };
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
};

#endif
