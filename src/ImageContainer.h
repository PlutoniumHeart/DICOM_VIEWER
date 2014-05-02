#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H


#include <iostream>
#include <cstdlib>

#include "ImageIO.h"


class ImageContainer
{
public:
    ImageContainer();
    virtual ~ImageContainer();

    ShortImageType::Pointer* GetShortImagePointer();
    DICOMIOType::Pointer* GetIOObject();
    short GetImageWidth();
    short GetImageHeight();
    short GetDefaultWindowCenter();
    short GetDefaultWindowWidth();
    short GetWindowLowerBound();
    short GetWindowUpperBound();
    std::string GetPatientName();
    std::string GetStudyInstanceUID();
    
private:
    ShortImageType::Pointer m_sImageObj;
    DICOMIOType::Pointer m_DicomIO;
};


#endif // IMAGECONTAINER_H
