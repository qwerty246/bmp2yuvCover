#include <image/ImageBMP.h>
#include <image/ImageYUV.h>

#include <iostream>
#include <assert.h>

#ifdef WIN32
# include <direct.h>
# define GetCurrentDir _getcwd
#else
# include <unistd.h>
# define GetCurrentDir getcwd
#endif

std::string GetCurDir()
{
	char pBuf[FILENAME_MAX];
	char* pRes = GetCurrentDir(pBuf, FILENAME_MAX);
	assert(pRes == pBuf);
	return std::string(pBuf);
}

int main(int argc, char* argv[])
{
	if (argc != 6 && argc != 3)
	{
		std::cout << std::string("Usage: ") + argv[0] + " <filename1>" +
														" <filename2>" +
														" <width>" +
														" <height>" +
														" <frames>" << std::endl;
		std::cout << "<filename1>: BMP image filename" << std::endl;
		std::cout << "<filename2>: YUV image filename" << std::endl;
		std::cout << "    <width>: YUV image file width" << std::endl;
		std::cout << "   <height>: YUV image file height" << std::endl;
		std::cout << "   <frames>: YUV image file frames" << std::endl;
		exit(0);
	}

	ulong lWidth, lHeight, lFrames;
	if (argc == 3)
	{
		// CIF
		lWidth = 352;
		lHeight = 288;
		lFrames = 1;
	}
	else
	{
		try
		{
			lWidth = std::stoi(argv[3]);
			lHeight = std::stoi(argv[4]);
			lFrames = std::stoi(argv[5]);
		}
		catch (...)
		{
			std::cout << "Invalid parameters." << std::endl;
			return 1;
		}
	}

    ImageBMP fileBMP;
	if (!fileBMP.OpenAndReadFile(GetCurDir() + "\\" + argv[1]))
    {
		if (!fileBMP.OpenAndReadFile(argv[1]))
		{
            std::cout << std::string("Error: unable to open file \"") + argv[1] + "\"." << std::endl;
			return 1;
		}
	}

	ImageYUV fileYUV;
	if (!fileYUV.OpenFile(GetCurDir() + "\\" + argv[2], lWidth, lHeight, lFrames))
	{
		if (!fileYUV.OpenFile(argv[2], lWidth, lHeight, lFrames))
		{
            std::cout << std::string("Error: unable to open file \"") + argv[1] + "\"." << std::endl;
			return 1;
		}
	}
	if (!fileYUV.OverlayImage(fileBMP))
	{
		return 1;
	}

	return 0;
}
