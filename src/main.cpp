#include "ImageIO.h"


int main()
{
    UnsignedCharImageType::Pointer imageObj = UnsignedCharImageType::New();
    UnsignedCharSeriesType::Pointer imageObj_3d = UnsignedCharSeriesType::New();
    ShortImageType::Pointer s_imageObj = ShortImageType::New();
    
    ImageIO::ReadPNGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/211.png", imageObj);
    ImageIO::WritePNGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/211.png", imageObj);

    ImageIO::ReadJPEGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/237.jpg", imageObj);
    ImageIO::WriteJPEGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/237.jpeg", imageObj);

    ImageIO::ReadDICOMImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/LI.MR.RESEARCH_PHANTOM.0007.0047.2013.08.06.19.22.15.906250.27825948.IMA", s_imageObj);
    ImageIO::WriteDICOMImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/Phantom.IMA", s_imageObj);

    ImageIO::ReadPNGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/PNG_Series/", imageObj_3d, "%03d.png", 85, 325);
    ImageIO::WritePNGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/PNG_Series/", imageObj_3d, "%03d.png", 85, 325);

    ImageIO::ReadJPEGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/JPEG_Series/", imageObj_3d, "%03d.jpg", 85, 325);
    ImageIO::WriteJPEGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/JPEG_Series/", imageObj_3d, "%03d.jpg", 85, 325);
    
    return 0;
}
