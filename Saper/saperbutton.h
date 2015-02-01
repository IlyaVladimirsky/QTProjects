#ifndef SAPERBUTTON_H
#define SAPERBUTTON_H

#include <QPushButton>
#include <QMouseEvent>


class SaperButton : public QPushButton
{
    Q_OBJECT
private:
    bool isFlagged;
    QString** fieldContents;
    int fieldRowsSize, fieldColsSize;
    QString buttonContents;
    int buttonPosX, buttonPosY;

    void cellAutoOpening(int x, int y);

protected:
    void mousePressEvent(QMouseEvent* e){
        if(e->button() == Qt::RightButton)
            emit rClicked();

        if(e->button() == Qt::LeftButton)
            emit lClicked();
    }

public:
    explicit SaperButton(QString** fieldContents, int rows, int cols, int x, int y, QString buttonContents = "", QPushButton *parent = 0);

    void showButtonContents();
    QString getContents(){ return buttonContents; }
    void setContents(QString s){ buttonContents = s; }

signals:
    void rClicked();
    void lClicked();
    void openNearestCell(int, int);
    void boom();
    void checkingForWin();

public slots:
    void changeLable();
    void demining();
};

#endif // SAPERBUTTON_H
