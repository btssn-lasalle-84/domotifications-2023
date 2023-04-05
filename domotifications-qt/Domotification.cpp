/**
 * @file Domotification.cpp
 *
 * @brief Définition de la classe Domotification
 * @author Mathieu MOYAERTS
 * @version 0.1
 */
#include "Domotification.h"
#include <QDebug>

Domotification::Domotification(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

Domotification::~Domotification()
{
    qDebug() << Q_FUNC_INFO;
}

void Domotification::gererActivationModule(QString nomModule, bool etatActivation)
{
}

void Domotification::gererNotification(QString nomModule, bool etatActivation)
{
}

void Domotification::ajouterModule(QString nomModule, Module::TypeModule type)
{
}
