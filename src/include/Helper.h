#ifndef HELPER_H
#define HELPER_H


#include <map>

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
#include "ImageContainer.h"


class Helper
{
public:
    Helper();
    ~Helper();
    
public:
    void Paint(QPainter *painter, QPaintEvent *event, int elapsed, const QRect& rect);
    void OpenImage(QString fileName);
    short GetImageWidth();
    short GetImageHeight();
    short GetDefaultImageWC();
    short GetDefaultImageWW();
    short GetUpperBound();
    short GetLowerBound();
    void UpdateImage(int wc, int ww);

private:
    void ITKImageToQImage(UnsignedCharImageType::Pointer& itk_image, QImage** qt_image);
    
    QImage *m_qtDisplayImage;

    UnsignedCharImageType::Pointer m_ucDisplayImageObj;
    //ShortImageType::Pointer m_sImageObj;
    //DICOMIOType::Pointer m_DicomIO;
    unsigned char *m_ucPixArray;
    short m_sImageWidth;
    short m_sImageHeight;
    short m_sDefaultWC;
    short m_sDefaultWW;
    short m_sUpperBound;
    short m_sLowerBound;
    std::map<int, ImageContainer*> m_ImageList;
};


#endif
