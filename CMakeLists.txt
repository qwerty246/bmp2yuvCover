CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(bmp2yuvCover)

ADD_EXECUTABLE(bmp2yuvCover
	include/bitmap/Bitmap.h
	include/bitmap/BitmapFileHeader.h
	include/bitmap/BitmapInfo.h
	include/bitmap/Param.h
	include/bitmap/ParamChar.h
	include/bitmap/ParamLong.h
	include/image/ImageBMP.h
	include/image/ImageYUV.h

	src/bitmap/Bitmap.cpp
	src/bitmap/BitmapFileHeader.cpp
	src/bitmap/BitmapInfo.cpp
	src/bitmap/Param.cpp
	src/bitmap/ParamChar.cpp
	src/bitmap/ParamLong.cpp
	src/image/ImageBMP.cpp
	src/image/ImageYUV.cpp
	src/main.cpp
)

TARGET_INCLUDE_DIRECTORIES(bmp2yuvCover
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
