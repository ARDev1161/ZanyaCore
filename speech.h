#ifndef SPEECH_H
#define SPEECH_H

#include <QDialog>

namespace Ui {
class Speech;
}

class Speech : public QDialog
{
    Q_OBJECT

public:
    explicit Speech(QWidget *parent = nullptr);
    ~Speech();

private:
    Ui::Speech *ui;
};

#endif // SPEECH_H
