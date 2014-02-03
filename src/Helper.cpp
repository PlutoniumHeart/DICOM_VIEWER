#include "Helper.h"


Helper::Helper()
    : m_ucPixArray(NULL)
    , m_sImageWidth(0)
    , m_sImageHeight(0)
{
    m_ucDisplayImageObj = UnsignedCharImageType::New();
    //m_sImageObj = ShortImageType::New();
    //m_DicomIO = DICOMIOType::New();
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
        ImageContainer* image = new ImageContainer;
        ImageIO::ReadDICOMImage(fileName.toUtf8().constData(),
                                *image->GetShortImagePointer(), *image->GetIOObject());

        m_sDefaultWC = image->GetDefaultWindowCenter();
        m_sDefaultWW = image->GetDefaultWindowWidth();
        m_sLowerBound = image->GetWindowLowerBound();
        m_sUpperBound = image->GetWindowUpperBound();

        ImageFilter::IntensityWindowingFilter<ShortImageType, UnsignedCharImageType,
                                              ShortImageType::Pointer, UnsignedCharImageType::Pointer>
            (*image->GetShortImagePointer(), m_ucDisplayImageObj, m_sDefaultWC, m_sDefaultWW);
        
        m_sImageWidth = image->GetImageWidth();
        m_sImageHeight = image->GetImageHeight();

        m_ucPixArray = new unsigned char[m_sImageWidth*m_sImageHeight];
        ITKImageToQImage(m_ucDisplayImageObj, &m_qtDisplayImage);

        m_ImageList.insert(std::pair<int, ImageContainer*>(1, image));
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
        (*m_ImageList[1]->GetShortImagePointer(), m_ucDisplayImageObj, wc, ww);
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
