#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H


#include "ImageCommon.h"


class ImageContainer
{
public:
    ImageContainer();
    virtual ~ImageContainer();

    void Allocate(int sliceNumber);
    void SetDimension(unsigned int dim);
    unsigned int GetDimension();
    ShortImageType::Pointer* GetImage(int slice);
    DICOMIOType::Pointer* GetIOObject(int slice);
    short GetWidth(int slice);
    short GetHeight(int slice);
    short GetLength();
    short GetDefaultWC(int slice);
    short GetDefaultWW(int slice);
    void SetCurrentWC(short wc);
    short GetCurrentWC();
    void SetCurrentWW(short ww);
    short GetCurrentWW();
    std::string GetPatientName(int slice);
    std::string GetPatientID(int slice);
    std::string GetAccession(int slice);
    std::string GetStudyDescription(int slice);
    std::string GetStudyDate(int slice);
    std::string GetSeriesDescription(int slice);
    std::string GetAcqusitionDate(int slice);
    std::string GetAcqusitionTime(int slice);
    std::string GetStudyInstanceUID(int slice);
    void SetMinSliceNum(int min);
    int GetMinSliceNum();
    void SetMaxSliceNum(int max);
    int GetMaxSliceNum();
    void SetCurrentSizeFactor(double factor);
    double GetCurrentSizeFactor();

private:
    unsigned int m_uiDim;
    ShortImageType::Pointer* m_sImageObj;
    DICOMIOType::Pointer* m_DicomIO;
    short m_sCurrentWC;
    short m_sCurrentWW;
    int m_iMinSliceNum;
    int m_iMaxSliceNum;
    double m_dCurrentSizeFactor;
    int m_iSlices;

};


#endif // IMAGECONTAINER_H
