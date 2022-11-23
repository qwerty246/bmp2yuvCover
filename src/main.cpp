#include <image/ImageBMP.h>
#include <image/ImageYUV.h>

#include <iostream>

#ifdef WIN32
# include <direct.h>
# define GetCurrentDir _getcwd
#else
# include <unistd.h>
# define GetCurrentDir getcwd
#endif

std::string GetCurDir()
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	return std::string(buff);
}

int main(int argc, char* argv[])
{
	if (argc != 6)
	{
		std::cout << std::string("Usage: ") + argv[0] + " <filename1>" +
														" <filename2>" +
														" <width>" +
														" <height>" +
														" <frames>" << std::endl;
		std::cout << "<filename1>: bmp image filename" << std::endl;
		std::cout << "<filename2>: yuv image filename" << std::endl;
		std::cout << "    <width>: yuv image file width" << std::endl;
		std::cout << "   <height>: yuv image file height" << std::endl;
		std::cout << "   <frames>: yuv image file frames" << std::endl;
		exit(0);
	}
	unsigned long uWidth, uHeight, uFrames;
	try
	{
		uWidth = std::stoi(argv[3]);
		uHeight = std::stoi(argv[4]);
		uFrames = std::stoi(argv[5]);
	}
	catch (...)
	{
		std::cout << "Invalid parameters." << std::endl;
		return 1;
	}

	ImageBMP fileBMP;
	if (!fileBMP.OpenAndReadFile(GetCurDir() + "\\" + argv[1]))
	{
		if (!fileBMP.OpenAndReadFile(argv[1]))
		{
			std::cout << std::string("File \"") + argv[1] + "\" can't be read." << std::endl;
			return 1;
		}
	}

	ImageYUV fileYUV;

	if (!fileYUV.OpenFile(GetCurDir() + "\\" + argv[2], uWidth, uHeight, uFrames))
	{
		if (!fileYUV.OpenFile(argv[2], uWidth, uHeight, uFrames))
		{
			std::cout << std::string("File \"") + argv[2] + "\" can't be read." << std::endl;
			return 1;
		}
	}
	if (!fileYUV.OverlayImage(fileBMP))
	{
		std::cout << "An error occurred while writing the file." << std::endl;
		return 1;
	}

	return 0;
}
