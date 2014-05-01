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
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(src/include)

set(SOURCES src/main.cpp 
            src/include/ImageCommon.h
            src/include/ImageIO.h src/ImageIO.cpp
            src/include/ImageFilter.h src/ImageFilter.cpp
            src/include/glWidget.h src/glWidget.cpp
            src/include/Helper.h src/Helper.cpp
            src/include/Window.h src/Window.cpp
            src/include/ImageWindowingDock.h src/ImageWindowingDock.cpp
            src/include/ImageListDock.h src/ImageListDock.cpp
            src/include/ResizeToolBar.h src/ResizeToolBar.cpp
            src/include/FileToolBar.h src/FileToolBar.cpp
            src/include/ImageContainer.h src/ImageContainer.cpp
)
set(RESOURCES src/DICOM_TOOL.qrc)

set(ALL_LIBS ${ITK_LIBRARIES}
             ${Qt5Widgets_LIBRARIES}
)

qt5_add_resources(Resources ${RESOURCES})

add_executable(DICOM_Tool ${SOURCES} ${Resources})

qt5_use_modules(DICOM_Tool Widgets Core PrintSupport OpenGL)

target_link_libraries(DICOM_Tool ${ALL_LIBS})
