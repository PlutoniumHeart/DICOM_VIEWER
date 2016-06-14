#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H


#include <QWidget>
#include <QGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>

#include "DisplayWidget.h"


class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(QWidget* parent);
    virtual ~CanvasWidget();

    int GetNumDisplays();
    int GetVerticalNum();
    int GetHorizontalNum();
    double GetSizeFactor();
    void SetSizeFactor(double factor);
    void Resize(QSize size);
    void Resize(int width, int height);
    DisplayWidget* GetDisplayWidget(int i);
    void SetupAnnotations(std::string UpperLeft, std::string UpperRight,
                          std::string LowerLeft, std::string LowerRight);

public slots:
    void Animate();
    void Rearrange(int x, int y);

private:
    QGridLayout* m_pLayout;
    std::vector<DisplayWidget*> m_vpDisplay;

    int m_iElapsed;
    int m_iX;
    int m_iY;
    double m_dSizeFactor;

};


#endif // CANVASWIDGET_H
