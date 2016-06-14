#ifndef IMAGEDATA_H
#define IMAGEDATA_H


#include <QImage>

#include "ImageCommon.h"


class ImageData
{
public:
    ImageData();
    ~ImageData();

    void PushBackSlice(ShortImageType::Pointer slice, itk::GDCMImageIO::Pointer io);
    void EraseSlice(int idx);
    void Clear();

    std::vector<QImage>* GetDisplayImage();
    QImage* GetDummyImage();
    std::vector<DICOMIOType::Pointer>* GetIO();
    void UpdateImageWindow(int slice, int wc, int ww);

    void Lock();
    void UnLock();

    short GetWidth(int slice);
    short GetHeight(int slice);
    short GetDepth();
    short GetDefaultWC(int slice);
    short GetDefaultWW(int slice);
    short GetCurrentWC(int slice);
    void SetCurrentWC(int slice, short wc);
    short GetCurrentWW(int slice);
    void SetCurrentWW(int slice, short ww);
    std::string GetPatientName(int slice);
    std::string GetPatientID(int slice);
    std::string GetAccession(int slice);
    std::string GetStudyDescription(int slice);
    std::string GetStudyDate(int slice);
    std::string GetSeriesDescription(int slice);
    std::string GetAcqusitionDate(int slice);
    std::string GetAcqusitionTime(int slice);
    std::string GetStudyInstanceUID(int slice);

private:
    QImage ToDisplayImage(ShortImageType::Pointer slice, int wc, int ww);
    void PushBackWindowInfo(DICOMIOType::Pointer io);

private:
    std::vector<ShortImageType::Pointer> m_vImageObj;
    std::vector<DICOMIOType::Pointer> m_vDicomIO;
    std::vector<QImage> m_vDisplayImage;
    QImage m_DummyImage;
    std::vector<short> m_vWCs;
    std::vector<short> m_vWWs;

};


#endif // IMAGEDATA_H
