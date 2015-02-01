#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QPalette>
#include <QLabel>
#include <QTime>
#include "saperbutton.h"
//#include "fieldgridlayout.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    const static int SIZE = 6;
    const static int BOMBS = 6;
    QMap<QPair<int, int>, SaperButton*> buttonsField;
    QString**  fieldContext;

    QGridLayout* gridLayout;
    QVBoxLayout* vboxLayout;

    QLabel* informationLabel;
    QPushButton* buttonNewGame;    

    void fieldAutoFilling();
    void mining(int minesCount);
    int generateNumb(int to, int from = 0);
    void digitsAlloc();
    int countBombsAround(int x, int y);
    bool isBomb(int x, int y);

    void setButtonsContext();
    void fieldClearing();

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
