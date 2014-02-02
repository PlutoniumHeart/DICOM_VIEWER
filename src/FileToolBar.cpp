#include "FileToolBar.h"


FileToolBar::FileToolBar()
{
    setWindowTitle("FileToolBar");

    openDICOM = new QAction(QIcon(":/icons/Image.png"), tr("Open DICON image"), this);
    addAction(openDICOM);
}


FileToolBar::~FileToolBar()
{
}


QAction* FileToolBar::GetOpenDICOMAction()
{
    return openDICOM;
}
