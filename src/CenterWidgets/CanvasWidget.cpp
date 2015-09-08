#include "CanvasWidget.h"


CanvasWidget::CanvasWidget(ImageHandler* handler, QWidget* parent)
    : QWidget(parent)
    , m_iElapsed(0)
{
    QGridLayout* layout = new QGridLayout;
    for (int i=0;i<2;i++)
    {
        DisplayWidget* display = new DisplayWidget(handler, this);
        m_vpDisplay.push_back(display);
        layout->addWidget(m_vpDisplay[i], 0, i);
    }
    setLayout(layout);
}


CanvasWidget::~CanvasWidget()
{
}


void CanvasWidget::Resize(QSize size)
{
    resize(size);

    for (int i=0;i<m_vpDisplay.size();i++)
    {
        m_vpDisplay[i]->resize(size);
    }
}


void CanvasWidget::Resize(int width, int height)
{
    resize(width*m_vpDisplay.size(), height);

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
