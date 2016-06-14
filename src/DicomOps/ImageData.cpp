#include "ImageData.h"


ImageData::ImageData()
{
    m_DummyImage = QImage(256, 256, QImage::Format_Grayscale8);
    for (int i=0;i<256;i++)
    {
        for (int j=0;j<256;j++)
        {
            m_DummyImage.setPixel(j, i, qRgb(0, 0, 0));
        }
    }
}


ImageData::~ImageData()
{
}


QImage ImageData::ToDisplayImage(ShortImageType::Pointer slice, int wc, int ww)
{
    int width = slice->GetLargestPossibleRegion().GetSize().GetElement(0);
    int height = slice->GetLargestPossibleRegion().GetSize().GetElement(1);
    ShortImageConstIteratorType itr(slice, slice->GetLargestPossibleRegion());
    itr.GoToBegin();
    QImage image = QImage(width, height, QImage::Format_Grayscale8);

    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            int tmp = itr.Get();

            if (tmp<wc-0.5-(ww-1)/2)
                tmp = 0;
            else if (tmp>wc-0.5+(ww-1)/2)
                tmp = 255;
            else
                tmp = ((tmp-(wc-0.5))/(ww-1)+0.5)*255;

            image.setPixel(j, i, qRgb(tmp, tmp, tmp));
            ++itr;
        }
    }
    return image;
}


void ImageData::PushBackWindowInfo(DICOMIOType::Pointer io)
{
    std::string tmpStr;
    io->GetValueFromTag("0028|1050", tmpStr);
    int wc = atoi(tmpStr.c_str());
    io->GetValueFromTag("0028|1051", tmpStr);
    int ww = atoi(tmpStr.c_str());

    m_vWCs.push_back(wc);
    m_vWWs.push_back(ww);
}


void ImageData::PushBackSlice(ShortImageType::Pointer slice, DICOMIOType::Pointer io)
{
    m_vImageObj.push_back(slice);
    m_vDicomIO.push_back(io);
    PushBackWindowInfo(io);
    m_vDisplayImage.push_back(ToDisplayImage(slice, m_vWCs[m_vWCs.size()-1], m_vWWs[m_vWWs.size()-1]));
}


void ImageData::EraseSlice(int idx)
{
    std::vector<ShortImageType::Pointer>::iterator itrITK = m_vImageObj.begin()+idx;
    std::vector<DICOMIOType::Pointer>::iterator itrio = m_vDicomIO.begin()+idx;
    std::vector<QImage>::iterator itrDisplay = m_vDisplayImage.begin()+idx;
    std::vector<short>::iterator itrWC = m_vWCs.begin()+idx;
    std::vector<short>::iterator itrWW = m_vWWs.begin()+idx;

    m_vImageObj.erase(itrITK);
    m_vDicomIO.erase(itrio);
    m_vDisplayImage.erase(itrDisplay);
    m_vWCs.erase(itrWC);
    m_vWWs.erase(itrWW);
}


void ImageData::Clear()
{
    m_vImageObj.clear();
    m_vDicomIO.clear();
    m_vDisplayImage.clear();
    m_vWCs.clear();
    m_vWWs.clear();
}


std::vector<QImage>* ImageData::GetDisplayImage()
{
    return &m_vDisplayImage;
}


QImage* ImageData::GetDummyImage()
{
    return &m_DummyImage;
}


std::vector<DICOMIOType::Pointer>* ImageData::GetIO()
{
    return &m_vDicomIO;
}


void ImageData::UpdateImageWindow(int slice, int wc, int ww)
{
    SetCurrentWC(slice, wc);
    SetCurrentWW(slice, ww);
    m_vDisplayImage[slice]=ToDisplayImage(m_vImageObj[slice], wc, ww);
}


short ImageData::GetWidth(int slice)
{
    return m_vImageObj[slice]->GetLargestPossibleRegion().GetSize().GetElement(0);
}


short ImageData::GetHeight(int slice)
{
    return m_vImageObj[slice]->GetLargestPossibleRegion().GetSize().GetElement(1);
}


short ImageData::GetDepth()
{
    return m_vImageObj.size();
}


short ImageData::GetDefaultWC(int slice)
{
    std::string tmp;
    m_vDicomIO[slice]->GetValueFromTag("0028|1050", tmp);
    return atoi(tmp.c_str());
}


short ImageData::GetDefaultWW(int slice)
{
    std::string tmp;
    m_vDicomIO[slice]->GetValueFromTag("0028|1051", tmp);
    return atoi(tmp.c_str());
}


short ImageData::GetCurrentWC(int slice)
{
    return m_vWCs[slice];
}


void ImageData::SetCurrentWC(int slice, short wc)
{
    m_vWCs[slice] = wc;
}


short ImageData::GetCurrentWW(int slice)
{
    return m_vWWs[slice];
}


void ImageData::SetCurrentWW(int slice, short ww)
{
    m_vWWs[slice] = ww;
}


std::string ImageData::GetPatientName(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0010|0010", temp);
    return temp;
}


std::string ImageData::GetPatientID(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0010|0020", temp);
    return temp;
}


std::string ImageData::GetAccession(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0010|0050", temp);
    return temp;
}


std::string ImageData::GetStudyDescription(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0008|1030", temp);
    return temp;
}


std::string ImageData::GetStudyDate(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0008|0020", temp);
    return temp;
}


std::string ImageData::GetSeriesDescription(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0008|103E", temp);
    return temp;
}


std::string ImageData::GetAcqusitionDate(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0008|0022", temp);
    return temp;
}


std::string ImageData::GetAcqusitionTime(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0008|0032", temp);
    return temp;
}


std::string ImageData::GetStudyInstanceUID(int slice)
{
    std::string temp;
    m_vDicomIO[slice]->GetValueFromTag("0020|000D", temp);
    return temp;
}
