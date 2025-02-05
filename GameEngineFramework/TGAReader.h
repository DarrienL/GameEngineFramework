#ifndef TGA_READER_H
#define TGA_READER_H

#include "StandardIncludes.h"

class Asset;

#pragma pack(push,1) // ENable memory packing
typedef struct {
	char IDLength;
	char ColourMapType;
	char DataTypeCode;
	short ColourMapStart;
	short ColourMapLength;
	char ColourMapDepth;
	short x_Origin;
	short y_Origin;
	short Width;
	short Height;
	char BitsPerPixel;
	char ImageDescriptor;
} TGAHeader;
#pragma pack(pop) // Disable memory packing

typedef struct {
	short Width;
	short Height;
	short BitsPerPixel;
	short DataOffset;
} ImageInfo;

class TGAReader 
{
public:
	// Constructors/Destructors
	TGAReader();
	virtual ~TGAReader() {}

	// Methods
	void ProcessAsset(Asset* _rawTGA, ImageInfo* _ImageInfo);

};

#endif

