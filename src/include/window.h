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


#include "glwidget.h"
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
    void openDICOM();
    void updateImage();
    void resetWindow();
    void pan(int scale);
    void zoomIn25Present();
    void zoomOut25Present();
    void zoomOriginalSize();
    void zoomFitToHeight();
    void zoomComboResize(int index);
    void zoomCustomSize();
    
private:
    GLWidget *m_glDisplay;
    QScrollArea *m_scrollArea;
    QTimer *m_timer;
    QMenu *m_mainMenu;
    FileToolBar *m_fileToolBar;
    ResizeToolBar *m_resizeToolBar;
    ImageWindowDock *m_imageWindowingDock;
    Helper helper;

    void setupMenuBar();
};


#endif
