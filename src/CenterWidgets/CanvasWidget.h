#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H


#include <QWidget>
#include <QGridLayout>

#include "DisplayWidget.h"
#include "ImageHandler.h"


class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(ImageHandler* handler, QWidget* parent);
    virtual ~CanvasWidget();

    void Resize(int width, int height);
    void SetupAnnotations(std::string UpperLeft, std::string UpperRight,
                          std::string LowerLeft, std::string LowerRight);

public slots:
    void Animate();

private:
    std::vector<DisplayWidget*> m_vpDisplay;

    int m_iElapsed;

};


#endif // CANVASWIDGET_H
