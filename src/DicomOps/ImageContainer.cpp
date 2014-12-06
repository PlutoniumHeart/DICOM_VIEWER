#include "ImageContainer.h"


ImageContainer::ImageContainer()
    : m_uiDim(0)
    , m_sImageObj(NULL)
{
    m_DicomIO = DICOMIOType::New();
}


ImageContainer::~ImageContainer()
{
    if(m_sImageObj != NULL)
    {
        delete [] m_sImageObj;
        m_sImageObj = NULL;
    }
}


void ImageContainer::Allocate(int sliceNumber)
{
    if(m_sImageObj != NULL)
    {
        delete [] m_sImageObj;
        m_sImageObj = NULL;
    }
    m_sImageObj = new ShortImageType::Pointer[sliceNumber];
    for(int i=0;i<sliceNumber;i++)
    {
        m_sImageObj[i] = ShortImageType::New();
    }
}


void ImageContainer::SetDimension(unsigned int dim)
{
    m_uiDim = dim;
}


ShortImageType::Pointer* ImageContainer::GetImage(int slice)
{
    return &(m_sImageObj[slice]);
}


DICOMIOType::Pointer* ImageContainer::GetIOObject()
{
    return &m_DicomIO;
}


short ImageContainer::GetWidth(int slice)
{
    return m_sImageObj[slice]->GetLargestPossibleRegion().GetSize().GetElement(0);
}

short ImageContainer::GetHeight(int slice)
{
    return m_sImageObj[slice]->GetLargestPossibleRegion().GetSize().GetElement(1);
}


short ImageContainer::GetLength(int slice)
{
    return m_sImageObj[slice]->GetLargestPossibleRegion().GetSize().GetElement(2);
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
