#include "Asset.h"
#include "AssetController.h"


int main() {
	AssetController::Instance().Initialize(10000000); // Allocated 10MB
	Asset* asset = AssetController::Instance().GetAsset("emoji.jpg");
	cout << "Bytes used by image.bmp: " << AssetController::Stack->GetBytesUsed() << endl;
}