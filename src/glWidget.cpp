#include "glWidget.h"


GLWidget::GLWidget(Helper *helper, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), m_Helper(helper)
    , m_MiddleButtonDown(false)
    , m_RightButtonDown(false)
{
    m_iElapsed = 0;
    resize(512, 512);
    setAutoFillBackground(false);
}


void GLWidget::Animate()
{
    m_iElapsed = (m_iElapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}


void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    m_Helper->Paint(&painter, event, m_iElapsed, geometry());
    painter.end();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_MiddleButtonDown = true;
        m_MouseMiddleStartPos[0] = event->x();
        m_MouseMiddleStartPos[1] = event->y();
    }
    else if(event->button()==Qt::RightButton)
    {
        m_RightButtonDown = true;
        m_MouseRightStartPos[0] = event->x();
        m_MouseRightStartPos[1] = event->y();
    }
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_MiddleButtonDown)
    {
        m_MouseMiddleCurrentPos[0] = event->x();
        m_MouseMiddleCurrentPos[1] = event->y();

        int tmpX = m_MouseMiddleCurrentPos[0] - m_MouseMiddleStartPos[0];
        int tmpY = m_MouseMiddleCurrentPos[1] - m_MouseMiddleStartPos[1];
        
        m_MouseMiddleStartPos[0] = event->x();
        m_MouseMiddleStartPos[1] = event->y();

        emit MiddleButtonMove(tmpX, tmpY);
    }
    else if(m_RightButtonDown)
    {
        m_MouseRightCurrentPos[0] = event->x();
        m_MouseRightCurrentPos[1] = event->y();

        int tmpX = m_MouseRightCurrentPos[0] - m_MouseRightStartPos[0];
        int tmpY = m_MouseRightCurrentPos[1] - m_MouseRightStartPos[1];
        
        m_MouseRightStartPos[0] = event->x();
        m_MouseRightStartPos[1] = event->y();

        emit RightButtonMove(tmpY);
    }
}


void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_MiddleButtonDown = false;
    }
    else if(event->button()==Qt::RightButton)
    {
        m_RightButtonDown = false;
    }
}


void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
        emit MiddleButtonDoubleClick();
}
