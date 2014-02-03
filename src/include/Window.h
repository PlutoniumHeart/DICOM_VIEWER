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


#include "glWidget.h"
#include "ImageWindowingDock.h"
#include "ImageListDock.h"
#include "FileToolBar.h"
#include "ResizeToolBar.h"


class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();
    ~Window();

private slots:
    void OpenDICOM();
    void CloseSeries();
    void UpdateImage();
    void ResetWindow();
    void Pan(int scale);
    void ZoomIn25Present();
    void ZoomOut25Present();
    void ZoomOriginalSize();
    void ZoomFitToHeight();
    void ZoomComboResize(int index);
    void ZoomCustomSize();
    void UpdateImageID(QModelIndex index);
    
private:
    GLWidget *m_glDisplay;
    QScrollArea *m_ScrollArea;
    QTimer *m_Timer;
    QMenu *m_MainMenu;
    FileToolBar *m_FileToolBar;
    ResizeToolBar *m_ResizeToolBar;
    ImageWindowDock *m_ImageWindowingDock;
    ImageListDock *m_ImageListDock;
    Helper m_Helper;

private:
    void CreateActions();
    void CreateMenuBar();
    void CreateDockWindows();
    void CreateToolBar();
    void AdjustScrollBar(QScrollBar* scrollBar, double factor);
};


#endif
