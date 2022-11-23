add_executable(inserter
	main.cpp
	
	bitmap/Bitmap.h
	bitmap/Bitmap.cpp
	bitmap/BitmapFileHeader.h
	bitmap/BitmapFileHeader.cpp
	bitmap/BitmapInfo.h
	bitmap/BitmapInfo.cpp
	bitmap/Param.h
	bitmap/Param.cpp
	bitmap/ParamChar.h
	bitmap/ParamChar.cpp
	bitmap/ParamLong.h
	bitmap/ParamLong.cpp

	image/ImageBMP.h
	image/ImageBMP.cpp
	image/ImageYUV.h
	image/ImageYUV.cpp
)

target_include_directories(inserter
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${CMAKE_SOURCE_DIR}
)
