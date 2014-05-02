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
    bool OpenImage(QString fileName);
    void CloseSeries(int nextIndex, std::string nextUID);
    short GetImageWidth();
    short GetImageHeight();
    short GetDefaultImageWC();
    short GetDefaultImageWW();
    short GetUpperBound();
    short GetLowerBound();
    int GetOpenedImageNumber();
    ImageContainer* GetContainer(std::string uid);
    ImageContainer* GetCurrentContainer();
    void UpdateImage(int wc, int ww);
    void SetCurrentImageID(int i, std::string uid);
    int GetCurrentImageID();

private:
    void ITKImageToQImage(UnsignedCharImageType::Pointer& itk_image, QImage** qt_image);

private:
    QImage *m_qtDisplayImage;

    UnsignedCharImageType::Pointer m_ucDisplayImageObj;
    unsigned char *m_ucPixArray;
    short m_sImageWidth;
    short m_sImageHeight;
    short m_sDefaultWC;
    short m_sDefaultWW;
    short m_sUpperBound;
    short m_sLowerBound;
    std::map<std::string, ImageContainer*> m_ImageList;
    int m_iCurrentImageID;
    std::string m_strStudyInstanceUID;
};


#endif
