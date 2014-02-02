#include "FileToolBar.h"


FileToolBar::FileToolBar()
{
    setWindowTitle("FileToolBar");

    openDICOM = addAction(QIcon(":/icons/Image.png"), "Open DICOM image");
}


FileToolBar::~FileToolBar()
{
}


QAction* FileToolBar::GetOpenDICOMAction()
{
    return openDICOM;
}
