#include "glwidget.h"


GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), helper(helper)
    , m_middleButtonDown(false)
    , m_rightButtonDown(false)
{
    elapsed = 0;
    resize(512, 512);
    setAutoFillBackground(false);
}


void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}


void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed, geometry());
    painter.end();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_middleButtonDown = true;
        m_mouseMiddleStartPos[0] = event->x();
        m_mouseMiddleStartPos[1] = event->y();
    }
    else if(event->button()==Qt::RightButton)
    {
        m_rightButtonDown = true;
        m_mouseRightStartPos[0] = event->x();
        m_mouseRightStartPos[1] = event->y();
    }
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_middleButtonDown)
    {
        m_mouseMiddleCurrentPos[0] = event->x();
        m_mouseMiddleCurrentPos[1] = event->y();

        int tmpX = m_mouseMiddleCurrentPos[0] - m_mouseMiddleStartPos[0];
        int tmpY = m_mouseMiddleCurrentPos[1] - m_mouseMiddleStartPos[1];
        
        m_mouseMiddleStartPos[0] = event->x();
        m_mouseMiddleStartPos[1] = event->y();

        emit middleButtonMove(tmpX, tmpY);
    }
    else if(m_rightButtonDown)
    {
        m_mouseRightCurrentPos[0] = event->x();
        m_mouseRightCurrentPos[1] = event->y();

        int tmpX = m_mouseRightCurrentPos[0] - m_mouseRightStartPos[0];
        int tmpY = m_mouseRightCurrentPos[1] - m_mouseRightStartPos[1];
        
        m_mouseRightStartPos[0] = event->x();
        m_mouseRightStartPos[1] = event->y();

        emit rightButtonMove(tmpY);
    }
}


void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_middleButtonDown = false;
    }
    else if(event->button()==Qt::RightButton)
    {
        m_rightButtonDown = false;
    }
}


void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit middleButtonDoubleClick();
}
