/**
 * @file Domotification.cpp
 *
 * @brief Définition de la classe Domotification
 * @author Mathieu MOYAERTS
 * @version 0.2
 */
#include "Domotification.h"
#include "Communication.h"
#include "IhmDomotifications.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe Domotification
 * @fn Domotification::Domotification
 * @param ihm
 */
Domotification::Domotification(IHMDomotifications* ihm) :
    QObject(ihm), communication(new Communication(this)), ihm(ihm),
    minuteurRecuperationNotifications(nullptr)
{
    qDebug() << Q_FUNC_INFO;
    chargerModules();
    initialiserRecuperationNotifications();
}

/**
 * @brief Destructeur de la classe Domotification
 * @fn Domotification::~Domotification
 */
Domotification::~Domotification()
{
    qDebug() << Q_FUNC_INFO;
}

// Slots

void Domotification::gererAcquittement(QString typeModule, int id)
{
    QString api         = typeModule;
    int     indexModule = recupererIndexModule(typeModule, id);
    qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id << "indexModule"
             << indexModule;

    if(modules[indexModule]->estActif())
    {
        QByteArray json = "{";
        json += "\"id\":" + QString::number(id) + QString(",") + "\"etat\":0" + "}";

        qDebug() << Q_FUNC_INFO << "api" << api << "json" << json;
        communication->envoyerRequetePost(api, json);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "le module n'est pas activé !";
    }
}

/**
 * @brief Gère l'activation d'un module
 * @fn Domotification::gererActivationModule
 * @param typeModule
 * @param id
 */
void Domotification::gererActivationModule(QString typeModule, int id)
{
    QString api         = "activation";
    int     indexModule = recupererIndexModule(typeModule, id);
    qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id << "indexModule"
             << indexModule;
    if(indexModule == NON_TROUVE)
        return;

    QByteArray json = "{";
    json += "\"module\":\"" + QString(typeModule) + QString("\"") + QString(",") +
            "\"id\":" + QString::number(id) + QString(",");
    if(modules[indexModule]->estActif())
    {
        json += "\"etat\":0";
    }
    else
    {
        json += "\"etat\":1";
    }
    json += "}";

    qDebug() << Q_FUNC_INFO << "api" << api << "json" << json;
    communication->envoyerRequetePost(api, json);

    modules[indexModule]->setActif(!modules[indexModule]->estActif());
}

// Méthodes

/**
 * @brief Domotification::estGere
 * @param typeModule
 * @param id
 * @return
 */
int Domotification::recupererIndexModule(QString typeModule, int id)
{
    for(int i = 0; i < modules.size(); ++i)
    {
        if(modules[i]->recupererType() == typeModule && modules[i]->getId() == id)
        {
            return i;
        }
    }
    return NON_TROUVE;
}

/**
 * @brief Domotification::getActivationModule
 * @param typeModule
 * @param id
 * @return
 */
bool Domotification::getActivationModule(QString typeModule, int id)
{
    for(int i = 0; i < modules.size(); ++i)
    {
        if(modules[i]->getNom() == typeModule && modules[i]->getId() == id)
        {
            qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id << "estActif"
                     << modules[i]->estActif();
            return modules[i]->estActif();
        }
    }
    return false;
}

/**
 * @brief Ajoute un module
 * @fn Domotification::ajouterModule
 * @param nomModule
 * @param type
 */
void Domotification::ajouterModule(QString nomModule, Module::TypeModule type)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule << "TypeModule" << type;
}

/**
 * @brief envoyer une notification
 * @fn Domotification::notifier
 * @param message
 */
void Domotification::notifier(QString message)
{
    qDebug() << Q_FUNC_INFO << "message" << message;
    emit nouvelleNotification(message);
}

/**
 * @brief Retourne le vecteur des modules machines
 * @fn Domotification::getMachines
 * @return
 */
QVector<Module*> Domotification::getMachines() const
{
    QVector<Module*> machines;
    for(auto i = 0; i < modules.size(); i++)
    {
        if(modules[i]->getType() == Module::Machine)
        {
            qDebug() << Q_FUNC_INFO << "module" << modules[i]->getNom() << "id"
                     << modules[i]->getId();
            machines.push_back(modules[i]);
        }
    }
    return machines;
}

/**
 * @brief Retourne le vecteur des modules poubelles
 * @fn Domotification::getPoubelles
 * @return
 */
QVector<Module*> Domotification::getPoubelles() const
{
    QVector<Module*> poubelles;
    for(auto i = 0; i < modules.size(); i++)
    {
        if(modules[i]->getType() == Module::Poubelle)
        {
            qDebug() << Q_FUNC_INFO << "module" << modules[i]->getNom() << "id"
                     << modules[i]->getId();
            poubelles.push_back(modules[i]);
        }
    }
    return poubelles;
}

/**
 * @brief Retourne le module boite
 * @fn Domotification::getBoite
 * @return
 */
Module* Domotification::getBoite() const
{
    for(auto i = 0; i < modules.size(); i++)
    {
        if(modules[i]->getType() == Module::BoiteAuxLettres)
        {
            return modules[i];
        }
    }
    return nullptr;
}

/**
 * @brief Charge à partir de la configuration et crée les modules à gérer
 * @fn Domotification::chargerModules
 */
void Domotification::chargerModules()
{
    /**
     * @todo Gérer un fichier de configuration INI pour les modules
     */
    // Pour les tests : 5 modules
    // 2 machines (0..6)
    modules.push_back(new Module("machine", Module::TypeModule::Machine, 0, this));
    modules.push_back(new Module("machine", Module::TypeModule::Machine, 1, this));
    // 2 poubelles (0..5)
    modules.push_back(new Module("poubelle", Module::TypeModule::Poubelle, 0, this));
    modules.push_back(new Module("poubelle", Module::TypeModule::Poubelle, 1, this));
    modules.push_back(new Module("poubelle", Module::TypeModule::Poubelle, 2, this));
    // 1 boite (0..1)
    modules.push_back(new Module("boite", Module::TypeModule::BoiteAuxLettres, 0, this));
    qDebug() << Q_FUNC_INFO << "modules" << modules;
}

void Domotification::initialiserRecuperationNotifications()
{
    /**
     * @todo Instancier le miniteur
     */
    /**
     * @todo Connecter le signal timeout du minuteur au slot qui effectue la requête HTTP pour
     * récupérer les notifications
     */
    /**
     * @todo Démarrer le minuteur avec la PERIODE_RECUPERATION_NOTIFICATIONS
     */
}
