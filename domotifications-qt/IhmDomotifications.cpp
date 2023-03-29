#include "IhmDomotifications.h"
#include "ui_IhmDomotifications.h"

IHMDomotifications::IHMDomotifications(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMDomotifications)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
}

IHMDomotifications::~IHMDomotifications()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void IHMDomotifications::afficherModules()
{
}

void IHMDomotifications::gererEtatModule()
{
}

void IHMDomotifications::gererActivationModule()
{
}

void IHMDomotifications::visualiserNotification()
{
}

void IHMDomotifications::acquitterNotification()
{
}

void IHMDomotifications::parametrer()
{
}

void IHMDomotifications::afficherModules()
{
}

void IHMDomotifications::gererEtatModule()
{
}

void IHMDomotifications::gererActivationModule()
{
}

void IHMDomotifications::isualiserNotification()
{
}

void IHMDomotifications::acquitterNotification()
{
}

void IHMDomotifications::parametrer()
{
}
