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
    
    m_ZoomIn = new QAction(QIcon(":/icons/Zoom_In.png"), tr("Zoom in (25%)"), this);
    m_ZoomOut = new QAction(QIcon(":/icons/Zoom_Out.png"), tr("Zoom out (25%)"), this);
    addAction(m_ZoomIn);
    addAction(m_ZoomOut);
    addWidget(m_DropDownZoom);
    m_OriginSize = new QAction(QIcon(":/icons/Zoom.png"), tr("Original size"), this);
    m_FitToHeight = new QAction(QIcon(":/icons/viewmagfit.png"), tr("Fit to height"), this);
    addAction(m_OriginSize);
    addAction(m_FitToHeight);
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
