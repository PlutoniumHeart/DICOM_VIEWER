#include "ImageOps.h"


ImageOps::ImageOps()
{
}


ImageOps::~ImageOps()
{
}


std::shared_ptr<ImageData> ImageOps::OpenSlice(QString filename)
{
    std::shared_ptr<ImageData> image = std::make_shared<ImageData>();

    DICOMIOType::Pointer io = DICOMIOType::New();
    ShortImageType::Pointer slice = ImageIO::ReadDICOMSlice(filename.toStdString(), io);

    image->PushBackSlice(slice, io);

    return image;
}


std::shared_ptr<ImageData> ImageOps::OpenSeries(QString folder)
{
    if (folder.isEmpty())
        return NULL;

    std::vector<std::string> filenames;
    int fileNum = ImageIO::ProbeDICOMFolder(folder.toStdString(), filenames);
    std::shared_ptr<ImageData> image = std::make_shared<ImageData>();

    for (int i=0;i<fileNum;i++)
    {
        DICOMIOType::Pointer io = DICOMIOType::New();
        ShortImageType::Pointer slice = ImageIO::ReadDICOMSlice(filenames[i], io);

        image->PushBackSlice(slice, io);
    }

    return image;
}
