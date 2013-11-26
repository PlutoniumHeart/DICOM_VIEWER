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

    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static bool BinaryThresholdFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2,
                                      int lowerThreshold, int upperThreshold,
                                      int foreground, int background);

    template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
    static bool BinaryDilationFilter2D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                     int foreground, int background);

    template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
    static bool BinaryDilationFilter3D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                     int foreground, int background);

    template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
    static bool BinaryErosionFilter2D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                     int foreground, int background);

    template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
    static bool BinaryErosionFilter3D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                     int foreground, int background);
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


template<class T1, class T2, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryThresholdFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2,
                                        int lowerThreshold, int upperThreshold,
                                        int foreground, int background)
{
    typedef itk::BinaryThresholdImageFilter<T1, T2> BinaryThresholdType;

    typename BinaryThresholdType::Pointer thresholdFilter = BinaryThresholdType::New();

    thresholdFilter->SetInput(imageObj_1);
    thresholdFilter->SetOutsideValue(background);
    thresholdFilter->SetInsideValue(foreground);
    thresholdFilter->SetLowerThreshold(lowerThreshold);
    thresholdFilter->SetUpperThreshold(upperThreshold);

    try
    {
        thresholdFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in thresholding image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = thresholdFilter->GetOutput();
    return true;
}


template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryDilationFilter2D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                       int foreground, int background)
{
    typedef itk::BinaryBallStructuringElement<T3, 2> StructuringElementType;
    typedef itk::BinaryDilateImageFilter<T1, T2, StructuringElementType> DilationType;

    typename DilationType::Pointer dilationFilter = DilationType::New();
    StructuringElementType structuringElement;

    structuringElement.SetRadius(Radius);
    structuringElement.CreateStructuringElement();

    dilationFilter->SetKernel(structuringElement);
    dilationFilter->SetInput(imageObj_1);
    dilationFilter->SetDilateValue(foreground);

    try
    {
        dilationFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in Dilating image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = dilationFilter->GetOutput();
    
    return true;
}


template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryDilationFilter3D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                       int foreground, int background)
{
    typedef itk::BinaryBallStructuringElement<T3, 3> StructuringElementType;
    typedef itk::BinaryDilateImageFilter<T1, T2, StructuringElementType> DilationType;

    typename DilationType::Pointer dilationFilter = DilationType::New();
    StructuringElementType structuringElement;

    structuringElement.SetRadius(Radius);
    structuringElement.CreateStructuringElement();

    dilationFilter->SetKernel(structuringElement);
    dilationFilter->SetInput(imageObj_1);
    dilationFilter->SetDilateValue(foreground);

    try
    {
        dilationFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in Dilating image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = dilationFilter->GetOutput();
    
    return true;
}


template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryErosionFilter2D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                       int foreground, int background)
{
    typedef itk::BinaryBallStructuringElement<T3, 2> StructuringElementType;
    typedef itk::BinaryErodeImageFilter<T1, T2, StructuringElementType> ErosionType;

    typename ErosionType::Pointer erosionFilter = ErosionType::New();
    StructuringElementType structuringElement;

    structuringElement.SetRadius(Radius);
    structuringElement.CreateStructuringElement();

    erosionFilter->SetKernel(structuringElement);
    erosionFilter->SetInput(imageObj_1);
    erosionFilter->SetErodeValue(foreground);

    try
    {
        erosionFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in eroding image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = erosionFilter->GetOutput();
    
    return true;
}


template<class T1, class T2, class T3, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryErosionFilter3D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int Radius,
                                       int foreground, int background)
{
    typedef itk::BinaryBallStructuringElement<T3, 3> StructuringElementType;
    typedef itk::BinaryErodeImageFilter<T1, T2, StructuringElementType> ErosionType;

    typename ErosionType::Pointer erosionFilter = ErosionType::New();
    StructuringElementType structuringElement;

    structuringElement.SetRadius(Radius);
    structuringElement.CreateStructuringElement();

    erosionFilter->SetKernel(structuringElement);
    erosionFilter->SetInput(imageObj_1);
    erosionFilter->SetErodeValue(foreground);

    try
    {
        erosionFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in eroding image: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = erosionFilter->GetOutput();
    
    return true;
}


#endif // IMAGEFILTER_H
