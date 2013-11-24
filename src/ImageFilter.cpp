#include "ImageFilter.h"


ImageFilter::ImageFilter()
{
}


ImageFilter::~ImageFilter()
{
}


bool ImageFilter::CastUnsignedCharToShortImage(UnsignedCharImageType::Pointer& imageObj_1,
                                             ShortImageType::Pointer& imageObj_2)
{
    CastUnsignedCharToShortImageType::Pointer castFilter = CastUnsignedCharToShortImageType::New();
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


bool ImageFilter::CastShortToUnsignedCharImage(ShortImageType::Pointer& imageObj_1,
                                           UnsignedCharImageType::Pointer& imageObj_2)
{
    CastShortToUnsignedCharImageType::Pointer castFilter = CastShortToUnsignedCharImageType::New();
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
