#include "speechdialog.h"
#include "ui_speechdialog.h"

SpeechDialog::SpeechDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpeechDialog)
{
    ui->setupUi(this);
}

SpeechDialog::~SpeechDialog()
{
    delete ui;
}
