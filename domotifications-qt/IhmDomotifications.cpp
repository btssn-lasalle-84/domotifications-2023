/**
 * @file IhmDomotifications.cpp
 *
 * @brief Définition de la classe IhmDomotifications
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include "IhmDomotifications.h"
#include "ui_IhmDomotifications.h"

/**
 * @brief Constructeur de la classe IHMDomotifications
 * @fn IHMDomotifications::IHMDomotifications
 * @param parent nullptr pour la fenêtre comme fenêtre principale de l'application
 */
IHMDomotifications::IHMDomotifications(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMDomotifications)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    setWindowTitle(TITRE_APPLICATION);
    resize(qApp->desktop()->availableGeometry(this).width(),
           qApp->desktop()->availableGeometry(this).height());
    // showMaximized();
}

/**
 * @brief Destructeur de la classe IHMDomotifications
 *
 * @fn IHMDomotifications::~IHMDomotifications
 * @details Libère les ressources de l'application
 */
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
