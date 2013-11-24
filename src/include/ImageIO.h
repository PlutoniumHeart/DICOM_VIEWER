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
#include <itkImageSeriesReader.h>
#include <itkImageSeriesWriter.h>
#include <itkNumericSeriesFileNames.h>
#include <itkGDCMSeriesFileNames.h>


const unsigned char D2 = 2;
const unsigned char D3 = 3;

typedef itk::Image<unsigned char, D2>                                          UnsignedCharImageType;
typedef itk::Image<unsigned char, D3>                                          UnsignedCharSeriesType;
typedef itk::Image<short, D2>                                                  ShortImageType;
typedef itk::Image<short, D3>                                                  ShortSeriesType;
typedef itk::ImageRegion<D2>                                                   UnsignedCharImageRegion2D;
typedef itk::PNGImageIO                                                        PNGIOType;
typedef itk::JPEGImageIO                                                       JPEGIOType;
typedef itk::GDCMImageIO                                                       DICOMIOType;
typedef itk::ImageFileReader<UnsignedCharImageType>                            UnsignedCharImageReadType;
typedef itk::ImageSeriesReader<UnsignedCharSeriesType>                         UnsignedCharSeriesReadType;
typedef itk::ImageFileReader<ShortImageType>                                   ShortImageReadType;
typedef itk::ImageSeriesReader<ShortSeriesType>                                ShortSeriesReadType;
typedef itk::ImageFileWriter<UnsignedCharImageType>                            UnsignedCharImageWriteType;
typedef itk::ImageSeriesWriter<UnsignedCharSeriesType,
                               UnsignedCharImageType>                          UnsignedCharSeriesWriteType;
typedef itk::ImageSeriesWriter<ShortSeriesType, ShortImageType>                ShortSeriesWriteType;
typedef itk::ImageFileWriter<ShortImageType>                                   ShortImageWriteType;
typedef itk::ImageRegionConstIterator<UnsignedCharImageType>                   UnsignedCharConstIteratorType;
typedef itk::ImageRegionConstIterator<ShortImageType>                          ShortImageConstIteratorType;
typedef itk::ImageRegionIterator<UnsignedCharImageType>                        UnsignedCharIteratorType;
typedef itk::GDCMSeriesFileNames                                               DICOMSeriesNameGeneratorType;
typedef itk::NumericSeriesFileNames                                            SeriesNameGeneratorType;


class ImageIO
{
public:
    ImageIO();
    ~ImageIO();

    static bool ReadPNGImage(std::string inputFile, UnsignedCharImageType::Pointer& imageObj);
    static bool WritePNGImage(std::string outputFile, UnsignedCharImageType::Pointer& imageObj);

    static bool ReadPNGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                              std::string seriesFormat, int begin, int end);
    static bool WritePNGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                               std::string seriesFormat, int begin, int end);

    static bool ReadJPEGImage(std::string inputFile, UnsignedCharImageType::Pointer& imageObj);
    static bool WriteJPEGImage(std::string outputFile, UnsignedCharImageType::Pointer& imageObj);

    static bool ReadJPEGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                              std::string seriesFormat, int begin, int end);
    static bool WriteJPEGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                              std::string seriesFormat, int begin, int end);

    static bool ReadDICOMImage(std::string inputFile, ShortImageType::Pointer& imageObj);
    static bool WriteDICOMImage(std::string inputFile, ShortImageType::Pointer& imageObj);

    static void SetDICOMFolder(std::string folderName, std::string** pSeriesName);
    static bool ReadDICOMSeries(std::string folderName, std::string seriesName,
                                ShortSeriesType::Pointer& imageObj);
    static bool WriteDICOMSeries(std::string folderNmae, ShortSeriesType::Pointer& imageObj,
                                 std::string seriesFormat, int begin, int end);
private:
    static PNGIOType::Pointer m_pPNGIO;
    static JPEGIOType::Pointer m_pJPEGIO;
    static DICOMIOType::Pointer m_pDICOMIO;
};


#endif // IMAGEIO_H
