#include "ResizeToolBar.h"


ResizeToolBar::ResizeToolBar()
{
    setWindowTitle("ResizeToolBar");

    m_dropDownZoom = new QComboBox;
    
    addAction(QIcon(QPixmap("./icons/Zoom_In.png")), "Zoom in (25%)");
    addAction(QIcon(QPixmap("./icons/Zoom_Out.png")), "Zoom out (25%)");
    addWidget(m_dropDownZoom);
    addAction(QIcon(QPixmap("./icons/Zoom.png")), "Original size");
    addAction(QIcon(QPixmap("./icons/viewmagfit.png")), "Fit to height");
}


ResizeToolBar::~ResizeToolBar()
{
    delete m_dropDownZoom;
}
