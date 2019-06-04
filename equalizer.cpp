#include "equalizer.h"
#include "ui_equalizer.h"

Equalizer::Equalizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Equalizer)
{
    ui->setupUi(this);
}

Equalizer::~Equalizer()
{
    delete ui;
}
