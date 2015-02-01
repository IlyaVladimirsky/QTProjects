#include "widget.h"

void Widget::fieldAutoFilling(){
    mining(BOMBS);
    digitsAlloc();
}

void Widget::mining(int minesCount){
    int x;
    int y;
    qsrand(QDateTime::currentDateTime().toTime_t() );


    for(int i = 0; i < minesCount; ++i){
        do{
            x = generateNumb(SIZE);
            y = generateNumb(SIZE);
        }while (fieldContext[x][y] == "*");
        fieldContext[x][y] = "*";
    }
}

int Widget::generateNumb(int to, int from){

   return (qrand() % to - from);
}

void Widget::digitsAlloc(){
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j){
            if(fieldContext[i][j] != "*")
                fieldContext[i][j] = QString::number(countBombsAround(i, j));
            if(fieldContext[i][j] == "0")
                fieldContext[i][j] = "";
        }
}

int Widget::countBombsAround(int x, int y){
    int count = 0;

    if(isBomb(    x, y + 1)) ++count;
    if(isBomb(x + 1, y + 1)) ++count;
    if(isBomb(x + 1,     y)) ++count;
    if(isBomb(x + 1, y - 1)) ++count;
    if(isBomb(    x, y - 1)) ++count;
    if(isBomb(x - 1, y - 1)) ++count;
    if(isBomb(x - 1,     y)) ++count;
    if(isBomb(x - 1, y + 1)) ++count;

    return count;
}

bool Widget::isBomb(int x, int y){
    if(x < 0 || x >= SIZE) return false;
    if(y < 0 || y >= SIZE) return false;

    if(fieldContext[x][y] == "*")
        return true;

    return false;
}

void Widget::setButtonsContext(){
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j){
            SaperButton* curButton = buttonsField.value(QPair<int, int>(i, j));
            curButton->setContents(fieldContext[i][j]);
        }
}

void Widget::fieldClearing(){
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            fieldContext[i][j] = "";
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    gridLayout = new QGridLayout;
    vboxLayout = new QVBoxLayout;
    informationLabel = new QLabel;
    buttonNewGame = new QPushButton("New Game");

    gridLayout->setSpacing(0);

    setFixedSize(170, 215);

    fieldContext = new QString*[SIZE];
    for(int i = 0; i < SIZE; ++i)
        fieldContext[i] = new QString[SIZE];

//    fieldContext[0][0] = "*";
//    fieldContext[0][1] = "1";
//    fieldContext[0][2] = "";
//    fieldContext[0][3] = "";
//    fieldContext[1][0] = "1";
//    fieldContext[1][1] = "1";
//    fieldContext[1][2] = "";
//    fieldContext[1][3] = "";
//    fieldContext[2][0] = "";
//    fieldContext[2][1] = "1";
//    fieldContext[2][2] = "2";
//    fieldContext[2][3] = "2";
//    fieldContext[3][0] = "";
//    fieldContext[3][1] = "1";
//    fieldContext[3][2] = "*";
//    fieldContext[3][3] = "*";

    fieldAutoFilling();

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
    repaint();

    fieldClearing();
    fieldAutoFilling();
    setButtonsContext();
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
