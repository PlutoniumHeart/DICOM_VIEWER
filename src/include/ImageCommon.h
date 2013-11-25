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
#include <itkRescaleIntensityImageFilter.h>


const unsigned char D2 = 2;
const unsigned char D3 = 3;

typedef itk::Image<unsigned char, D2>                                       UnsignedCharImageType;
typedef itk::Image<unsigned char, D3>                                       UnsignedCharSeriesType;
typedef itk::Image<short, D2>                                               ShortImageType;
typedef itk::Image<short, D3>                                               ShortSeriesType;
typedef itk::ImageRegion<D2>                                                UnsignedCharImageRegion2D;
typedef itk::PNGImageIO                                                     PNGIOType;
typedef itk::JPEGImageIO                                                    JPEGIOType;
typedef itk::GDCMImageIO                                                    DICOMIOType;
typedef itk::ImageFileReader<UnsignedCharImageType>                         UnsignedCharImageReadType;
typedef itk::ImageSeriesReader<UnsignedCharSeriesType>                      UnsignedCharSeriesReadType;
typedef itk::ImageFileReader<ShortImageType>                                ShortImageReadType;
typedef itk::ImageSeriesReader<ShortSeriesType>                             ShortSeriesReadType;
typedef itk::ImageFileWriter<UnsignedCharImageType>                         UnsignedCharImageWriteType;
typedef itk::ImageSeriesWriter<UnsignedCharSeriesType,
                               UnsignedCharImageType>                       UnsignedCharSeriesWriteType;
typedef itk::ImageSeriesWriter<ShortSeriesType, ShortImageType>             ShortSeriesWriteType;
typedef itk::ImageFileWriter<ShortImageType>                                ShortImageWriteType;
typedef itk::ImageRegionConstIterator<UnsignedCharImageType>                UnsignedCharImageConstIteratorType;
typedef itk::ImageRegionConstIterator<UnsignedCharSeriesType>               UnsignedCharSeriesConstIteratorType;
typedef itk::ImageRegionConstIterator<ShortImageType>                       ShortImageConstIteratorType;
typedef itk::ImageRegionConstIterator<ShortSeriesType>                      ShortSeriesConstIteratorType;
typedef itk::ImageRegionIterator<UnsignedCharImageType>                     UnsignedCharImageIteratorType;
typedef itk::ImageRegionIterator<UnsignedCharSeriesType>                    UnsignedCharSeriesIteratorType;
typedef itk::ImageRegionIterator<ShortImageType>                            ShortImageIteratorType;
typedef itk::ImageRegionIterator<ShortSeriesType>                           ShortSeriesIteratorType;
typedef itk::GDCMSeriesFileNames                                            DICOMSeriesNameGeneratorType;
typedef itk::NumericSeriesFileNames                                         SeriesNameGeneratorType;


#endif // IMAGECOMMON_H
