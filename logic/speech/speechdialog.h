#ifndef SPEECHDIALOG_H
#define SPEECHDIALOG_H

#include <QDialog>

namespace Ui {
class SpeechDialog;
}

class SpeechDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpeechDialog(QWidget *parent = nullptr);
    ~SpeechDialog();

private:
    Ui::SpeechDialog *ui;
};

#endif // SPEECHDIALOG_H
