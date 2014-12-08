#ifndef FILETOOLBAR_H
#define FILETOOLBAR_H


#include <QToolBar>
#include <QIcon>
#include <QAction>


class FileToolbar : public QToolBar
{
    Q_OBJECT

public:
    FileToolbar();
    ~FileToolbar();

    QAction* GetOpenDICOMAction();
    QAction* GetOpenDICOMSeriesAction();

private:
    QAction *m_pOpenDICOM;
    QAction *m_pOpenDICOMSeries;

};


#endif // FILETOOLBAR_H
