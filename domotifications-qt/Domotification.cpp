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
    connect(communication,
            SIGNAL(etatsNotifications(QVector<bool>, QVector<bool>, bool)),
            this,
            SLOT(gererNotifications(QVector<bool>, QVector<bool>, bool)));
}

/**
 * @brief Destructeur de la classe Domotification
 * @fn Domotification::~Domotification
 */
Domotification::~Domotification()
{
    enregistrerModules();
    qDebug() << Q_FUNC_INFO;
}

// Slots

void Domotification::gererAcquittement(QString typeModule, int id)
{
    QString api         = typeModule;
    int     indexModule = recupererIndexModule(typeModule, id);
    qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id << "indexModule"
             << indexModule;

    if(modules[indexModule]->estActif() && modules[indexModule]->estNotifie())
    {
        QByteArray json = "{";
        json += "\"id\":" + QString::number(id) + QString(",") + "\"etat\":0" + "}";

        qDebug() << Q_FUNC_INFO << "api" << api << "json" << json;
        communication->envoyerRequetePost(api, json);
        modules[indexModule]->setNotifie(false);
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
 * @brief Domotification::recupererIndexModule
 * @param typeModule
 * @param id
 * @return int
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
 * @return bool
 */
bool Domotification::getActivationModule(QString typeModule, int id)
{
    for(int i = 0; i < modules.size(); ++i)
    {
        if(modules[i]->getType() == Module::getType(typeModule) && modules[i]->getId() == id)
        {
            qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id << "estActif"
                     << modules[i]->estActif();
            return modules[i]->estActif();
        }
    }
    return false;
}

/**
 * @brief Domotification::getNotificationModule
 * @param typeModule
 * @param id
 * @return bool
 */
bool Domotification::getNotificationModule(QString typeModule, int id)
{
    for(int i = 0; i < modules.size(); ++i)
    {
        if(modules[i]->getType() == Module::getType(typeModule) && modules[i]->getId() == id)
        {
            qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id << "estNotifie"
                     << modules[i]->estNotifie();
            return modules[i]->estNotifie();
        }
    }
    return false;
}

/**
 * @fn Domotification::gererNotifications
 * @brief Gère les états des notifications
 * @param machines
 * @param poubelles
 * @param boite
 */
void Domotification::gererNotifications(QVector<bool> etatsmachines,
                                        QVector<bool> etatspoubelles,
                                        bool          etatboite)
{
    qDebug() << Q_FUNC_INFO << "etatsmachines" << etatsmachines << "poubelles" << etatspoubelles
             << "etatboite" << etatboite;
    for(auto i = 0; i < etatspoubelles.size(); i++)
    {
        if(etatspoubelles[i])
        {
            switch(i)
            {
                case 0:
                    getPoubelles()[0]->setNotifie(true);
                    notifier(NOTIFICATION_POUBELLE_BLEUE);
                    break;
                case 1:
                    getPoubelles()[1]->setNotifie(true);
                    notifier(NOTIFICATION_POUBELLE_VERTE);
                    break;
                case 2:
                    getPoubelles()[2]->setNotifie(true);
                    notifier(NOTIFICATION_POUBELLE_JAUNE);
                    break;
                case 3:
                    getPoubelles()[3]->setNotifie(true);
                    notifier(NOTIFICATION_POUBELLE_ROUGE);
                    break;
                case 4:
                    getPoubelles()[4]->setNotifie(true);
                    notifier(NOTIFICATION_POUBELLE_GRISE);
                    break;
                default:
                    break;
            }
        }
    }
    for(auto i = 0; i < etatsmachines.size(); i++)
    {
        if(etatsmachines[i])
        {
            getMachines()[i]->setNotifie(true);
            notifier(NOTIFICATION_MACHINE);
            qDebug() << Q_FUNC_INFO << "etatNotificationMachines" << getMachines()[i]->estNotifie();
            getNotificationModule("machine", i);
        }
    }
    if(etatboite)
    {
        getBoite()->setNotifie(true);
        notifier(NOTIFICATION_BOITE);
    }
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
                     << modules[i]->getId() << "actif" << modules[i]->estActif();
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
                     << modules[i]->getId() << "actif" << modules[i]->estActif();
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
            qDebug() << Q_FUNC_INFO << "module" << modules[i]->getNom() << "id"
                     << modules[i]->getId() << "actif" << modules[i]->estActif();
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
    QSettings parametres(CONFIGURATION_APPLICATION, QSettings::IniFormat);
    QUrl      urlStation = parametres.value("Domotifications/station").toUrl();
    communication->setUrlStation(urlStation);
    int nombrePoubelles = parametres.value("Poubelles/nb").toInt();
    int nombreMachines  = parametres.value("Machines/nb").toInt();
    int nombreBoite     = parametres.value("BoiteAuxLettres/nb").toInt();
    qDebug() << Q_FUNC_INFO << "nombrePoubelles" << nombrePoubelles << "nombreMachines"
             << nombreMachines << "nombreBoite" << nombreBoite << "urlStation" << urlStation;
    /**
     * @todo Supprimer la clé "actif" et assurer la récupération de l'état via la station
     */
    for(auto i = 0; i < nombrePoubelles; i++)
    {
        QString sectionName = QString("Poubelle%1").arg(i);
        QString nom         = parametres.value(sectionName + "/nom").toString();
        bool    actif       = parametres.value(sectionName + "/actif").toBool();
        modules.push_back(new Module(nom, Module::TypeModule::Poubelle, i, actif, this));
    }

    for(auto i = 0; i < nombreMachines; i++)
    {
        QString sectionName = QString("Machine%1").arg(i);
        QString nom         = parametres.value(sectionName + "/nom").toString();
        bool    actif       = parametres.value(sectionName + "/actif").toBool();
        modules.push_back(new Module(nom, Module::TypeModule::Machine, i, actif, this));
    }

    for(auto i = 0; i < nombreBoite; i++)
    {
        QString sectionName = QString("BoiteAuxLettres%1").arg(i);
        QString nom         = parametres.value(sectionName + "/nom").toString();
        bool    actif       = parametres.value(sectionName + "/actif").toBool();
        modules.push_back(new Module(nom, Module::TypeModule::BoiteAuxLettres, i, actif, this));
    }

#ifdef SIMULATION_MODULES
    // Pour les tests : 6 modules
    // 2 machines (0..6)
    modules.push_back(new Module("machine", Module::TypeModule::Machine, 0, this));
    modules.push_back(new Module("machine", Module::TypeModule::Machine, 1, this));
    // 3 poubelles (0..5)
    modules.push_back(new Module("poubelle", Module::TypeModule::Poubelle, 0, this));
    modules.push_back(new Module("poubelle", Module::TypeModule::Poubelle, 1, this));
    modules.push_back(new Module("poubelle", Module::TypeModule::Poubelle, 2, this));
    // 1 boite (0..1)
    modules.push_back(new Module("boite", Module::TypeModule::BoiteAuxLettres, 0, this));

    // Pour les tests : simule des états
    // une machine
    modules[0]->setActif(true);
    modules[0]->setNotifie(true);
    modules[1]->setActif(false);
    // une poubelle
    modules[3]->setActif(false);
    modules[4]->setActif(true);
    modules[4]->setNotifie(true);
    // la boite aux lettres
    modules[5]->setActif(true);
    modules[5]->setNotifie(true);

#endif
    qDebug() << Q_FUNC_INFO << "modules" << modules;
}

/**
 * @brief Enregistre dans le fichier de configuration les modules gérés
 * @fn Domotification::enregistrerModules
 */
void Domotification::enregistrerModules()
{
    /**
     * @todo Supprimer la clé "actif" si la récupération de l'état via la station a été réalisée
     */
    QSettings parametres(CONFIGURATION_APPLICATION, QSettings::IniFormat);
    qDebug() << Q_FUNC_INFO << "CONFIGURATION_APPLICATION" << CONFIGURATION_APPLICATION;
    QVector<Module*> poubelles = getPoubelles();
    parametres.setValue(QString("Poubelles") + "/nb", poubelles.size());
    for(auto i = 0; i < poubelles.size(); i++)
    {
        QString nomSection = QString("Poubelle%1").arg(i);
        parametres.setValue(nomSection + "/nom", poubelles[i]->getNom());
        parametres.setValue(nomSection + "/actif", poubelles[i]->estActif());
        qDebug() << Q_FUNC_INFO << "nomSection" << nomSection << "nom" << poubelles[i]->getNom()
                 << "actif" << poubelles[i]->estActif();
    }

    QVector<Module*> machines = getMachines();
    parametres.setValue(QString("Machines") + "/nb", machines.size());
    for(auto i = 0; i < machines.size(); i++)
    {
        QString nomSection = QString("Machine%1").arg(i);
        parametres.setValue(nomSection + "/nom", machines[i]->getNom());
        parametres.setValue(nomSection + "/actif", machines[i]->estActif());
        qDebug() << Q_FUNC_INFO << "nomSection" << nomSection << "nom" << machines[i]->getNom()
                 << "actif" << machines[i]->estActif();
    }

    Module* boite = getBoite();
    if(boite == nullptr)
        parametres.setValue(QString("BoiteAuxLettres") + "/nb", 0);
    else
    {
        parametres.setValue(QString("BoiteAuxLettres") + "/nb", 1);
        QString nomSection = QString("BoiteAuxLettres") + "0";
        parametres.setValue(nomSection + "/nom", boite->getNom());
        parametres.setValue(nomSection + "/actif", boite->estActif());
        qDebug() << Q_FUNC_INFO << "nomSection" << nomSection << "nom" << boite->getNom() << "actif"
                 << boite->estActif();
    }

    parametres.setValue(QString("Domotifications") + "/station",
                        communication->getUrlStation().toString());
}

void Domotification::initialiserRecuperationNotifications()
{
    QTimer* minuteurRecuperationNotifications = new QTimer(this);

    connect(minuteurRecuperationNotifications,
            SIGNAL(timeout()),
            communication,
            SLOT(recupererNotifications()));

    minuteurRecuperationNotifications->start(PERIODE_RECUPERATION_NOTIFICATIONS);
}
