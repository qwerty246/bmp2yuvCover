#pragma once

#include "ImageBMP.h"
#include <bitmap/BitmapFileHeader.h>
#include <bitmap/BitmapInfo.h>

#include <fstream>
#include <string>
#include <mutex>

class ImageYUV
{
public:
	ImageYUV();
	~ImageYUV();

	bool OpenFile(std::string sFileName, unsigned long uWidth, unsigned long uHeight, unsigned long uFrames);
	bool OverlayImage(const ImageBMP& file);
private:
	void OverlayImageOnFrame(const ImageBMP& file, unsigned long uFrame);

	unsigned long _uWidth;
	unsigned long _uHeight;
	unsigned long _uFrames;
	bool _bIsOpened;

	std::ofstream _ofstream;
	std::mutex _mutex;
};
