#include "Helper.h"


Helper::Helper()
    : m_ucPixArray(NULL)
    , m_sImageWidth(0)
    , m_sImageHeight(0)
{
    m_ucDisplayImageObj = UnsignedCharImageType::New();
    m_qtDisplayImage = new QImage();
}


Helper::~Helper()
{
    if(m_ucPixArray!=NULL)
    {
        delete [] m_ucPixArray;
        m_ucPixArray = NULL;
    }
}


void Helper::Paint(QPainter *painter, QPaintEvent *event, int elapsed, const QRect& rect)
{
    QRect rect1 = QRect(0, 0, rect.width(), rect.height());
    painter->drawImage(rect1, *m_qtDisplayImage);
}


bool Helper::OpenImage(QString fileName)
{
    if(!fileName.isEmpty())
    {
        ImageContainer* image = new ImageContainer;
        ImageIO::ReadDICOMImage(fileName.toUtf8().constData(),
                                *image->GetShortImagePointer(), *image->GetIOObject());

        m_sDefaultWC = image->GetDefaultWindowCenter();
        m_sDefaultWW = image->GetDefaultWindowWidth();
        m_sLowerBound = image->GetWindowLowerBound();
        m_sUpperBound = image->GetWindowUpperBound();

        ImageFilter::IntensityWindowingFilter
            <ShortImageType, UnsignedCharImageType,
             ShortImageType::Pointer, UnsignedCharImageType::Pointer>
            (*image->GetShortImagePointer(), m_ucDisplayImageObj, m_sDefaultWC, m_sDefaultWW);
        
        m_sImageWidth = image->GetImageWidth();
        m_sImageHeight = image->GetImageHeight();

        m_ucPixArray = new unsigned char[m_sImageWidth*m_sImageHeight];
        ITKImageToQImage(m_ucDisplayImageObj, &m_qtDisplayImage);

        m_iCurrentImageID = m_ImageList.size()+1;
        m_strStudyInstanceUID = image->GetStudyInstanceUID();
        m_ImageList.insert(std::pair<std::string, ImageContainer*>(m_strStudyInstanceUID, image));
        return true;
    }
    else
    {
        return false;
    }
}


void Helper::CloseSeries(int nextIndex, std::string nextUID)
{
    if(nextUID == "")
    {
        ImageContainer* temp = m_ImageList[m_strStudyInstanceUID];
        m_ImageList.erase(m_strStudyInstanceUID);
        delete temp;
        m_qtDisplayImage = new QImage(1, 1, QImage::Format_RGB32);

        for(int i=0;i<1;i++)
        {
            for(int j=0;j<1;j++)
            {
                short temp = m_ucPixArray[j+i*1];
                m_qtDisplayImage->setPixel(j, i, qRgb(0, 0, 0));
            }
        }

        m_strStudyInstanceUID = "";
        m_iCurrentImageID = 0;
    }
    else
    {
        ImageContainer* temp = m_ImageList[m_strStudyInstanceUID];
        m_ImageList.erase(m_strStudyInstanceUID);
        delete temp;
        m_strStudyInstanceUID = nextUID;
        m_iCurrentImageID = nextIndex;
        SetCurrentImageID(nextIndex, m_strStudyInstanceUID);
    }
}


void Helper::ITKImageToQImage(UnsignedCharImageType::Pointer& itk_image, QImage** qt_image)
{
    int i = 0, j = 0;
    ImageIO::PixelToArray(itk_image, &m_ucPixArray);
    **qt_image = QImage(m_sImageWidth, m_sImageHeight, QImage::Format_RGB32);

    for(i=0;i<m_sImageHeight;i++)
    {
        for(j=0;j<m_sImageWidth;j++)
        {
            short temp = m_ucPixArray[j+i*m_sImageWidth];
            (*qt_image)->setPixel(j, i, qRgb(temp, temp, temp));
        }
    }
}


void Helper::UpdateImage(int wc, int ww)
{
    ImageFilter::IntensityWindowingFilter<ShortImageType, UnsignedCharImageType,
                                          ShortImageType::Pointer, UnsignedCharImageType::Pointer>
        (*m_ImageList[m_strStudyInstanceUID]->GetShortImagePointer(), m_ucDisplayImageObj, wc, ww);
    ITKImageToQImage(m_ucDisplayImageObj, &m_qtDisplayImage);
}


short Helper::GetImageWidth()
{
    return m_sImageWidth;
}


short Helper::GetImageHeight()
{
    return m_sImageHeight;
}


short Helper::GetDefaultImageWC()
{
    return m_sDefaultWC;
}


short Helper::GetDefaultImageWW()
{
    return m_sDefaultWW;
}


short Helper::GetUpperBound()
{
    return m_sUpperBound;
}


short Helper::GetLowerBound()
{
    return m_sLowerBound;
}


int Helper::GetOpenedImageNumber()
{
    return m_ImageList.size();
}


ImageContainer* Helper::GetContainer(std::string uid)
{
    return m_ImageList[uid];
}


ImageContainer* Helper::GetCurrentContainer()
{
    return m_ImageList[m_strStudyInstanceUID];
}


void Helper::SetCurrentImageID(int i, std::string uid)
{
    m_strStudyInstanceUID = uid;
    m_iCurrentImageID = i;
    
    m_sDefaultWC = m_ImageList[uid]->GetDefaultWindowCenter();
    m_sDefaultWW = m_ImageList[uid]->GetDefaultWindowWidth();
    m_sLowerBound = m_ImageList[uid]->GetWindowLowerBound();
    m_sUpperBound = m_ImageList[uid]->GetWindowUpperBound();
    
    m_sImageWidth = m_ImageList[uid]->GetImageWidth();
    m_sImageHeight = m_ImageList[uid]->GetImageHeight();
    delete [] m_ucPixArray;
    m_ucPixArray = NULL;
    m_ucPixArray = new unsigned char[m_sImageWidth*m_sImageHeight];
}


int Helper::GetCurrentImageID()
{
    return m_iCurrentImageID;
}
