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

	bool OpenFile(std::string sFileName, ulong lWidth, ulong lHeight, ulong lFrames);
	bool OverlayImage(const ImageBMP& file);
private:
	void OverlayImageOnFrame(const ImageBMP& file, ulong lFrame);
	uchar GetSum(double dR, double dG, double dB, short nX) const;

	ulong m_lWidth;
	ulong m_lHeight;
	ulong m_lFrames;
	bool m_bIsOpened;
	std::ofstream m_ofstream;
	std::mutex m_mutex;
	std::string m_sFileName;
};
