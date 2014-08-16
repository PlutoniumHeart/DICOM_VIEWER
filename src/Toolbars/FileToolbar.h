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

private:
    QAction *openDICOM;

};


#endif // FILETOOLBAR_H
