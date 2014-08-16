#include "ImageContainer.h"


ImageContainer::ImageContainer()
    : m_uiDim(0)
{
    m_sImageObj = ShortImageType::New();
    m_DicomIO = DICOMIOType::New();
}


ImageContainer::~ImageContainer()
{
}


void ImageContainer::SetDimension(unsigned int dim)
{
    m_uiDim = dim;
}


ShortImageType::Pointer* ImageContainer::GetImage()
{
    return &m_sImageObj;
}


DICOMIOType::Pointer* ImageContainer::GetIOObject()
{
    return &m_DicomIO;
}


short ImageContainer::GetWidth()
{
    return m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(0);
}

short ImageContainer::GetHeight()
{
    return m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(1);
}


short ImageContainer::GetLength()
{
    return m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(2);
}


short ImageContainer::GetDefaultWC()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0028|1050", temp);
    return atoi(temp.c_str());
}


short ImageContainer::GetDefaultWW()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0028|1051", temp);
    return atoi(temp.c_str());
}


std::string ImageContainer::GetPatientName()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0010|0010", temp);
    return temp;
}


std::string ImageContainer::GetStudyInstanceUID()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0020|000D", temp);
    return temp;
}


void ImageContainer::SetCurrentWC(short wc)
{
    m_sCurrentWC = wc;
}


short ImageContainer::GetCurrentWC()
{
    return m_sCurrentWC;
}


void ImageContainer::SetCurrentWW(short ww)
{
    m_sCurrentWW = ww;
}


short ImageContainer::GetCurrentWW()
{
    return m_sCurrentWW;
}
