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

	bool OpenFile(std::string sFileName, ulong uWidth, ulong uHeight, ulong uFrames);
	bool OverlayImage(const ImageBMP& file);
private:
	void OverlayImageOnFrame(const ImageBMP& file, ulong uFrame);
	uchar GetSum(double R, double G, double B, short x) const;

	ulong _uWidth;
	ulong _uHeight;
	ulong _uFrames;
	bool _bIsOpened;

	std::ofstream _ofstream;
	std::mutex _mutex;
	std::string _sFileName;
};
