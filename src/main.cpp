#include "ImageIO.h"
#include "ImageFilter.h"


int main()
{
    UnsignedCharImageType::Pointer imageObj = UnsignedCharImageType::New();
    UnsignedCharSeriesType::Pointer imageObj_3d = UnsignedCharSeriesType::New();
    ShortImageType::Pointer s_imageObj = ShortImageType::New();
    ShortSeriesType::Pointer s_imageObj_3d = ShortSeriesType::New();
    std::string* pSeriesName = NULL;
    
    /*ImageIO::ReadPNGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/211.png", imageObj);
    ImageIO::WritePNGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/211.png", imageObj);

    ImageIO::ReadJPEGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/237.jpg", imageObj);
    ImageIO::WriteJPEGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/237.jpeg", imageObj);

    ImageIO::ReadDICOMImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/LI.MR.RESEARCH_PHANTOM.0007.0047.2013.08.06.19.22.15.906250.27825948.IMA", s_imageObj);
    ImageIO::WriteDICOMImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/Phantom.IMA", s_imageObj);

    ImageIO::ReadPNGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/PNG_Series/", imageObj_3d, "%03d.png", 85, 325);
    ImageIO::WritePNGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/PNG_Series/", imageObj_3d, "%03d.png", 85, 325);

    ImageIO::ReadJPEGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/JPEG_Series/", imageObj_3d, "%03d.jpg", 85, 325);
    ImageIO::WriteJPEGSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/JPEG_Series/", imageObj_3d, "%03d.jpg", 85, 325);
    */

    /*ImageIO::SetDICOMFolder("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/DICOM_Series/", &pSeriesName);
    std::cout<<"There is (are) "<<sizeof(pSeriesName)/sizeof(std::string)<<" DICOM series in the folder"<<std::endl;
    for(int i=0;i<sizeof(pSeriesName)/sizeof(std::string);i++)
    {
        std::cout<<"Reading "<<pSeriesName[i]<<std::endl;
        ImageIO::ReadDICOMSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/DICOM_Series/", pSeriesName[i], s_imageObj_3d);
        std::cout<<"Writing "<<pSeriesName[i]<<std::endl;
        ImageIO::WriteDICOMSeries("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/DICOM_Series/", s_imageObj_3d, "%03d.IMA", 1, 96);
    }
    */

    /*ImageIO::ReadPNGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/211.png", imageObj);
    ImageFilter::Cast<UnsignedCharImageType, ShortImageType,
                      UnsignedCharImageType::Pointer, ShortImageType::Pointer>(imageObj, s_imageObj);
    ImageIO::WriteDICOMImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/211.IMA", s_imageObj);
    */
    
    ImageIO::ReadDICOMImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/input/LI.MR.RESEARCH_PHANTOM.0007.0047.2013.08.06.19.22.15.906250.27825948.IMA", s_imageObj);
    ImageFilter::RescaleIntensityFilter<ShortImageType, UnsignedCharImageType,
                      ShortImageType::Pointer, UnsignedCharImageType::Pointer>(s_imageObj, imageObj);
    ImageIO::WritePNGImage("/home/zhitaoli/workspace/Git/DICOM_Tool/data/output/liver.png", imageObj);
    
    return 0;
}
