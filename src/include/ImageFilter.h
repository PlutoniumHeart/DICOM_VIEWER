#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H


#include "ImageCommon.h"


class ImageFilter
{
public:
    ImageFilter();
    ~ImageFilter();
    
    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static bool Cast(T1Pointer& imageObj_1, T2Pointer& imageObj_2);

    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static bool RescaleIntensityFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2);
};


template<class T1, class T2, class T1Pointer, class T2Pointer>
bool ImageFilter::Cast(T1Pointer& imageObj_1, T2Pointer& imageObj_2)
{
    typedef itk::CastImageFilter<T1, T2> CastFilterType;

    typename CastFilterType::Pointer castFilter = CastFilterType::New();

    castFilter->SetInput(imageObj_1);
    try
    {
        castFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in casting image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = castFilter->GetOutput();

    return true;
}


template<class T1, class T2, class T1Pointer, class T2Pointer>
bool ImageFilter::RescaleIntensityFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2)
{
    typedef itk::RescaleIntensityImageFilter<T1, T2> RescaleFilterType;

    typename RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();

    rescaleFilter->SetInput(imageObj_1);
    try
    {
        rescaleFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in casting image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = rescaleFilter->GetOutput();
    
    return true;
}


#endif // IMAGEFILTER_H
