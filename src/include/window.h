#ifndef WINDOW_H
#define WINDOW_H


#include <QMainWindow>
#include <QTimer>
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>

#include "glwidget.h"
#include "helper.h"
#include "ImageWindowingDock.h"


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
    
private:
    GLWidget *m_glDisplay;
    QScrollArea *m_scrollArea;
    QTimer *m_timer;
    QMenu *m_mainMenu;
    ImageWindowDock *m_lowerDock;
    Helper helper;

    void setupMenuBar();
};


#endif
