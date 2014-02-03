#include "ImageContainer.h"


ImageContainer::ImageContainer()
{
    m_sImageObj = ShortImageType::New();
    m_DicomIO = DICOMIOType::New();
}


ImageContainer::~ImageContainer()
{
}


ShortImageType::Pointer* ImageContainer::GetShortImagePointer()
{
    return &m_sImageObj;
}


DICOMIOType::Pointer* ImageContainer::GetIOObject()
{
    return &m_DicomIO;
}


short ImageContainer::GetImageWidth()
{
    return m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(0);
}


short ImageContainer::GetImageHeight()
{
    return m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(1);
}


short ImageContainer::GetDefaultWindowCenter()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0028|1050", temp);
    return atoi(temp.c_str());
}


short ImageContainer::GetDefaultWindowWidth()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0028|1051", temp);
    return atoi(temp.c_str());
}


short ImageContainer::GetWindowLowerBound()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0028|0106", temp);
    return atoi(temp.c_str());
}


short ImageContainer::GetWindowUpperBound()
{
    std::string temp;
    m_DicomIO->GetValueFromTag("0028|0107", temp);
    return atoi(temp.c_str());
}
