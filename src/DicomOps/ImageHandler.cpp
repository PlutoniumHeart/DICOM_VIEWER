#include "ImageHandler.h"


ImageHandler::ImageHandler()
    : m_pCurrentImage(NULL)
    , m_iActiveIndex(-1)
{
}


ImageHandler::~ImageHandler()
{
}


bool ImageHandler::AddImage(QString filename)
{
    if(filename.isEmpty())
        return false;

    std::shared_ptr<ImageContainer> image = std::make_shared<ImageContainer>();
    image->Allocate(1);

    ImageIO::ReadDICOMImage(filename.toStdString(), *image->GetImage(0), *image->GetIOObject(0));
    image->SetDimension(2);
    image->SetCurrentWC(image->GetDefaultWC(image->GetActiveSlice()));
    image->SetCurrentWW(image->GetDefaultWW(image->GetActiveSlice()));
    image->SetCurrentSizeFactor(1);

    m_vecImages.push_back(image);
    m_pCurrentImage = image;
    m_iActiveIndex = m_vecImages.size()-1;
    image->SetActiveSlice(0);
    image->SetMinSliceNum(0);
    image->SetMaxSliceNum(0);

//    DisplayImage(image->GetDefaultWC(image->GetActiveSlice()), image->GetDefaultWW(image->GetActiveSlice()));

    return true;
}


bool ImageHandler::AddImageSeries(QString folderPath)
{
    if(folderPath.isEmpty())
        return false;

    std::shared_ptr<ImageContainer> imageSeries = std::make_shared<ImageContainer>();

    std::vector<std::string> filenames;

    int fileNum = ImageIO::ProbeDICOMFolder(folderPath.toStdString(), filenames);
    imageSeries->Allocate(fileNum);

    for(int i=0;i<fileNum;i++)
    {
        ImageIO::ReadDICOMImage(filenames[i], *imageSeries->GetImage(i), *imageSeries->GetIOObject(i));
    }

    m_vecImages.push_back(imageSeries);
    m_pCurrentImage = imageSeries;
    m_iActiveIndex = m_vecImages.size() - 1;
    imageSeries->SetActiveSlice(0);
    imageSeries->SetMinSliceNum(0);
    imageSeries->SetMaxSliceNum(fileNum-1);

    imageSeries->SetDimension(3);
    imageSeries->SetCurrentWC(imageSeries->GetDefaultWC(imageSeries->GetActiveSlice()));
    imageSeries->SetCurrentWW(imageSeries->GetDefaultWW(imageSeries->GetActiveSlice()));
    imageSeries->SetCurrentSizeFactor(1);

//    DisplayImage(imageSeries->GetDefaultWC(imageSeries->GetActiveSlice()),
//                 imageSeries->GetDefaultWW(imageSeries->GetActiveSlice()));

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
    if(temp != NULL)
        temp.reset();
    m_vecImages.erase(m_vecImages.begin()+m_iActiveIndex);

    if(m_vecImages.size() != 0)
    {
        m_iActiveIndex = m_vecImages.size()-1;
//        UpdateImage(m_vecImages[m_iActiveIndex]->GetCurrentWC(), m_vecImages[m_iActiveIndex]->GetCurrentWW());
    }
    else
    {
        m_vecImages.clear();
        m_iActiveIndex = -1;
    }

    return true;
}


void ImageHandler::DisplayImage(short wc, short ww, int slice, QImage* image)
{
    std::shared_ptr<ImageContainer> currentImage = m_vecImages[m_iActiveIndex];

    ITKImageToQImage(*currentImage->GetImage(slice), image);
}


void ImageHandler::UpdateImage(short wc, short ww, int slice, QImage* image)
{
    m_vecImages[m_iActiveIndex]->SetCurrentWC(wc);
    m_vecImages[m_iActiveIndex]->SetCurrentWW(ww);

    DisplayImage(wc, ww, slice, image);
}


void ImageHandler::ITKImageToQImage(ShortImageType::Pointer& itk_image, QImage* qt_image)
{
    int i = 0, j = 0;
    std::shared_ptr<ImageContainer> ActiveImage = m_vecImages[m_iActiveIndex];
    int width = ActiveImage->GetWidth(ActiveImage->GetActiveSlice());
    int height = ActiveImage->GetHeight(ActiveImage->GetActiveSlice());
    ShortImageConstIteratorType itkImage(itk_image, itk_image->GetLargestPossibleRegion());
    itkImage.GoToBegin();
    int wc = ActiveImage->GetCurrentWC();
    int ww = ActiveImage->GetCurrentWW();

    *qt_image = QImage(width, height, QImage::Format_RGB32);

    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            int temp = itkImage.Get();

            if(temp<wc-0.5-(ww-1)/2)
                temp = 0;
            else if(temp>wc-0.5+(ww-1)/2)
                temp = 255;
            else
                temp = ((temp-(wc-0.5))/(ww-1)+0.5)*255;

            qt_image->setPixel(j, i, qRgb(temp, temp, temp));
            ++itkImage;
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


void ImageHandler::Paint(QPainter *painter, QPaintEvent *event, int elapsed, QImage* image, const QRect& rect)
{
    QRect rect1 = QRect(0, 0, rect.width(), rect.height());
    painter->drawImage(rect1, *image);
}
