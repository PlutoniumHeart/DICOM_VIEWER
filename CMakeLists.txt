cmake_minimum_required( VERSION 2.8 )

project ( DICOM_Tool )

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
else(ITK_FOUND)
  message(FATAL_ERROR "ITK not found. Please set ITK_DIR. ")
endif(ITK_FOUND)

include_directories(src/include)

set(SOURCES src/main.cpp 
            src/include/ImageCommon.h
            src/include/ImageIO.h src/ImageIO.cpp
            src/include/ImageFilter.h src/ImageFilter.cpp
)

set(ALL_LIBS ${ITK_LIBRARIES})

add_executable(DICOM_Tool ${SOURCES})

target_link_libraries(DICOM_Tool ${ALL_LIBS})
