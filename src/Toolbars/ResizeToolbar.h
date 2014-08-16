#ifndef RESIZETOOLBAR_H
#define RESIZETOOLBAR_H


#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QComboBox>


class ResizeToolbar : public QToolBar
{
    Q_OBJECT

public:
    ResizeToolbar();
    ~ResizeToolbar();

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
