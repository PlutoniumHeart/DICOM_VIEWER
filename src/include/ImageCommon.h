#ifndef IMAGECOMMON_H
#define IMAGECOMMON_H


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
#include <itkCastImageFilter.h>


const unsigned char D2 = 2;
const unsigned char D3 = 3;

typedef itk::Image<unsigned char, D2>                                        UnsignedCharImageType;
typedef itk::Image<unsigned char, D3>                                        UnsignedCharSeriesType;
typedef itk::Image<short, D2>                                                ShortImageType;
typedef itk::Image<short, D3>                                                ShortSeriesType;
typedef itk::ImageRegion<D2>                                                 UnsignedCharImageRegion2D;
typedef itk::PNGImageIO                                                      PNGIOType;
typedef itk::JPEGImageIO                                                     JPEGIOType;
typedef itk::GDCMImageIO                                                     DICOMIOType;
typedef itk::ImageFileReader<UnsignedCharImageType>                          UnsignedCharImageReadType;
typedef itk::ImageSeriesReader<UnsignedCharSeriesType>                       UnsignedCharSeriesReadType;
typedef itk::ImageFileReader<ShortImageType>                                 ShortImageReadType;
typedef itk::ImageSeriesReader<ShortSeriesType>                              ShortSeriesReadType;
typedef itk::ImageFileWriter<UnsignedCharImageType>                          UnsignedCharImageWriteType;
typedef itk::ImageSeriesWriter<UnsignedCharSeriesType,
                               UnsignedCharImageType>                        UnsignedCharSeriesWriteType;
typedef itk::ImageSeriesWriter<ShortSeriesType, ShortImageType>              ShortSeriesWriteType;
typedef itk::ImageFileWriter<ShortImageType>                                 ShortImageWriteType;
typedef itk::ImageRegionConstIterator<UnsignedCharImageType>                 UnsignedCharConstIteratorType;
typedef itk::ImageRegionConstIterator<ShortImageType>                        ShortImageConstIteratorType;
typedef itk::ImageRegionIterator<UnsignedCharImageType>                      UnsignedCharIteratorType;
typedef itk::GDCMSeriesFileNames                                             DICOMSeriesNameGeneratorType;
typedef itk::NumericSeriesFileNames                                          SeriesNameGeneratorType;
typedef itk::CastImageFilter<UnsignedCharImageType, ShortImageType>          CastUnsignedCharToShortImageType;
typedef itk::CastImageFilter<ShortImageType, UnsignedCharImageType>          CastShortToUnsignedCharImageType;
typedef itk::CastImageFilter<UnsignedCharSeriesType, ShortSeriesType>        CastUnsignedCharToShortSeriesType;
typedef itk::CastImageFilter<ShortSeriesType, UnsignedCharSeriesType>        CastShortToUnsignedCharSeriesType;


#endif // IMAGECOMMON_H
