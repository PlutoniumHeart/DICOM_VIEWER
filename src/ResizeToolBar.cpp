#include "ResizeToolBar.h"


ResizeToolBar::ResizeToolBar()
{
    setWindowTitle("ResizeToolBar");

    m_DropDownZoom = new QComboBox;
    m_DropDownZoom->setEditable(true);
    m_DropDownZoom->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    m_DropDownZoom->setInsertPolicy(QComboBox::NoInsert);
    m_DropDownZoom->setMinimumWidth(120);
    m_DropDownZoom->addItem("800%", 8.0);
    m_DropDownZoom->addItem("700%", 7.0);
    m_DropDownZoom->addItem("600%", 6.0);
    m_DropDownZoom->addItem("500%", 5.0);
    m_DropDownZoom->addItem("400%", 4.0);
    m_DropDownZoom->addItem("300%", 3.0);
    m_DropDownZoom->addItem("200%", 2.0);
    m_DropDownZoom->addItem("100%", 1.0);
    m_DropDownZoom->addItem("50%", 0.5);
    m_DropDownZoom->setCurrentText("100%");
    
    m_ZoomIn = addAction(QIcon(QPixmap(":/icons/Zoom_In.png")), "Zoom in (25%)");
    m_ZoomOut = addAction(QIcon(QPixmap(":/icons/Zoom_Out.png")), "Zoom out (25%)");
    addWidget(m_DropDownZoom);
    m_OriginSize = addAction(QIcon(QPixmap(":/icons/Zoom.png")), "Original size");
    m_FitToHeight = addAction(QIcon(QPixmap(":/icons/viewmagfit.png")), "Fit to height");
}


ResizeToolBar::~ResizeToolBar()
{
    delete m_DropDownZoom;
}


QAction* ResizeToolBar::GetActionZoomIn()
{
    return m_ZoomIn;
}


QAction* ResizeToolBar::GetActionZoomOut()
{
    return m_ZoomOut;
}


QAction* ResizeToolBar::GetActionOriginalSize()
{
    return m_OriginSize;
}


QAction* ResizeToolBar::GetActionFitToHeight()
{
    return m_FitToHeight;
}


QComboBox* ResizeToolBar::GetComboResize()
{
    return m_DropDownZoom;
}
