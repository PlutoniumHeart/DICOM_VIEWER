#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H


#include <vector>
#include <memory>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QImage>

#include "ImageContainer.h"
#include "ImageIO.h"
#include "ImageFilter.h"


class ImageHandler
{
public:
    ImageHandler();
    virtual ~ImageHandler();

    bool AddImage(QString filename);
    bool RemoveImage();

    void SetActiveIndex(unsigned int index);
    int GetActiveIndex();
    std::shared_ptr<ImageContainer> GetImageObj();
    int GetNumberOfOpenedImages();

    void UpdateImage(short wc, short ww);

    void Paint(QPainter* painter, QPaintEvent* event, int elapsed, const QRect& rect);

private:
    void DisplayImage(short wc, short ww);
    void ITKImageToQImage(UnsignedCharImageType::Pointer& itk_image, QImage** qt_image);

private:
    std::vector<std::shared_ptr<ImageContainer> > m_vecImages;
    std::shared_ptr<ImageContainer> m_pCurrentImage;
    int m_iActiveIndex;
    UnsignedCharImageType::Pointer m_ucDisplayImageObj;
    QImage *m_qtDisplayImage;
    unsigned char* m_ucPixArray;

};


#endif // IMAGEHANDLER_H
