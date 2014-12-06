#include "TextOverlayWidget.h"


TextOverlayWidget::TextOverlayWidget(QWidget *parent)
    : QWidget(parent)
    , m_iFontSize(0)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}


TextOverlayWidget::~TextOverlayWidget()
{
}


void TextOverlayWidget::SetText(std::string text)
{
    m_sText = text;
}


void TextOverlayWidget::SetFontSize(int size)
{
    m_iFontSize = size;
}


void TextOverlayWidget::SetPenColor(QColor color)
{
    m_penColor = color;
}


void TextOverlayWidget::SetOrigin(int x, int y)
{
    m_iOriginX = x;
    m_iOriginY = y;
}


void TextOverlayWidget::SetWidth(int width)
{
    m_iWidth = width;
}


void TextOverlayWidget::SetHeight(int height)
{
    m_iHeight = height;
}


void TextOverlayWidget::SetAlignment(Qt::Alignment align)
{
    m_align = align;
}


void TextOverlayWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.save();
    QFont font("Helvetica");
    font.setPointSize(m_iFontSize);
    p.setFont(font);
    p.setPen(m_penColor);
    p.drawText(m_iOriginX, m_iOriginY, m_iWidth, m_iHeight,
               m_align, QString(m_sText.c_str()));
//    p.drawText(0, 10, 200, 100,
//               Qt::AlignLeft|Qt::AlignTop, QString(m_sText.c_str()));
    p.restore();
}
