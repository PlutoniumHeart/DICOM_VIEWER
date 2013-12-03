#ifndef RESIZETOOLBAR_H
#define RESIZETOOLBAR_H


#include <QToolBar>
#include <QIcon>
#include <QComboBox>


class ResizeToolBar : public QToolBar
{
    Q_OBJECT

public:
    ResizeToolBar();
    ~ResizeToolBar();

    QAction* GetActionZoomIn();
    QAction* GetActionZoomOut();
    QAction* GetActionOriginalSize();
    QAction* GetActionFitToHeight();

    QComboBox* GetComboResize();

private:
    QComboBox* m_dropDownZoom;

    QAction* m_zoomIn;
    QAction* m_zoomOut;
    QAction* m_originSize;
    QAction* m_fitToHeight;
};


#endif // RESIZETOOLBAR_H
