#ifndef RESIZETOOLBAR_H
#define RESIZETOOLBAR_H


#include <QAction>
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
    QComboBox* m_DropDownZoom;

    QAction* m_ZoomIn;
    QAction* m_ZoomOut;
    QAction* m_OriginSize;
    QAction* m_FitToHeight;
};


#endif // RESIZETOOLBAR_H
