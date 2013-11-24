#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H


#include "ImageCommon.h"


class ImageFilter
{
public:
    ImageFilter();
    ~ImageFilter();
    
    static bool CastUnsignedCharToShortImage(UnsignedCharImageType::Pointer& imageObj_1,
                                             ShortImageType::Pointer& imageObj_2);
    static bool CastShortToUnsignedCharImage(ShortImageType::Pointer& imageObj_1,
                                             UnsignedCharImageType::Pointer& imageObj_2);
    static bool CastUnsignedCharToShortSeries(UnsignedCharSeriesType::Pointer& imageObj_1,
                                              ShortSeriesType::Pointer& imageObj_2);
    static bool CastShortToUnsignedCharSeries(ShortSeriesType::Pointer& imageObj_1,
                                              UnsignedCharSeriesType::Pointer& imageObj_2);
};


#endif // IMAGEFILTER_H
