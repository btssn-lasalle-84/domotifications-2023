/**
 * @file Domotification.cpp
 *
 * @brief Définition de la classe Domotification
 * @author Mathieu MOYAERTS
 * @version 0.1
 */
#include "Domotification.h"
#include "Communication.h"
#include "IhmDomotifications.h"
#include <QDebug>

Domotification::Domotification(IHMDomotifications* ihm) :
    QObject(ihm), communication(new Communication(this)), ihm(ihm)
{
    qDebug() << Q_FUNC_INFO;
    /**
     * @todo Gérer un fichier de configuration INI pour les modules
     */
    // Pour les tests
    modules["Machine"] = new Module("Machine", Module::TypeModule::Machine, this);
    modules["BoiteAuxLettres"] =
      new Module("BoiteAuxLettres", Module::TypeModule::BoiteAuxLettres, this);
    modules["Poubelle"] = new Module("Poubelle", Module::TypeModule::Poubelle, this);
}

Domotification::~Domotification()
{
    qDebug() << Q_FUNC_INFO;
}

// Slots

void Domotification::gererActivationModule(QString nomModule)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule;
    if(modules.contains(nomModule))
    {
        modules[nomModule]->setActif(!modules[nomModule]->estActif());
        // Exemple
        QByteArray json = "{";
        json += "\"id\":" + QString::number(modules[nomModule]->getId()) + QString(",");
        if(modules[nomModule]->estActif())
            json += "\"etat\":true";
        else
            json += "\"etat\":false";
        json += "}";
        communication->envoyerRequetePost(Module::getType(modules[nomModule]->getType()), json);
    }
}

// Méthodes

bool Domotification::getActivationModule(QString nomModule)
{
    if(modules.contains(nomModule))
    {
        return modules[nomModule]->estActif();
    }
    return false;
}

void Domotification::gererNotification(QString nomModule)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule;
}

void Domotification::ajouterModule(QString nomModule, Module::TypeModule type)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule << "TypeModule" << type;
}

void Domotification::notifier(QString message)
{
    qDebug() << Q_FUNC_INFO << "message" << message;
    emit nouvelleNotification(message);
}
