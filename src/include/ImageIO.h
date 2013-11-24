#ifndef IMAGEIO_H
#define IMAGEIO_H


#include "ImageCommon.h"


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

    template<class T1, class T2>
    static bool CreateBlankImage(T1 imageObj, int x, int y);
    template<class T1, class T2>
    static bool CreateBlankSeries(T1 imageObj, int x, int y, int z);
    
private:
    static PNGIOType::Pointer m_pPNGIO;
    static JPEGIOType::Pointer m_pJPEGIO;
    static DICOMIOType::Pointer m_pDICOMIO;
};


template<class T1, class T2>
bool ImageIO::CreateBlankImage(T1 imageObj, int x, int y)
{
    itk::Index<D2> start;
    itk::Size<D2> size;

    start.Fill(0);
    size[0] = x;
    size[1] = y;
    T2 region(start, size);

    imageObj->SetRegions(region);
    imageObj->Allocate();
    imageObj->FillBuffer(0);
    
    return true;
}


template<class T1, class T2>
bool ImageIO::CreateBlankSeries(T1 imageObj, int x, int y, int z)
{
    itk::Index<D3> start;
    itk::Size<D3> size;

    start.Fill(0);
    size[0] = x;
    size[1] = y;
    size[2] = z;
    T2 region(start, size);

    imageObj->SetRegions(region);
    imageObj->Allocate();
    imageObj->FillBuffer(0);
    
    return true;
}


#endif // IMAGEIO_H
