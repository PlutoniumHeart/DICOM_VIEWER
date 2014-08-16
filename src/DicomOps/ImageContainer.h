#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H


#include "ImageCommon.h"


class ImageContainer
{
public:
    ImageContainer();
    virtual ~ImageContainer();

    void SetDimension(unsigned int dim);
    unsigned int GetDimension();
    ShortImageType::Pointer* GetImage();
    DICOMIOType::Pointer* GetIOObject();
    short GetWidth();
    short GetHeight();
    short GetLength();
    short GetDefaultWC();
    short GetDefaultWW();
    void SetCurrentWC(short wc);
    short GetCurrentWC();
    void SetCurrentWW(short ww);
    short GetCurrentWW();
    std::string GetPatientName();
    std::string GetStudyInstanceUID();

private:
    unsigned int m_uiDim;
    ShortImageType::Pointer m_sImageObj;
    DICOMIOType::Pointer m_DicomIO;
    short m_sCurrentWC;
    short m_sCurrentWW;

};


#endif // IMAGECONTAINER_H
