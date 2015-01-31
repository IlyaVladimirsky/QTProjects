#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    gridLayout = new QGridLayout;
    vboxLayout = new QVBoxLayout;
    informationLabel = new QLabel;
    buttonNewGame = new QPushButton("New Game");

    gridLayout->setSpacing(0);

    setFixedSize(150, 190);

    fieldContext = new QString*[SIZE];
    for(int i = 0; i < SIZE; ++i)
        fieldContext[i] = new QString[SIZE];

    fieldContext[0][0] = "*";
    fieldContext[0][1] = "1";
    fieldContext[0][2] = "";
    fieldContext[0][3] = "";
    fieldContext[1][0] = "1";
    fieldContext[1][1] = "1";
    fieldContext[1][2] = "";
    fieldContext[1][3] = "";
    fieldContext[2][0] = "";
    fieldContext[2][1] = "1";
    fieldContext[2][2] = "2";
    fieldContext[2][3] = "2";
    fieldContext[3][0] = "";
    fieldContext[3][1] = "1";
    fieldContext[3][2] = "*";
    fieldContext[3][3] = "*";

    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j){
            SaperButton* curButton = new SaperButton(fieldContext, SIZE, SIZE, i, j, fieldContext[i][j]);
            buttonsField.insert(QPair<int, int>(i, j), curButton);
            gridLayout->addWidget(curButton, i, j);
            connect(curButton, &SaperButton::openNearestCell, this, &Widget::deminingCell);
            connect(curButton, &SaperButton::boom, this, &Widget::explosion);
            connect(curButton, &SaperButton::checkingForWin, this, &Widget::checkingForWin);
        }

    connect(buttonNewGame, &QPushButton::clicked, this, &Widget::newGame);

    vboxLayout->addLayout(gridLayout);
    vboxLayout->addWidget(informationLabel, 1, Qt::AlignHCenter);
    vboxLayout->addWidget(buttonNewGame);

    setLayout(vboxLayout);    
}
void Widget::openAllCells(){
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j){
            SaperButton* curButton = buttonsField.value(QPair<int, int>(i, j));
            curButton->setChecked(true);
            curButton->showButtonContents();
        }
}
void Widget::closeAllCells(){
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j){
            SaperButton* curButton = buttonsField.value(QPair<int, int>(i, j));
            curButton->setChecked(false);
            curButton->setText("");
            repaint();
        }
}

Widget::~Widget(){
    foreach (SaperButton* button, buttonsField)
        delete button;

    for(int i = 0; i < SIZE; ++i)
        delete fieldContext[i];
    delete fieldContext;

    delete vboxLayout;
}

void Widget::deminingCell(int x, int y){
    buttonsField.value(QPair<int, int>(x, y))->demining();
}

void Widget::explosion(){
    openAllCells();
    informationLabel->setText("Game over!");
}

void Widget::newGame(){
    informationLabel->setText("");
    closeAllCells();
}

void Widget::checkingForWin(){
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j){
            SaperButton* curButton = buttonsField.value(QPair<int, int>(i, j));
            if((!curButton->isChecked() && curButton->getContents() != "*"))
                return;
        }
    openAllCells();
    informationLabel->setText("You win!");
    repaint();
}
