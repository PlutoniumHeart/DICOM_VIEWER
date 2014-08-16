#include "DisplayWidget.h"


DisplayWidget::DisplayWidget(ImageHandler *handler, QWidget *parent)
    : QWidget(parent)
    , m_Handler(handler)
    , m_MiddleButtonDown(false)
    , m_RightButtonDown(false)
{
    m_iElapsed = 0;
    resize(512, 512);
    setAutoFillBackground(false);
}


void DisplayWidget::Animate()
{
    m_iElapsed = (m_iElapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}


void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    m_Handler->Paint(&painter, event, m_iElapsed, geometry());
    painter.end();
}


void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_MiddleButtonDown = true;
        m_MouseMiddleStartPos[0] = (float)QCursor::pos().x()/(QGuiApplication::primaryScreen()->availableSize().width());
        m_MouseMiddleStartPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());
    }
    else if(event->button()==Qt::RightButton)
    {
        m_RightButtonDown = true;
        m_MouseRightStartPos[0] = (float)QCursor::pos().x()/(QGuiApplication::primaryScreen()->availableSize().width());
        m_MouseRightStartPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());
    }
}


void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_MiddleButtonDown)
    {
        m_MouseMiddleCurrentPos[0] = (float)QCursor::pos().x()/(QGuiApplication::primaryScreen()->availableSize().width());
        m_MouseMiddleCurrentPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());

        float tmpX = m_MouseMiddleCurrentPos[0] - m_MouseMiddleStartPos[0];
        float tmpY = m_MouseMiddleCurrentPos[1] - m_MouseMiddleStartPos[1];
        
        m_MouseMiddleStartPos[0] = m_MouseMiddleCurrentPos[0];
        m_MouseMiddleStartPos[1] = m_MouseMiddleCurrentPos[1];

        emit MiddleButtonMove(tmpX, tmpY);
    }
    else if(m_RightButtonDown)
    {
        m_MouseRightCurrentPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());
        float tmpY = m_MouseRightCurrentPos[1] - m_MouseRightStartPos[1];
        m_MouseRightStartPos[1] = m_MouseRightCurrentPos[1];
        emit RightButtonMove(tmpY);
    }
}


void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_MiddleButtonDown = false;
        m_MouseMiddleCurrentPos[0] = 0.0;
        m_MouseMiddleCurrentPos[1] = 0.0;
        m_MouseMiddleStartPos[0] = 0.0;
        m_MouseMiddleStartPos[1] = 0.0;
    }
    else if(event->button()==Qt::RightButton)
    {
        m_RightButtonDown = false;
        m_MouseRightCurrentPos[0] = 0.0;
        m_MouseRightCurrentPos[1] = 0.0;
        m_MouseRightStartPos[0] = 0.0;
        m_MouseRightStartPos[1] = 0.0;
    }
}


void DisplayWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
        emit MiddleButtonDoubleClick();
}
