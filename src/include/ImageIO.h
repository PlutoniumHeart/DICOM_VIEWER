#ifndef IMAGEIO_H
#define IMAGEIO_H


#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkImageRegionConstIterator.h>
#include <itkPNGImageIO.h>
#include <itkJPEGImageIO.h>
#include <itkGDCMImageIO.h>
#include <itkMetaDataDictionary.h>
#include <itkMetaDataObject.h>


const unsigned char D2 = 2;

typedef itk::Image<unsigned char, D2>                                          UnsignedCharImageType;
typedef itk::Image<short, D2>                                                  ShortImageType;
typedef itk::ImageRegion<D2>                                                   UnsignedCharImageRegion2D;
typedef itk::PNGImageIO                                                        PNGIOType;
typedef itk::JPEGImageIO                                                       JPEGIOType;
typedef itk::GDCMImageIO                                                       DICOMIOType;
typedef itk::ImageFileReader<UnsignedCharImageType>                            UnsignedCharImageReadType;
typedef itk::ImageFileReader<ShortImageType>                                   ShortImageReadType;
typedef itk::ImageFileWriter<UnsignedCharImageType>                            UnsignedCharImageWriteType;
typedef itk::ImageFileWriter<ShortImageType>                                   ShortImageWriteType;
typedef itk::ImageRegionConstIterator<UnsignedCharImageType>                   UnsignedCharConstIteratorType;
typedef itk::ImageRegionConstIterator<ShortImageType>                          ShortImageConstIteratorType;
typedef itk::ImageRegionIterator<UnsignedCharImageType>                        UnsignedCharIteratorType;


class ImageIO
{
public:
    ImageIO();
    ~ImageIO();

    static bool ReadPNGImage(std::string inputFile, UnsignedCharImageType::Pointer& imageObj);
    static bool WritePNGImage(std::string outputFile, UnsignedCharImageType::Pointer& imageObj);

    static bool ReadJPEGImage(std::string inputFile, UnsignedCharImageType::Pointer& imageObj);
    static bool WriteJPEGImage(std::string outputFile, UnsignedCharImageType::Pointer& imageObj);

    static bool ReadDICOMImage(std::string inputFile, ShortImageType::Pointer& imageObj);
    static bool WriteDICOMImage(std::string inputFile, ShortImageType::Pointer& imageObj);
private:
    static PNGIOType::Pointer m_pPNGIO;
    static JPEGIOType::Pointer m_pJPEGIO;
    static DICOMIOType::Pointer m_pDICOMIO;
};


#endif // IMAGEIO_H
