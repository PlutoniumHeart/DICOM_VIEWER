#include "ImageLayoutControlDock.h"


ImageLayoutControlDock::ImageLayoutControlDock()
    : m_iVerticalNum(1)
    , m_iHorizontalNum(1)
{
    setWindowTitle("Display Layout Window");
    m_pDockContents = new QWidget;
    m_pLayoutWidget = new QWidget(m_pDockContents);
    m_pLayoutWidget->setGeometry(QRect(20, 30, 241, 56));

    m_pLabelVertical = new QLabel(m_pLayoutWidget);
    m_pLabelVertical->setText("Rows");
    m_pLabelHorizontal = new QLabel(m_pLayoutWidget);
    m_pLabelHorizontal->setText("Columns");
    m_pSpinBoxVertical = new QSpinBox(m_pLayoutWidget);
    m_pSpinBoxHorizontal = new QSpinBox(m_pLayoutWidget);

    m_pPushButtonSet = new QPushButton(m_pDockContents);
    m_pPushButtonSet->setGeometry(QRect(50, 3, 80, 23));
    m_pPushButtonSet->setText("Set Layout");

    m_pLayout = new QGridLayout(m_pLayoutWidget);
    m_pLayout->setContentsMargins(0, 0, 0, 0);
    m_pLayout->addWidget(m_pLabelVertical, 0, 0, 1, 1);
    m_pLayout->addWidget(m_pLabelHorizontal, 1, 0, 1, 1);
    m_pLayout->addWidget(m_pSpinBoxVertical, 0, 2, 1, 1);
    m_pLayout->addWidget(m_pSpinBoxHorizontal, 1, 2, 1, 1);

    setWidget(m_pDockContents);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setMinimumSize(QSize(280, 160));
    setStyleSheet(QStringLiteral("QDockWidget::title {background: rgb(181, 195, 255)}"));

    connect(m_pSpinBoxVertical, SIGNAL(valueChanged(int)), this, SLOT(SetVertical(int)));
    connect(m_pSpinBoxHorizontal, SIGNAL(valueChanged(int)), this, SLOT(SetHorizontal(int)));
    connect(m_pPushButtonSet, SIGNAL(clicked()), this, SLOT(EmitNewLayout()));
}


ImageLayoutControlDock::~ImageLayoutControlDock()
{
    delete m_pLayout;
    delete m_pPushButtonSet;
    delete m_pSpinBoxHorizontal;
    delete m_pSpinBoxVertical;
    delete m_pLayoutWidget;
    delete m_pDockContents;
}


void ImageLayoutControlDock::EmitNewLayout()
{
    emit NewLayout(m_iHorizontalNum, m_iVerticalNum);
}


QSpinBox* ImageLayoutControlDock::GetSpinBoxVertical()
{
    return m_pSpinBoxVertical;
}


QSpinBox* ImageLayoutControlDock::GetSpinBoxHorizontal()
{
    return m_pSpinBoxHorizontal;
}


QPushButton* ImageLayoutControlDock::GetSetLayoutButton()
{
    return m_pPushButtonSet;
}


void ImageLayoutControlDock::SetVertical(int i)
{
    m_iVerticalNum = i;
}


void ImageLayoutControlDock::SetHorizontal(int j)
{
    m_iHorizontalNum = j;
}
