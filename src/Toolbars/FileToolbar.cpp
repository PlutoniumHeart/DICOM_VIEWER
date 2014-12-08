#include "FileToolbar.h"


FileToolbar::FileToolbar()
{
    setWindowTitle("FileToolbar");

    m_pOpenDICOM = new QAction(QIcon(":/icons/Image.png"), tr("Open DICON image"), this);
    m_pOpenDICOMSeries = new QAction(QIcon(":/icons/ImageSeries.png"), tr("Open DICON Series"), this);
    addAction(m_pOpenDICOM);
    addAction(m_pOpenDICOMSeries);
}


FileToolbar::~FileToolbar()
{
}


QAction* FileToolbar::GetOpenDICOMAction()
{
    return m_pOpenDICOM;
}


QAction* FileToolbar::GetOpenDICOMSeriesAction()
{
    return m_pOpenDICOMSeries;
}
