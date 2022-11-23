#include "ImageYUV.h"

#include <iostream>
#include <vector>
#include <thread>

ImageYUV::ImageYUV() :
	_uWidth(0),
	_uHeight(0),
	_uFrames(0),
	_bIsOpened(false)
{
}

ImageYUV::~ImageYUV()
{
}

bool ImageYUV::OpenFile(std::string sFileName, unsigned long uWidth, unsigned long uHeight, unsigned long uFrames)
{
	_ofstream.open(sFileName, std::fstream::binary | std::fstream::in | std::fstream::out);
	if (!_ofstream)
	{
		_bIsOpened = false;
		return false;
	}
	_uWidth = uWidth;
	_uHeight = uHeight;
	_uFrames = uFrames;
	_bIsOpened = true;
	return true;
}

unsigned char GetSum(int R, int G, int B, int x)
{
	int sum = R + G + B + x;
	if (sum > 255)
	{
		return 255;
	}
	if (sum < 0)
	{
		return 0;
	}
	return sum;
}

bool ImageYUV::OverlayImage(const ImageBMP& file)
{
	if (!_bIsOpened)
	{
		return false;
	}
	if (file.GetWidth() > _uWidth)
	{
		return false;
	}
	if (file.GetHeight() > _uHeight)
	{
		return false;
	}
	std::vector <std::thread> vThreads;
	unsigned int maxThreads = std::thread::hardware_concurrency();
	size_t i = 0;
	try
	{
		while (i < _uFrames)
		{
			for (size_t j = 0; j < maxThreads && i < _uFrames; i++, j++)
			{
				vThreads.push_back(std::thread(&ImageYUV::OverlayImageOnFrame, this, std::ref(file), i));
			}
			for (std::thread& th : vThreads)
			{
				if (th.joinable())
				{
					th.join();
				}
			}
			vThreads.clear();
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void ImageYUV::OverlayImageOnFrame(const ImageBMP& file, unsigned long uFrame)
{
	if (uFrame > _uFrames)
	{
		return;
	}
	const char* pFileMap = file.GetDataMap();
	unsigned long long uPosPage = uFrame * _uWidth * _uHeight * 1.5;
	unsigned long long uPosU = _uWidth * _uHeight;
	unsigned long long uPosV = _uWidth * _uHeight * 1.25;
	for (size_t i = 0; i < file.GetHeight(); i++)
	{
		for (size_t j = 0; j < file.GetWidth(); j++)
		{
			unsigned char uR, uG, uB;
			uB = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j];
			uG = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j + 1];
			uR = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j + 2];

			unsigned char uY = GetSum(0.299 * uR, 0.587 * uG, 0.114 * uB, 0);

			_mutex.lock();
			_ofstream.seekp(uPosPage + i * _uWidth + j);
			_ofstream << uY;
			_mutex.unlock();
			if ((i % 2 == 0) &&
				(j % 2 == 0))
			{
				unsigned char uU = GetSum(-0.169 * uR, -0.331 * uG, 0.500 * uB, 128);
				unsigned char uV = GetSum(0.500 * uR, -0.419 * uG, -0.081 * uB, 128);
				_mutex.lock();
				_ofstream.seekp(uPosPage + uPosU + i * _uWidth / 4 + j / 2);
				_ofstream << uU;
				_ofstream.seekp(uPosPage + uPosV + i * _uWidth / 4 + j / 2);
				_ofstream << uV;
				_mutex.unlock();
			}
		}
	}
}
