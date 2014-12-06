#include "ImageIO.h"


PNGIOType::Pointer ImageIO::m_pPNGIO = PNGIOType::New();
JPEGIOType::Pointer ImageIO::m_pJPEGIO = JPEGIOType::New();
DICOMIOType::Pointer ImageIO::m_pDICOMIO = DICOMIOType::New();


ImageIO::ImageIO()
{
}


ImageIO::~ImageIO()
{
}


bool ImageIO::ReadPNGImage(std::string inputFile, UnsignedCharImageType::Pointer& imageObj)
{
    UnsignedCharImageReadType::Pointer reader = UnsignedCharImageReadType::New();
    reader->SetImageIO(m_pPNGIO);
    reader->SetFileName(inputFile);
    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception in reading PNG file: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj = reader->GetOutput();
    return true;
}


bool ImageIO::WritePNGImage(std::string outputFile, UnsignedCharImageType::Pointer& imageObj)
{
    UnsignedCharImageWriteType::Pointer writer = UnsignedCharImageWriteType::New();

    writer->SetImageIO(m_pPNGIO);
    writer->SetFileName(outputFile);
    writer->SetInput(imageObj);
    try
    {
        writer->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception in file writing: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    return true;
}


bool ImageIO::ReadPNGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                            std::string seriesFormat, int begin, int end)
{
    UnsignedCharSeriesReadType::Pointer reader = UnsignedCharSeriesReadType::New();
    SeriesNameGeneratorType::Pointer nameGenerator = SeriesNameGeneratorType::New();

    nameGenerator->SetSeriesFormat(folderName+seriesFormat);
    nameGenerator->SetStartIndex(begin);
    nameGenerator->SetEndIndex(end);
    nameGenerator->SetIncrementIndex(1);

    reader->SetImageIO(m_pPNGIO);
    reader->SetFileNames(nameGenerator->GetFileNames());
    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception caught in reading file series: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj = reader->GetOutput();
    return true;
}


bool ImageIO::WritePNGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                              std::string seriesFormat, int begin, int end)
{
    UnsignedCharSeriesWriteType::Pointer writer = UnsignedCharSeriesWriteType::New();
    SeriesNameGeneratorType::Pointer nameGenerator = SeriesNameGeneratorType::New();

    nameGenerator->SetSeriesFormat(folderName+seriesFormat);
    nameGenerator->SetStartIndex(begin);
    nameGenerator->SetEndIndex(end);
    nameGenerator->SetIncrementIndex(1);

    writer->SetImageIO(m_pPNGIO);
    writer->SetInput(imageObj);
    writer->SetFileNames(nameGenerator->GetFileNames());
    try
    {
        writer->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Execption caught in writing files: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    return true;
}


bool ImageIO::ReadJPEGImage(std::string inputFile, UnsignedCharImageType::Pointer& imageObj)
{
    UnsignedCharImageReadType::Pointer reader = UnsignedCharImageReadType::New();
    reader->SetImageIO(m_pJPEGIO);
    reader->SetFileName(inputFile);
    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception in reading PNG file: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj = reader->GetOutput();
    return true;
}


bool ImageIO::WriteJPEGImage(std::string outputFile, UnsignedCharImageType::Pointer& imageObj)
{
    UnsignedCharImageWriteType::Pointer writer = UnsignedCharImageWriteType::New();

    writer->SetImageIO(m_pJPEGIO);
    writer->SetFileName(outputFile);
    writer->SetInput(imageObj);
    try
    {
        writer->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception in file writing: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    return true;
}


bool ImageIO::ReadJPEGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                            std::string seriesFormat, int begin, int end)
{
    UnsignedCharSeriesReadType::Pointer reader = UnsignedCharSeriesReadType::New();
    SeriesNameGeneratorType::Pointer nameGenerator = SeriesNameGeneratorType::New();

    nameGenerator->SetSeriesFormat(folderName+seriesFormat);
    nameGenerator->SetStartIndex(begin);
    nameGenerator->SetEndIndex(end);
    nameGenerator->SetIncrementIndex(1);

    reader->SetImageIO(m_pJPEGIO);
    reader->SetFileNames(nameGenerator->GetFileNames());
    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception caught in reading file series: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj = reader->GetOutput();
    return true;
}


bool ImageIO::WriteJPEGSeries(std::string folderName, UnsignedCharSeriesType::Pointer& imageObj,
                              std::string seriesFormat, int begin, int end)
{
    UnsignedCharSeriesWriteType::Pointer writer = UnsignedCharSeriesWriteType::New();
    SeriesNameGeneratorType::Pointer nameGenerator = SeriesNameGeneratorType::New();

    nameGenerator->SetSeriesFormat(folderName+seriesFormat);
    nameGenerator->SetStartIndex(begin);
    nameGenerator->SetEndIndex(end);
    nameGenerator->SetIncrementIndex(1);

    writer->SetImageIO(m_pJPEGIO);
    writer->SetInput(imageObj);
    writer->SetFileNames(nameGenerator->GetFileNames());
    try
    {
        writer->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Execption caught in writing files: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    return true;
}


bool ImageIO::ReadDICOMImage(std::string inputFile, ShortImageType::Pointer& imageObj,
                             DICOMIOType::Pointer& IO)
{
    ShortImageReadType::Pointer reader = ShortImageReadType::New();
    reader->SetImageIO(IO);
    reader->SetFileName(inputFile);
    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception in reading DICOM file: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    imageObj = reader->GetOutput();
    return true;
}


bool ImageIO::WriteDICOMImage(std::string outputFile, ShortImageType::Pointer& imageObj,
                              DICOMIOType::Pointer& IO)
{
    ShortImageWriteType::Pointer writer = ShortImageWriteType::New();
    //DICOMIOType::Pointer pDICOMIO = DICOMIOType::New();
    writer->SetImageIO(IO);
    writer->SetFileName(outputFile);
    writer->SetInput(imageObj);
    try
    {
        writer->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exception in file writing: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    return true;
}


int ImageIO::SetDICOMFolder(std::string folderName, std::string** pSeriesName)
{
    short i = 0;
    short sNumberOfSeries = 0;
    
    DICOMSeriesNameGeneratorType::Pointer nameGenerator = DICOMSeriesNameGeneratorType::New();
    nameGenerator->AddSeriesRestriction("0020|0012");
    nameGenerator->SetDirectory(folderName);

    const std::vector<std::string> seriesUID = nameGenerator->GetSeriesUIDs();
    std::vector<std::string>::const_iterator seriesItr;
    sNumberOfSeries = seriesUID.size();
    *pSeriesName = new std::string[sNumberOfSeries];
    for(seriesItr=seriesUID.begin();seriesItr!=seriesUID.end();seriesItr++)
    {
        (*pSeriesName)[i++] = *seriesItr;
    }

    return sNumberOfSeries;
}


bool ImageIO::ReadDICOMSeries(std::string folderName, std::string seriesName,
                              ShortSeriesType::Pointer& imageObj)
{
    DICOMSeriesNameGeneratorType::Pointer nameGenerator = DICOMSeriesNameGeneratorType::New();
    ShortSeriesReadType::Pointer seriesReader = ShortSeriesReadType::New();
    seriesReader->SetImageIO(m_pDICOMIO);
    nameGenerator->AddSeriesRestriction("0020|0012");
    nameGenerator->SetDirectory(folderName);
    std::vector<std::string> fileNameContainer = nameGenerator->GetFileNames(seriesName);
    seriesReader->SetFileNames(fileNameContainer);

    try
    {
        seriesReader->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exceptions caught in reading file series: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }

    imageObj = seriesReader->GetOutput();
    return true;
}


bool ImageIO::WriteDICOMSeries(std::string folderName, ShortSeriesType::Pointer& imageObj,
                               std::string seriesFormat, int begin, int end)
{
    ShortSeriesWriteType::Pointer seriesWriter = ShortSeriesWriteType::New();
    seriesWriter->SetInput(imageObj);
    seriesWriter->SetImageIO(m_pDICOMIO);
    SeriesNameGeneratorType::Pointer nameGenerator = SeriesNameGeneratorType::New();
    nameGenerator->SetSeriesFormat(folderName+seriesFormat);
    nameGenerator->SetStartIndex(begin);
    nameGenerator->SetEndIndex(end);
    nameGenerator->SetIncrementIndex(1);
    seriesWriter->SetFileNames(nameGenerator->GetFileNames());

    try
    {
        seriesWriter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        std::cerr<<"Exeption caught in writing image series: "<<std::endl;
        std::cerr<<e<<std::endl;
        return false;
    }
    return true;
}


int ImageIO::PixelToArray(UnsignedCharImageType::Pointer& imageObj, unsigned char** array)
{
    int i = 0;
    UnsignedCharImageConstIteratorType in(imageObj, imageObj->GetLargestPossibleRegion());
    in.GoToBegin();
    while(!in.IsAtEnd())
    {
        (*array)[i++] = in.Get();
        ++in;
    }
    return 0;
}


int ImageIO::PixelToArray(UnsignedCharSeriesType::Pointer& imageObj, unsigned char** array)
{
    int i = 0;
    UnsignedCharSeriesConstIteratorType in(imageObj, imageObj->GetLargestPossibleRegion());
    in.GoToBegin();
    while(!in.IsAtEnd())
    {
        *array[i++] = in.Get();
        ++in;
    }
    return 0;
}
