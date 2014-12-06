#include "ImageContainer.h"


ImageContainer::ImageContainer()
    : m_uiDim(0)
    , m_sImageObj(NULL)
    , m_DicomIO(NULL)
    , m_iActiveSlice(0)
    , m_iMinSliceNum(0)
    , m_iMaxSliceNum(0)
{
}


ImageContainer::~ImageContainer()
{
    if(m_sImageObj != NULL)
    {
        delete [] m_sImageObj;
        m_sImageObj = NULL;
    }

    if(m_DicomIO != NULL)
    {
        delete [] m_DicomIO;
        m_DicomIO = NULL;
    }
}


void ImageContainer::Allocate(int sliceNumber)
{
    if(m_sImageObj != NULL)
    {
        delete [] m_sImageObj;
        m_sImageObj = NULL;
    }
    if(m_DicomIO != NULL)
    {
        delete [] m_DicomIO;
        m_DicomIO = NULL;
    }
    m_sImageObj = new ShortImageType::Pointer[sliceNumber];
    m_DicomIO = new DICOMIOType::Pointer[sliceNumber];
    for(int i=0;i<sliceNumber;i++)
    {
        m_sImageObj[i] = ShortImageType::New();
        m_DicomIO[i] = DICOMIOType::New();
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


DICOMIOType::Pointer* ImageContainer::GetIOObject(int slice)
{
    return &m_DicomIO[slice];
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


short ImageContainer::GetDefaultWC(int slice)
{
    std::string temp;
    m_DicomIO[slice]->GetValueFromTag("0028|1050", temp);
    return atoi(temp.c_str());
}


short ImageContainer::GetDefaultWW(int slice)
{
    std::string temp;
    m_DicomIO[slice]->GetValueFromTag("0028|1051", temp);
    return atoi(temp.c_str());
}


std::string ImageContainer::GetPatientName(int slice)
{
    std::string temp;
    m_DicomIO[slice]->GetValueFromTag("0010|0010", temp);
    return temp;
}


std::string ImageContainer::GetStudyInstanceUID(int slice)
{
    std::string temp;
    m_DicomIO[slice]->GetValueFromTag("0020|000D", temp);
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


void ImageContainer::SetActiveSlice(int slice)
{
    m_iActiveSlice = slice;
}


int ImageContainer::GetActiveSlice()
{
    return m_iActiveSlice;
}


void ImageContainer::SetMinSliceNum(int min)
{
    m_iMinSliceNum = min;
}


int ImageContainer::GetMinSliceNum()
{
    return m_iMinSliceNum;
}


void ImageContainer::SetMaxSliceNum(int max)
{
    m_iMaxSliceNum = max;
}


int ImageContainer::GetMaxSliceNum()
{
    return m_iMaxSliceNum;
}
