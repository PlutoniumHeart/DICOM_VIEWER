#ifndef IMAGEOPS_H
#define IMAGEOPS_H


#include <QImage>

#include "ImageIO.h"
#include "ImageData.h"


class ImageOps
{
public:
    ImageOps();
    ~ImageOps();

    static std::shared_ptr<ImageData> OpenSlice(QString filename);
    static std::shared_ptr<ImageData> OpenSeries(QString folder);

};


#endif // IMAGEOPS_H
