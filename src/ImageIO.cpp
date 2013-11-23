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


bool ImageIO::ReadDICOMImage(std::string inputFile, ShortImageType::Pointer& imageObj)
{
    ShortImageReadType::Pointer reader = ShortImageReadType::New();
    reader->SetImageIO(m_pDICOMIO);
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


bool ImageIO::WriteDICOMImage(std::string outputFile, ShortImageType::Pointer& imageObj)
{
    ShortImageWriteType::Pointer writer = ShortImageWriteType::New();
    DICOMIOType::Pointer pDICOMIO = DICOMIOType::New();
    writer->SetImageIO(m_pDICOMIO);
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
