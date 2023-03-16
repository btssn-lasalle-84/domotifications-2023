#include "ihmdomotifications.h"
#include "ui_ihmdomotifications.h"

IHMDomotifications::IHMDomotifications(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IHMDomotifications)
{
    ui->setupUi(this);
}

IHMDomotifications::~IHMDomotifications()
{
    delete ui;
}

