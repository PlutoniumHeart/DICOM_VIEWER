#include "ImageWindowingDock.h"


ImageWindowDock::ImageWindowDock()
{
    setWindowTitle("Level-Window");
    m_DockContents = new QWidget;
    m_LayoutWidget = new QWidget(m_DockContents);
    m_LayoutWidget->setGeometry(QRect(20, 30, 241, 56));
    
    m_LabelWC = new QLabel(m_LayoutWidget);
    m_LabelWW = new QLabel(m_LayoutWidget);
    m_LabelWC->setText("WC");
    m_LabelWW->setText("WW");
    m_SliderWC = new QSlider(m_LayoutWidget);
    m_SliderWW = new QSlider(m_LayoutWidget);
    m_SliderWC->setOrientation(Qt::Horizontal);
    m_SliderWW->setOrientation(Qt::Horizontal);
    m_SpinBoxWC = new QSpinBox(m_LayoutWidget);
    m_SpinBoxWW = new QSpinBox(m_LayoutWidget);
    
    m_PushButtonReset = new QPushButton(m_DockContents);
    m_PushButtonReset->setGeometry(QRect(50, 3, 41, 23));
    m_PushButtonReset->setText("Reset");

    m_Layout = new QGridLayout(m_LayoutWidget);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->addWidget(m_LabelWC, 0, 0, 1, 1);
    m_Layout->addWidget(m_LabelWW, 1, 0, 1, 1);
    m_Layout->addWidget(m_SpinBoxWC, 0, 2, 1, 1);
    m_Layout->addWidget(m_SpinBoxWW, 1, 2, 1, 1);
    m_Layout->addWidget(m_SliderWC, 0, 1, 1, 1);
    m_Layout->addWidget(m_SliderWW, 1, 1, 1, 1);
        
    setWidget(m_DockContents);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(QSize(280, 160));
    setStyleSheet(QStringLiteral("QDockWidget::title {background: rgb(181, 195, 255)}"));

    connect(m_SpinBoxWC, SIGNAL(valueChanged(int)), m_SliderWC, SLOT(setValue(int)));
    connect(m_SliderWC, SIGNAL(valueChanged(int)), m_SpinBoxWC, SLOT(setValue(int)));
    connect(m_SpinBoxWW, SIGNAL(valueChanged(int)), m_SliderWW, SLOT(setValue(int)));
    connect(m_SliderWW, SIGNAL(valueChanged(int)), m_SpinBoxWW, SLOT(setValue(int)));
    connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(SetFloatingProperty(bool)));

    SetWidgetsDisabled(true);
}


ImageWindowDock::~ImageWindowDock()
{
    delete m_SpinBoxWW;
    delete m_SpinBoxWC;
    delete m_SliderWW;
    delete m_SliderWC;
    delete m_LabelWW;
    delete m_LabelWC;
    delete m_PushButtonReset;
    delete m_Layout;
    delete m_LayoutWidget;
    delete m_DockContents;
}


void ImageWindowDock::SetWidgetsDisabled(bool disabled)
{
    m_SliderWC->setDisabled(disabled);
    m_SliderWW->setDisabled(disabled);
    m_SpinBoxWC->setDisabled(disabled);
    m_SpinBoxWW->setDisabled(disabled);
    m_PushButtonReset->setDisabled(disabled);
}


void ImageWindowDock::UpdateWindowLevel(float x, float y)
{
    int X = (int)(x*1000.0);
    int Y = (int)(y*1000.0);
    m_SpinBoxWC->setValue(m_SpinBoxWC->value()-X);
    m_SpinBoxWW->setValue(m_SpinBoxWW->value()-Y);
}


void ImageWindowDock::SetFloatingProperty(bool floating)
{
    if(floating)
        resize(280, 160);
}


QSlider* ImageWindowDock::GetSliderWC()
{
    return m_SliderWC;
}


QSlider* ImageWindowDock::GetSliderWW()
{
    return m_SliderWW;
}


QSpinBox* ImageWindowDock::GetSpinBoxWC()
{
    return m_SpinBoxWC;
}


QSpinBox* ImageWindowDock::GetSpinBoxWW()
{
    return m_SpinBoxWW;
}


QPushButton* ImageWindowDock::GetResetButton()
{
    return m_PushButtonReset;
}
