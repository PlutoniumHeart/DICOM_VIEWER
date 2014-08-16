#include "FileToolbar.h"


FileToolbar::FileToolbar()
{
    setWindowTitle("FileToolbar");

    openDICOM = new QAction(QIcon(":/icons/Image.png"), tr("Open DICON image"), this);
    addAction(openDICOM);
}


FileToolbar::~FileToolbar()
{
}


QAction* FileToolbar::GetOpenDICOMAction()
{
    return openDICOM;
}
