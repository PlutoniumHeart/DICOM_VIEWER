#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H


#include <QWidget>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include "ImageHandler.h"


//class ImageHandler;

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(ImageHandler *handler, QWidget *parent);

public slots:
    void Animate();

signals:
    void MiddleButtonMove(float x, float y);
    void RightButtonMove(float y);
    void MiddleButtonDoubleClick();
    void WheelMovement(int x, int y);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

protected:
    float m_MouseMiddleStartPos[2];
    float m_MouseMiddleCurrentPos[2];
    float m_MouseRightStartPos[2];
    float m_MouseRightCurrentPos[2];
    
    bool m_MiddleButtonDown;
    bool m_RightButtonDown;
    
private:
    ImageHandler* m_Handler;
    int m_iElapsed;

};


#endif // DISPLAYWIDGET_H
