#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QImage>

#include "ImageIO.h"
#include "ImageFilter.h"


class Helper
{
public:
    Helper();
    ~Helper();
    
public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed, const QRect& rect);
    void openImage(QString fileName);
    short GetImageWidth();
    short GetImageHeight();
    short GetDefaultImageWC();
    short GetDefaultImageWW();
    short GetUpperBound();
    short GetLowerBound();
    void updateImage(int wc, int ww);

private:
    void ITKImageToQImage(UnsignedCharImageType::Pointer& itk_image, QImage** qt_image);
    
    QImage *m_qtDisplayImage;

    UnsignedCharImageType::Pointer m_ucDisplayImageObj;
    ShortImageType::Pointer m_sImageObj;
    DICOMIOType::Pointer m_dicomIO;
    unsigned char *m_ucPixArray;
    short m_sImageWidth;
    short m_sImageHeight;
    short m_sDefaultWC;
    short m_sDefaultWW;
    short m_sUpperBound;
    short m_sLowerBound;
};


#endif
