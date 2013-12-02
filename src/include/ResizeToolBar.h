#ifndef RESIZETOOLBAR_H
#define RESIZETOOLBAR_H


#include <QToolBar>
#include <QIcon>
#include <QComboBox>


class ResizeToolBar : public QToolBar
{
    Q_OBJECT

public:
    ResizeToolBar();
    ~ResizeToolBar();

private:
    QComboBox* m_dropDownZoom;
};


#endif // RESIZETOOLBAR_H
