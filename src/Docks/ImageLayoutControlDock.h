#ifndef IMAGELAYOUTCONTROLDOCK_H
#define IMAGELAYOUTCONTROLDOCK_H


#include <iostream>
#include <QDockWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>


class ImageLayoutControlDock : public QDockWidget
{
    Q_OBJECT

public:
    ImageLayoutControlDock();
    virtual ~ImageLayoutControlDock();

    QSpinBox* GetSpinBoxVertical();
    QSpinBox* GetSpinBoxHorizontal();
    QPushButton* GetSetLayoutButton();

public slots:
    void SetVertical(int x);
    void SetHorizontal(int y);
    void EmitNewLayout();

signals:
    void NewLayout(int x, int y);

private:
    QWidget* m_pDockContents;
    QWidget* m_pLayoutWidget;

    QLabel* m_pLabelVertical;
    QLabel* m_pLabelHorizontal;
    QGridLayout* m_pLayout;
    QSpinBox* m_pSpinBoxVertical;
    QSpinBox* m_pSpinBoxHorizontal;
    QPushButton* m_pPushButtonSet;

    int m_iVerticalNum;
    int m_iHorizontalNum;

};


#endif // IMAGELAYOUTCONTROLDOCK_H
