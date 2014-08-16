cmake_minimum_required( VERSION 2.8 )

project ( DICOM_Tool )

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
else(ITK_FOUND)
  message(FATAL_ERROR "ITK not found. Please set ITK_DIR. ")
endif(ITK_FOUND)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x -fpermissive")

include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(src/DicomOps/)
include_directories(src/Toolbars/)
include_directories(src/CenterWidgets/)
include_directories(src/Docks/)
include_directories(src/)

set(SOURCES src/main.cpp 
            src/Window.h src/Window.cpp

            src/Toolbars/FileToolbar.h
            src/Toolbars/FileToolbar.cpp
            src/Toolbars/ResizeToolbar.h
            src/Toolbars/ResizeToolbar.cpp

            src/CenterWidgets/DisplayWidget.h
            src/CenterWidgets/DisplayWidget.cpp

            src/Docks/ImageWindowingDock.h
            src/Docks/ImageWindowingDock.cpp
            src/Docks/ImageListDock.h
            src/Docks/ImageListDock.cpp

            src/DicomOps/ImageCommon.h
            src/DicomOps/ImageIO.h
            src/DicomOps/ImageIO.cpp
            src/DicomOps/ImageFilter.h
            src/DicomOps/ImageFilter.cpp
            src/DicomOps/ImageContainer.h
            src/DicomOps/ImageContainer.cpp
            src/DicomOps/ImageHandler.h
            src/DicomOps/ImageHandler.cpp
)
set(RESOURCES src/DICOM_TOOL.qrc)

set(ALL_LIBS ${ITK_LIBRARIES}
             ${Qt5Widgets_LIBRARIES}
)

qt5_add_resources(Resources ${RESOURCES})

add_executable(DICOM_Tool ${SOURCES} ${Resources})

qt5_use_modules(DICOM_Tool Widgets Core PrintSupport OpenGL)

target_link_libraries(DICOM_Tool ${ALL_LIBS})
