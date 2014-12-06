#ifndef TEXTOVERLAYWIDGET_H
#define TEXTOVERLAYWIDGET_H


#include <QWidget>
#include <QPainter>


class TextOverlayWidget : public QWidget
{
    Q_OBJECT

public:
    TextOverlayWidget(QWidget* parent = 0);
    virtual ~TextOverlayWidget();

    void SetText(std::string text);
    void SetFontSize(int size);
    void SetPenColor(QColor color);

    void SetOrigin(int x, int y);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetAlignment(Qt::Alignment align);

protected:
    void paintEvent(QPaintEvent *);

private:
    std::string m_sText;
    int m_iFontSize;
    QColor m_penColor;
    int m_iOriginX;
    int m_iOriginY;
    int m_iWidth;
    int m_iHeight;
    Qt::Alignment m_align;

};


#endif // TEXTOVERLAYWIDGET_H
