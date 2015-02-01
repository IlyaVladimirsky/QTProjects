#include "saperbutton.h"

void SaperButton::cellAutoOpening(int x, int y){
    if(x < 0 || x >= fieldRowsSize) return;
    if(y < 0 || y >= fieldColsSize) return;

    emit openNearestCell(x, y);
}

void SaperButton::showButtonContents(){
    setText(buttonContents);
}

SaperButton::SaperButton(QString** fieldContents, int rows, int cols, int x, int y, QString buttonContents, QPushButton *parent) :
    QPushButton(parent),
    isFlagged(false),
    fieldContents(fieldContents),
    fieldRowsSize(rows),
    fieldColsSize(cols),
    buttonContents(buttonContents),
    buttonPosX(x),
    buttonPosY(y)
{
    setFixedSize(30, 30);
    setCheckable(true);
    connect(this, &SaperButton::rClicked, &SaperButton::changeLable);
    connect(this, &SaperButton::lClicked, &SaperButton::demining);
}

void SaperButton::changeLable(){
    if(!isChecked())
        if(isFlagged){
            setText("");
            isFlagged = false;
        }else{
            setText("!");
            isFlagged = true;
        }
}

void SaperButton::demining(){
    if(isChecked())
        return;

    if(text() == "!")
        return;

    setChecked(true);
    showButtonContents();

    if(fieldContents[buttonPosX][buttonPosY] == "*"){
        emit boom();
        return;
    }

    emit checkingForWin();

    if(text() != "")
        return;

    cellAutoOpening(buttonPosX,     buttonPosY + 1);
    cellAutoOpening(buttonPosX + 1, buttonPosY + 1);
    cellAutoOpening(buttonPosX + 1, buttonPosY);
    cellAutoOpening(buttonPosX + 1, buttonPosY - 1);
    cellAutoOpening(buttonPosX,     buttonPosY - 1);
    cellAutoOpening(buttonPosX - 1, buttonPosY - 1);
    cellAutoOpening(buttonPosX - 1, buttonPosY );
    cellAutoOpening(buttonPosX - 1, buttonPosY + 1);    
}
