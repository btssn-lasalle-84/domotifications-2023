/**
 * @file Domotification.cpp
 *
 * @brief Définition de la classe Domotification
 * @author Mathieu MOYAERTS
 * @version 0.1
 */
#include "Domotification.h"
#include <QDebug>

Domotification::Domotification(QObject* parent) : QObject(parent), reseau(new Communication), ihm(new IHMDomotifications)
{
    qDebug() << Q_FUNC_INFO;
}

Domotification::~Domotification()
{
    delete reseau;
    delete ihm;
    qDebug() << Q_FUNC_INFO;
}

void Domotification::gererActivationModule()
{
    qDebug() << Q_FUNC_INFO;
    QObject *adresseObjetSignal = sender();
    if(adresseObjetSignal == ihm->getBoutonGererActivationPoubelle())
    {
        reseau->envoyerRequetePostBoiteAuxLettres();
    }

}
void Domotification::gererNotification(QString nomModule, bool etatActivation)
{
}

void Domotification::ajouterModule(QString nomModule, Module::TypeModule type)
{
}

void Domotification::notifier(QString message)
{
    emit nouvelleNotification(message);
}
