#ifndef WINDOW_H
#define WINDOW_H


#include <string>
#include <sstream>

#include <QMainWindow>
#include <QTimer>
#include <QScrollArea>
#include <QScrollBar>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QLineEdit>

#include "FileToolbar.h"
#include "ResizeToolbar.h"
#include "ImageHandler.h"
#include "DisplayWidget.h"
#include "ImageWindowingDock.h"
#include "ImageListDock.h"


class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();
    ~Window();

private:
    QMenu* m_pMenu;
    FileToolbar* m_pFileToolbar;
    ResizeToolbar* m_pResizeToolbar;
    DisplayWidget* m_pDisplay;
    QScrollArea* m_pScrollArea;
    QTimer* m_pTimer;
    ImageWindowDock* m_pImageWindowingDock;
    ImageListDock* m_pImageListDock;

    ImageHandler m_ImageHandler;

private:
    void CreateMenus();
    void CreateToolbars();
    void CreateCenterWidgets();
    void CreateDocks();
    void CreateConnections();

private slots:
    void OpenDicomImage();
    void OpenDicomSeries();
    void CloseDicomImage();
    void Pan(float scale);
    void UpdateImage();
    void UpdateImage(int index);
    void ResetWindow();
    void ZoomIn25Present();
    void ZoomOut25Present();
    void ZoomOriginalSize();
    void ZoomFitToHeight();
    void ZoomComboResize(int index);
    void ZoomCustomSize();

};


#endif
