#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QGLWidget>
#include <QTimer>
#include "helper.h"


class Helper;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(Helper *helper, QWidget *parent);

public slots:
    void animate();

signals:
    void middleButtonMove(int x, int y);
    void rightButtonMove(int y);
    void middleButtonDoubleClick();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    short m_mouseMiddleStartPos[2];
    short m_mouseMiddleCurrentPos[2];
    short m_mouseRightStartPos[2];
    short m_mouseRightCurrentPos[2];
    
    bool m_middleButtonDown;
    bool m_rightButtonDown;
    
private:
    Helper *helper;
    int elapsed;
};


#endif
