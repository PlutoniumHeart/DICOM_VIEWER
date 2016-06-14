#include "CanvasWidget.h"


CanvasWidget::CanvasWidget(QWidget* parent)
    : QWidget(parent)
    , m_iElapsed(0)
    , m_iX(1)
    , m_iY(1)
    , m_dSizeFactor(1)
{
    m_pLayout = new QGridLayout;

    DisplayWidget* display = new DisplayWidget(this);
    m_vpDisplay.push_back(display);
    m_pLayout->addWidget(m_vpDisplay[0], 0, 1);
    m_pLayout->setSpacing(5);

    setLayout(m_pLayout);
}


CanvasWidget::~CanvasWidget()
{
    delete m_pLayout;
}


int CanvasWidget::GetNumDisplays()
{
    return m_vpDisplay.size();
}


double CanvasWidget::GetSizeFactor()
{
    return m_dSizeFactor;
}


void CanvasWidget::SetSizeFactor(double factor)
{
    m_dSizeFactor = factor;
}


int CanvasWidget::GetVerticalNum()
{
    return m_iY;
}


int CanvasWidget::GetHorizontalNum()
{
    return m_iX;
}


void CanvasWidget::Resize(QSize size)
{
    Resize(size.width(), size.height());
}


void CanvasWidget::Resize(int width, int height)
{
    resize((width+10)*m_iX, (height+10)*m_iY);

    for (int i=0;i<m_vpDisplay.size();i++)
    {
        m_vpDisplay[i]->resize(width, height);
    }
}


DisplayWidget* CanvasWidget::GetDisplayWidget(int i)
{
    return m_vpDisplay[i];
}


void CanvasWidget::SetupAnnotations(std::string UpperLeft, std::string UpperRight,
                                    std::string LowerLeft, std::string LowerRight)
{
    for (int i=0;i<m_vpDisplay.size();i++)
    {
        m_vpDisplay[i]->SetUpperLeftAnnotation(UpperLeft);
        m_vpDisplay[i]->SetUpperRightAnnotation(UpperRight);
        m_vpDisplay[i]->SetLowerLeftAnnotation(LowerLeft);
        m_vpDisplay[i]->SetLowerRightAnnotation(LowerRight);
    }
}


void CanvasWidget::Animate()
{
    m_iElapsed = (m_iElapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;

    for (int i=0;i<m_vpDisplay.size();i++)
    {
        m_vpDisplay[i]->repaint();
    }
}


void CanvasWidget::Rearrange(int x, int y)
{
    m_iX = x;
    m_iY = y;

    for (int i=0;i<m_vpDisplay.size();i++)
    {
        delete m_vpDisplay[i];
    }
    m_vpDisplay.clear();

    for (int i=0;i<y;i++)
    {
        for (int j=0;j<x;j++)
        {
            DisplayWidget* display = new DisplayWidget(this);
            m_vpDisplay.push_back(display);
            m_pLayout->addWidget(m_vpDisplay[j+i*x], i, j);
            m_pLayout->setSpacing(5);
        }
    }
}
