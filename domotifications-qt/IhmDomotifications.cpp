#include "IhmDomotifications.h"
#include "ui_IhmDomotifications.h"

IHMDomotifications::IHMDomotifications(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMDomotifications)
{
    ui->setupUi(this);
}

IHMDomotifications::~IHMDomotifications()
{
    delete ui;
}