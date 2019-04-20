#include "speech.h"
#include "ui_speech.h"

Speech::Speech(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Speech)
{
    ui->setupUi(this);
}

Speech::~Speech()
{
    delete ui;
}
