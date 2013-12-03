#include "ResizeToolBar.h"


ResizeToolBar::ResizeToolBar()
{
    setWindowTitle("ResizeToolBar");

    m_dropDownZoom = new QComboBox;
    
    m_zoomIn = addAction(QIcon(QPixmap("./icons/Zoom_In.png")), "Zoom in (25%)");
    m_zoomOut = addAction(QIcon(QPixmap("./icons/Zoom_Out.png")), "Zoom out (25%)");
    addWidget(m_dropDownZoom);
    m_originSize = addAction(QIcon(QPixmap("./icons/Zoom.png")), "Original size");
    m_fitToHeight = addAction(QIcon(QPixmap("./icons/viewmagfit.png")), "Fit to height");
}


ResizeToolBar::~ResizeToolBar()
{
    delete m_dropDownZoom;
}


QAction* ResizeToolBar::GetActionZoomIn()
{
    return m_zoomIn;
}


QAction* ResizeToolBar::GetActionZoomOut()
{
    return m_zoomOut;
}


QAction* ResizeToolBar::GetActionOriginalSize()
{
    return m_originSize;
}


QAction* ResizeToolBar::GetActionFitToHeight()
{
    return m_fitToHeight;
}
