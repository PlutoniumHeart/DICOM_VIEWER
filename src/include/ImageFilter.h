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

    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static bool BinaryConnectedComponentFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2);

    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static bool BinaryConnectedComponentRelabelFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2);

    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static void SelectComponent(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int component);

    template<class T1, class T1Pointer, class T2, class T2Pointer>
    static bool Difference(T1Pointer& lhs, T1Pointer& rhs, T1Pointer& difference);

    template<class T1, class T2, class T1Pointer, class T2Pointer>
    static bool IntensityWindowingFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int WC, int WW);

    template<class T1, class T2, class T1Pointer, class T2Pointer, class T3>
    static bool ResampleFilter2D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int outSizeX, int outSizeY);
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


template<class T1, class T2, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryConnectedComponentFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2)
{
    typedef itk::ConnectedComponentImageFilter<T1, T2> ConnectedComponentType;

    typename ConnectedComponentType::Pointer connectedFilter = ConnectedComponentType::New();

    connectedFilter->SetInput(imageObj_1);

    try
    {
        connectedFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in analyzing connected components: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = connectedFilter->GetOutput();
    return true;
}


template<class T1, class T2, class T1Pointer, class T2Pointer>
bool ImageFilter::BinaryConnectedComponentRelabelFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2)
{
    typedef itk::RelabelComponentImageFilter<T1, T2> RelabelComponentType;

    typename RelabelComponentType::Pointer relabelFilter = RelabelComponentType::New();

    relabelFilter->SetInput(imageObj_1);

    try
    {
        relabelFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in relabeling connected components: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = relabelFilter->GetOutput();
    return true;
}


template<class T1, class T2, class T1Pointer, class T2Pointer>
void ImageFilter::SelectComponent(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int component)
{
    typedef itk::ImageRegionConstIterator<T1> ConstIteratorType;
    typedef itk::ImageRegionIterator<T2> IteratorType;
    ConstIteratorType in(imageObj_1, imageObj_1->GetLargestPossibleRegion());
    IteratorType out(imageObj_2, imageObj_2->GetLargestPossibleRegion());
    in.GoToBegin();
    out.GoToBegin();
    while(!in.IsAtEnd())
    {
        if(in.Get()<=component && in.Get()!=0)
            out.Set(255);
        else
            out.Set(0);
        ++in;
        ++out;
    }
}


template<class T1, class T1Pointer, class T2, class T2Pointer>
bool ImageFilter::Difference(T1Pointer& lhs, T1Pointer& rhs, T1Pointer& difference)
{
    /*typedef itk::SubtractImageFilter<T1, T1, T2> DifferenceFilterType;
    T2Pointer temp = T2::New();
    typename DifferenceFilterType::Pointer diffFilter = DifferenceFilterType::New();

    diffFilter->SetInput1(lhs);
    diffFilter->SetInput2(rhs);

    try
    {
        diffFilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in subtracting images: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    temp = diffFilter->GetOutput();
    return true;
    */
    typedef itk::ImageRegionConstIterator<T1> ConstIteratorType;
    typedef itk::ImageRegionIterator<T1> IteratorType;
    ConstIteratorType in_l(lhs, lhs->GetLargestPossibleRegion());
    ConstIteratorType in_r(rhs, rhs->GetLargestPossibleRegion());
    IteratorType out(difference, difference->GetLargestPossibleRegion());
    in_l.GoToBegin();
    in_r.GoToBegin();
    out.GoToBegin();
    while(!in_l.IsAtEnd())
    {
        if((in_l.Get()-in_r.Get())>255)
            out.Set(255);
        else if((in_l.Get()-in_r.Get())<0)
        {
            out.Set(0);
        }
        else
            out.Set((in_l.Get()-in_r.Get()));
        
        //out.Set(255);
        ++in_l;
        ++in_r;
        ++out;
    }
    
}


template<class T1, class T2, class T1Pointer, class T2Pointer>
bool ImageFilter::IntensityWindowingFilter(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int WC, int WW)
{
    typedef itk::IntensityWindowingImageFilter<T1, T2> windowingFilterType;
    typename windowingFilterType::Pointer filter = windowingFilterType::New();

    filter->SetInput(imageObj_1);
    filter->SetWindowMinimum(WC-WW/2);
    filter->SetWindowMaximum(WC+WW/2);
    filter->SetOutputMinimum(0);
    filter->SetOutputMaximum(255);

    try
    {
        filter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in windowing images: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj_2 = filter->GetOutput();
    
    return true;
}


template<class T1, class T2, class T1Pointer, class T2Pointer, class T3>
bool ImageFilter::ResampleFilter2D(T1Pointer& imageObj_1, T2Pointer& imageObj_2, int outSizeX, int outSizeY)
{
    typedef itk::IdentityTransform<double, 2> TransformType;
    typedef itk::ResampleImageFilter<T1, T2> ResampleImageFilterType;
    typename ResampleImageFilterType::Pointer resampleFilter = ResampleImageFilterType::New();
        
    typename T1::SizeType inputSize = imageObj_1->GetLargestPossibleRegion().GetSize();
    typename T2::SizeType outputSize;
    outputSize[0] = outSizeX;
    outputSize[1] = outSizeY;

    typename T2::SpacingType outputSpacing;
    outputSpacing[0] = imageObj_1->GetSpacing()[0]*(static_cast<double>(inputSize[0])/static_cast<double>(outputSize[0]));
    outputSpacing[1] = imageObj_1->GetSpacing()[1]*(static_cast<double>(inputSize[1])/static_cast<double>(outputSize[1]));
    
    resampleFilter->SetInput(imageObj_1);
    resampleFilter->SetSize(outputSize);
    resampleFilter->SetOutputSpacing(outputSpacing);
    resampleFilter->SetTransform(TransformType::New());
    resampleFilter->UpdateLargestPossibleRegion();

    imageObj_2 = resampleFilter->GetOutput();
    
    return true;
}


#endif // IMAGEFILTER_H
