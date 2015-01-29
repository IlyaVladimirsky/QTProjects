#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QPalette>
#include <QLabel>
#include "saperbutton.h"
//#include "fieldgridlayout.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    const static int SIZE = 4;
    QMap<QPair<int, int>, SaperButton*> buttonsField;
    //SaperButton*** buttonsField;

    QLabel* informationLabel;
    QGridLayout* gridLayout;
    QVBoxLayout* vboxLayout;

    QPushButton* buttonNewGame;

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void openAllCells();
    void closeAllCells();
public slots:
    void deminingCell(int, int);
    void explosion();
    void newGame();
    void checkingForWin();
};

#endif // WIDGET_H
