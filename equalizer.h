#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <QDialog>

namespace Ui {
class Equalizer;
}

class Equalizer : public QDialog
{
    Q_OBJECT

public:
    explicit Equalizer(QWidget *parent = nullptr);
    ~Equalizer();

private:
    Ui::Equalizer *ui;
};

#endif // EQUALIZER_H
