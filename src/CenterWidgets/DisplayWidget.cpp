#include "DisplayWidget.h"


DisplayWidget::DisplayWidget(ImageHandler *handler, QWidget *parent)
    : QWidget(parent)
    , m_bMiddleButtonDown(false)
    , m_bRightButtonDown(false)
    , m_pHandler(handler)
    , m_iElapsed(0)
    , m_iActiveSlice(0)
    , m_bShowAnnotation(true)
    , m_qtDisplayImage(new QImage())
    , m_pUpperLeft(NULL)
    , m_pUpperRight(NULL)
    , m_pLowerLeft(NULL)
    , m_pLowerRight(NULL)
{
    resize(512, 512);
    setAutoFillBackground(false);

    InitializeAnnotation();
}


DisplayWidget::~DisplayWidget()
{
    if(m_pUpperLeft != NULL)
    {
        delete m_pUpperLeft;
        m_pUpperLeft = NULL;
    }
    if(m_pUpperRight != NULL)
    {
        delete m_pUpperRight;
        m_pUpperRight = NULL;
    }
    if(m_pLowerLeft != NULL)
    {
        delete m_pLowerLeft;
        m_pLowerLeft = NULL;
    }
    if(m_pLowerRight!= NULL)
    {
        delete m_pLowerRight;
        m_pLowerRight = NULL;
    }
    if(m_qtDisplayImage != NULL)
    {
        delete m_qtDisplayImage;
        m_qtDisplayImage = NULL;
    }
}


void DisplayWidget::InitializeAnnotation()
{
    m_pUpperLeft = new TextOverlayWidget(this);

    m_pUpperLeft->setGeometry(0, 0, 200, 100);
    m_pUpperLeft->SetFontSize(8);
    m_pUpperLeft->SetPenColor(QColor(255, 255, 0, 255));

    m_pUpperRight = new TextOverlayWidget(this);

    m_pUpperRight->setGeometry(this->geometry().width(), 0, 200, 100);
    m_pUpperRight->SetFontSize(8);
    m_pUpperRight->SetPenColor(QColor(255, 255, 0, 255));

    m_pLowerLeft = new TextOverlayWidget(this);

    m_pLowerLeft->setGeometry(0, this->geometry().height(), 200, 150);
    m_pLowerLeft->SetFontSize(8);
    m_pLowerLeft->SetPenColor(QColor(255, 255, 0, 255));

    m_pLowerRight = new TextOverlayWidget(this);

    m_pLowerRight->setGeometry(this->geometry().width(), this->geometry().height(), 200, 150);
    m_pLowerRight->SetFontSize(8);
    m_pLowerRight->SetPenColor(QColor(255, 255, 0, 255));
}


void DisplayWidget::ShowAnnotation()
{
    m_pUpperLeft->show();
    m_pUpperRight->show();
    m_pLowerLeft->show();
    m_pLowerRight->show();
}


void DisplayWidget::UpdateAnnotation()
{
    m_pUpperLeft->setGeometry(0, 0, 200, 100);
    m_pUpperLeft->SetOrigin(0, 0);
    m_pUpperLeft->SetWidth(200);
    m_pUpperLeft->SetHeight(100);
    m_pUpperLeft->SetAlignment(Qt::AlignLeft|Qt::AlignTop);

    m_pUpperRight->setGeometry(this->geometry().width()-200, 0, 200, 100);
    m_pUpperRight->SetOrigin(0, 0);
    m_pUpperRight->SetWidth(200);
    m_pUpperRight->SetHeight(100);
    m_pUpperRight->SetAlignment(Qt::AlignRight|Qt::AlignTop);

    m_pLowerLeft->setGeometry(0, this->geometry().height()-180, 200, 180);
    m_pLowerLeft->SetOrigin(0, 0);
    m_pLowerLeft->SetWidth(200);
    m_pLowerLeft->SetHeight(180);
    m_pLowerLeft->SetAlignment(Qt::AlignLeft|Qt::AlignBottom);

    m_pLowerRight->setGeometry(this->geometry().width()-200, this->geometry().height()-150, 200, 150);
    m_pLowerRight->SetOrigin(0, 0);
    m_pLowerRight->SetWidth(200);
    m_pLowerRight->SetHeight(150);
    m_pLowerRight->SetAlignment(Qt::AlignRight|Qt::AlignBottom);
}


void DisplayWidget::SetUpperLeftAnnotation(std::string text)
{
    m_pUpperLeft->SetText(text);
}


void DisplayWidget::SetUpperRightAnnotation(std::string text)
{
    m_pUpperRight->SetText(text);
}


void DisplayWidget::SetLowerLeftAnnotation(std::string text)
{
    m_pLowerLeft->SetText(text);
}


void DisplayWidget::SetLowerRightAnnotation(std::string text)
{
    m_pLowerRight->SetText(text);
}


void DisplayWidget::Animate()
{
    m_iElapsed = (m_iElapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}


void DisplayWidget::SetActiveSlice(int i)
{
    m_iActiveSlice = i;
}


int DisplayWidget::GetActiveSlice()
{
    return m_iActiveSlice;
}


QImage* DisplayWidget::GetDisplayImage()
{
    return m_qtDisplayImage;
}


void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    m_pHandler->Paint(&painter, event, m_iElapsed, m_qtDisplayImage, geometry());
    painter.end();

    if(m_bShowAnnotation)
    {
        UpdateAnnotation();
        ShowAnnotation();
    }
}


void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        m_bMiddleButtonDown = true;
        m_MouseMiddleStartPos[0] = (float)QCursor::pos().x()/(QGuiApplication::primaryScreen()->availableSize().width());
        m_MouseMiddleStartPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());
    }
    else if(event->button()==Qt::RightButton)
    {
        m_bRightButtonDown = true;
        m_MouseRightStartPos[0] = (float)QCursor::pos().x()/(QGuiApplication::primaryScreen()->availableSize().width());
        m_MouseRightStartPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());
    }
}


void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMiddleButtonDown)
    {
        m_MouseMiddleCurrentPos[0] = (float)QCursor::pos().x()/(QGuiApplication::primaryScreen()->availableSize().width());
        m_MouseMiddleCurrentPos[1] = (float)QCursor::pos().y()/(QGuiApplication::primaryScreen()->availableSize().height());

        float tmpX = m_MouseMiddleCurrentPos[0] - m_MouseMiddleStartPos[0];
        float tmpY = m_MouseMiddleCurrentPos[1] - m_MouseMiddleStartPos[1];
        
        m_MouseMiddleStartPos[0] = m_MouseMiddleCurrentPos[0];
        m_MouseMiddleStartPos[1] = m_MouseMiddleCurrentPos[1];

        emit MiddleButtonMove(tmpX, tmpY);
    }
    else if(m_bRightButtonDown)
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
        m_bMiddleButtonDown = false;
        m_MouseMiddleCurrentPos[0] = 0.0;
        m_MouseMiddleCurrentPos[1] = 0.0;
        m_MouseMiddleStartPos[0] = 0.0;
        m_MouseMiddleStartPos[1] = 0.0;
    }
    else if(event->button()==Qt::RightButton)
    {
        m_bRightButtonDown = false;
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


void DisplayWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta()/(8*15);

    emit WheelMovement(numDegrees.rx(), numDegrees.ry());
}
