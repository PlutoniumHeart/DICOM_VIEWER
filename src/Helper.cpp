#include "Helper.h"


Helper::Helper()
    : m_ucPixArray(NULL)
    , m_sImageWidth(0)
    , m_sImageHeight(0)
{
    m_ucDisplayImageObj = UnsignedCharImageType::New();
    m_sImageObj = ShortImageType::New();
    m_DicomIO = DICOMIOType::New();
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


void Helper::OpenImage(QString fileName)
{
    if(!fileName.isEmpty())
    {
        ImageIO::ReadDICOMImage(fileName.toUtf8().constData(), m_sImageObj, m_DicomIO);

        std::string temp;
        m_DicomIO->GetValueFromTag("0028|1050", temp);
        m_sDefaultWC = atoi(temp.c_str());
        
        m_DicomIO->GetValueFromTag("0028|1051", temp);
        m_sDefaultWW = atoi(temp.c_str());

        m_DicomIO->GetValueFromTag("0028|0106", temp);
        m_sLowerBound = atoi(temp.c_str());

        m_DicomIO->GetValueFromTag("0028|0107", temp);
        m_sUpperBound = atoi(temp.c_str());

        ImageFilter::IntensityWindowingFilter<ShortImageType, UnsignedCharImageType,
                                              ShortImageType::Pointer, UnsignedCharImageType::Pointer>
            (m_sImageObj, m_ucDisplayImageObj, m_sDefaultWC, m_sDefaultWW);
        
        m_sImageWidth = m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(0);
        m_sImageHeight = m_sImageObj->GetLargestPossibleRegion().GetSize().GetElement(1);

        m_ucPixArray = new unsigned char[m_sImageWidth*m_sImageHeight];
        ITKImageToQImage(m_ucDisplayImageObj, &m_qtDisplayImage);
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
        (m_sImageObj, m_ucDisplayImageObj, wc, ww);
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
