#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QWidget>
#include <QTimer>
#include "Helper.h"


class Helper;

class GLWidget : public QWidget
{
    Q_OBJECT

public:
    GLWidget(Helper *helper, QWidget *parent);

public slots:
    void Animate();

signals:
    void MiddleButtonMove(int x, int y);
    void RightButtonMove(int y);
    void MiddleButtonDoubleClick();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

protected:
    short m_MouseMiddleStartPos[2];
    short m_MouseMiddleCurrentPos[2];
    short m_MouseRightStartPos[2];
    short m_MouseRightCurrentPos[2];
    
    bool m_MiddleButtonDown;
    bool m_RightButtonDown;
    
private:
    Helper *m_Helper;
    int m_iElapsed;
};


#endif
