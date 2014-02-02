#include "ResizeToolBar.h"


ResizeToolBar::ResizeToolBar()
{
    setWindowTitle("ResizeToolBar");

    m_dropDownZoom = new QComboBox;
    m_dropDownZoom->setEditable(true);
    m_dropDownZoom->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    m_dropDownZoom->setInsertPolicy(QComboBox::NoInsert);
    m_dropDownZoom->setMinimumWidth(120);
    m_dropDownZoom->addItem("800%", 8.0);
    m_dropDownZoom->addItem("700%", 7.0);
    m_dropDownZoom->addItem("600%", 6.0);
    m_dropDownZoom->addItem("500%", 5.0);
    m_dropDownZoom->addItem("400%", 4.0);
    m_dropDownZoom->addItem("300%", 3.0);
    m_dropDownZoom->addItem("200%", 2.0);
    m_dropDownZoom->addItem("100%", 1.0);
    m_dropDownZoom->addItem("50%", 0.5);
    m_dropDownZoom->setCurrentText("100%");
    
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


QComboBox* ResizeToolBar::GetComboResize()
{
    return m_dropDownZoom;
}
