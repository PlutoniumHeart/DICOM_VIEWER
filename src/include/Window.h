#ifndef WINDOW_H
#define WINDOW_H


#include <string>
#include <sstream>
#include <QMainWindow>
#include <QTimer>
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QLineEdit>


#include "glWidget.h"
#include "ImageWindowingDock.h"
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
    void UpdateImage();
    void ResetWindow();
    void Pan(int scale);
    void ZoomIn25Present();
    void ZoomOut25Present();
    void ZoomOriginalSize();
    void ZoomFitToHeight();
    void ZoomComboResize(int index);
    void ZoomCustomSize();
    
private:
    GLWidget *m_glDisplay;
    QScrollArea *m_ScrollArea;
    QTimer *m_Timer;
    QMenu *m_MainMenu;
    FileToolBar *m_FileToolBar;
    ResizeToolBar *m_ResizeToolBar;
    ImageWindowDock *m_ImageWindowingDock;
    Helper m_Helper;

private:    
    void SetupMenuBar();
};


#endif
