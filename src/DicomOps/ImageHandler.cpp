#include "ImageHandler.h"


ImageHandler::ImageHandler()
    : m_pCurrentImage(NULL)
    , m_ucPixArray(NULL)
    , m_iActiveIndex(-1)
{
    m_qtDisplayImage = new QImage();
    m_ucDisplayImageObj = UnsignedCharImageType::New();
}


ImageHandler::~ImageHandler()
{
    if(m_qtDisplayImage != NULL)
    {
        delete m_qtDisplayImage;
        m_qtDisplayImage = NULL;
    }

    if(m_ucPixArray != NULL)
    {
        delete [] m_ucPixArray;
        m_ucPixArray = NULL;
    }
}


bool ImageHandler::AddImage(QString filename)
{
    if(filename.isEmpty())
        return false;

    std::shared_ptr<ImageContainer> image(std::make_shared<ImageContainer>());

    ImageIO::ReadDICOMImage(filename.toStdString(), *image->GetImage(), *image->GetIOObject());
    image->SetDimension(2);
    image->SetCurrentWC(image->GetDefaultWC());
    image->SetCurrentWW(image->GetDefaultWW());

    m_vecImages.push_back(image);
    m_pCurrentImage = image;
    m_iActiveIndex = m_vecImages.size()-1;

    DisplayImage(image->GetDefaultWC(), image->GetDefaultWW());

    std::cout<<"Contain "<<m_vecImages.size()<<" images."<<std::endl;
    std::cout<<"Active image: "<<m_iActiveIndex<<std::endl;

    return true;
}


bool ImageHandler::RemoveImage()
{
    if(m_iActiveIndex < 0 || m_iActiveIndex >= m_vecImages.size())
    {
        std::cout<<"No more images to remove."<<std::endl;
        return false;
    }

    std::shared_ptr<ImageContainer> temp = m_vecImages[m_iActiveIndex];
    m_vecImages.erase(m_vecImages.begin()+m_iActiveIndex);
    if(temp != NULL)
        temp.reset();

    if(m_vecImages.size() != 0)
    {
        m_iActiveIndex = m_vecImages.size()-1;
        UpdateImage(m_vecImages[m_iActiveIndex]->GetCurrentWC(), m_vecImages[m_iActiveIndex]->GetCurrentWW());
    }
    else
    {
        m_iActiveIndex = -1;
        if(m_qtDisplayImage != NULL)
        {
            delete m_qtDisplayImage;
            m_qtDisplayImage = NULL;
        }
        m_qtDisplayImage = new QImage(1, 1, QImage::Format_RGB32);

        for(int i=0;i<1;i++)
        {
            for(int j=0;j<1;j++)
            {
                //short temp = m_ucPixArray[j+i*1];
                m_qtDisplayImage->setPixel(j, i, qRgb(0, 0, 0));
            }
        }
    }

    std::cout<<"Contain "<<m_vecImages.size()<<" images."<<std::endl;
    std::cout<<"Active image: "<<m_iActiveIndex<<std::endl;

    return true;
}


void ImageHandler::DisplayImage(short wc, short ww)
{
    std::shared_ptr<ImageContainer> currentImage = m_vecImages[m_iActiveIndex];

    if(m_ucPixArray != NULL)
    {
        delete [] m_ucPixArray;
        m_ucPixArray = NULL;
    }

    m_ucPixArray = new unsigned char[currentImage->GetWidth()*currentImage->GetHeight()];

    ImageFilter::IntensityWindowingFilter
            <ShortImageType, UnsignedCharImageType,
             ShortImageType::Pointer, UnsignedCharImageType::Pointer>
            (*currentImage->GetImage(), m_ucDisplayImageObj, wc, ww);

    ITKImageToQImage(m_ucDisplayImageObj, &m_qtDisplayImage);
}


void ImageHandler::UpdateImage(short wc, short ww)
{
    m_vecImages[m_iActiveIndex]->SetCurrentWC(wc);
    m_vecImages[m_iActiveIndex]->SetCurrentWW(ww);

    ImageFilter::IntensityWindowingFilter<ShortImageType, UnsignedCharImageType,
                                          ShortImageType::Pointer, UnsignedCharImageType::Pointer>
        (*(m_vecImages[m_iActiveIndex]->GetImage()), m_ucDisplayImageObj, wc, ww);
    ITKImageToQImage(m_ucDisplayImageObj, &m_qtDisplayImage);
}


void ImageHandler::ITKImageToQImage(UnsignedCharImageType::Pointer& itk_image, QImage **qt_image)
{
    int i = 0, j = 0;
    ImageIO::PixelToArray(itk_image, &m_ucPixArray);
    **qt_image = QImage(m_vecImages[m_iActiveIndex]->GetWidth(), m_vecImages[m_iActiveIndex]->GetHeight(), QImage::Format_RGB32);

    for(i=0;i<m_vecImages[m_iActiveIndex]->GetHeight();i++)
    {
        for(j=0;j<m_vecImages[m_iActiveIndex]->GetWidth();j++)
        {
            short temp = m_ucPixArray[j+i*m_vecImages[m_iActiveIndex]->GetWidth()];
            (*qt_image)->setPixel(j, i, qRgb(temp, temp, temp));
        }
    }
}


void ImageHandler::SetActiveIndex(unsigned int index)
{
    m_iActiveIndex = index;
}


int ImageHandler::GetActiveIndex()
{
    return m_iActiveIndex;
}


std::shared_ptr<ImageContainer> ImageHandler::GetImageObj()
{
    return m_vecImages[m_iActiveIndex];
}


int ImageHandler::GetNumberOfOpenedImages()
{
    return m_vecImages.size();
}


void ImageHandler::Paint(QPainter *painter, QPaintEvent *event, int elapsed, const QRect& rect)
{
    QRect rect1 = QRect(0, 0, rect.width(), rect.height());
    painter->drawImage(rect1, *m_qtDisplayImage);
}
