#include "ImageWindowingDock.h"


ImageWindowDock::ImageWindowDock()
{
    setWindowTitle("Level-Window");
    m_DockContents = new QWidget;
    m_layoutWidget = new QWidget(m_DockContents);
    m_layoutWidget->setGeometry(QRect(20, 30, 241, 56));
    
    m_labelWC = new QLabel(m_layoutWidget);
    m_labelWW = new QLabel(m_layoutWidget);
    m_labelWC->setText("WC");
    m_labelWW->setText("WW");
    m_sliderWC = new QSlider(m_layoutWidget);
    m_sliderWW = new QSlider(m_layoutWidget);
    m_sliderWC->setOrientation(Qt::Horizontal);
    m_sliderWW->setOrientation(Qt::Horizontal);
    m_spinBoxWC = new QSpinBox(m_layoutWidget);
    m_spinBoxWW = new QSpinBox(m_layoutWidget);
    
    m_pushButtonReset = new QPushButton(m_DockContents);
    m_pushButtonReset->setGeometry(QRect(50, 3, 41, 23));
    m_pushButtonReset->setText("Reset");

    m_layout = new QGridLayout(m_layoutWidget);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_labelWC, 0, 0, 1, 1);
    m_layout->addWidget(m_labelWW, 1, 0, 1, 1);
    m_layout->addWidget(m_spinBoxWC, 0, 2, 1, 1);
    m_layout->addWidget(m_spinBoxWW, 1, 2, 1, 1);
    m_layout->addWidget(m_sliderWC, 0, 1, 1, 1);
    m_layout->addWidget(m_sliderWW, 1, 1, 1, 1);
        
    setWidget(m_DockContents);
    
    setMinimumSize(QSize(280, 160));
    setStyleSheet(QStringLiteral("QDockWidget::title {background: rgb(181, 195, 255)}"));

    connect(m_spinBoxWC, SIGNAL(valueChanged(int)), m_sliderWC, SLOT(setValue(int)));
    connect(m_sliderWC, SIGNAL(valueChanged(int)), m_spinBoxWC, SLOT(setValue(int)));
    connect(m_spinBoxWW, SIGNAL(valueChanged(int)), m_sliderWW, SLOT(setValue(int)));
    connect(m_sliderWW, SIGNAL(valueChanged(int)), m_spinBoxWW, SLOT(setValue(int)));

    m_sliderWC->setDisabled(true);
    m_sliderWW->setDisabled(true);
    m_spinBoxWC->setDisabled(true);
    m_spinBoxWW->setDisabled(true);
    m_pushButtonReset->setDisabled(true);
}


ImageWindowDock::~ImageWindowDock()
{
    delete m_spinBoxWW;
    delete m_spinBoxWC;
    delete m_sliderWW;
    delete m_sliderWC;
    delete m_labelWW;
    delete m_labelWC;
    delete m_pushButtonReset;
    delete m_layout;
    delete m_layoutWidget;
    delete m_DockContents;
}


void ImageWindowDock::EnableWidgets()
{
    m_sliderWC->setDisabled(false);
    m_sliderWW->setDisabled(false);
    m_spinBoxWC->setDisabled(false);
    m_spinBoxWW->setDisabled(false);
    m_pushButtonReset->setDisabled(false);
}


void ImageWindowDock::updateWindowLevel(int x, int y)
{
    m_spinBoxWC->setValue(m_spinBoxWC->value()-x);
    m_spinBoxWW->setValue(m_spinBoxWW->value()-y);
}


QSlider* ImageWindowDock::GetSliderWC()
{
    return m_sliderWC;
}


QSlider* ImageWindowDock::GetSliderWW()
{
    return m_sliderWW;
}


QSpinBox* ImageWindowDock::GetSpinBoxWC()
{
    return m_spinBoxWC;
}


QSpinBox* ImageWindowDock::GetSpinBoxWW()
{
    return m_spinBoxWW;
}


QPushButton* ImageWindowDock::GetResetButton()
{
    return m_pushButtonReset;
}
