/**
 * @file IhmDomotifications.cpp
 *
 * @brief Définition de la classe IhmDomotifications
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "IhmDomotifications.h"
#include "ui_IhmDomotifications.h"

#include "Constantes.h"
#include "Domotification.h"
#include "Module.h"

/**
 * @brief Constructeur de la classe IHMDomotifications
 * @fn IHMDomotifications::IHMDomotifications
 * @param parent nullptr pour la fenêtre comme fenêtre principale de l'application
 */
IHMDomotifications::IHMDomotifications(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMDomotifications), domotification(new Domotification(this))
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    initialiserBarreDeTaches();
    initialiserGUI();
    initialiserSignauxSlots();
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
    delete imageBoutonActivation;
    delete imageBoutonDesactivation;
    delete imageBoutonAcquittement;
    // delete imageLogoBTS;
    // delete imageLogoParametre;
    for(int i = 0; i < poubelles.size(); i++)
    {
        delete imagesLogoPoubelle[i];
    }
    delete imageLogoMachine;
    delete imageLogoBoiteAuxLettres;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Slot pour la visualisation des notifications
 *
 * @fn IHMDomotifications::visualiserNotification
 * @details Affiche une notification système avec un type de message et un message prédéfinis
 *
 * @param message de la notification
 * @param type pour les différents types de notifications en fonction de la gravité
 */
void IHMDomotifications::visualiserNotification(QString message)
{
    qDebug() << Q_FUNC_INFO << "message" << message;

    QSystemTrayIcon::MessageIcon messageIcon =
      QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Critical);

    iconeSysteme->showMessage(TITRE_APPLICATION, message, messageIcon);
    qDebug() << Q_FUNC_INFO << "TITRE_APPLICATION" << TITRE_APPLICATION << "message" << message
             << "messageIcon" << messageIcon;
}

/**
 * @brief Methode pour l'acquittement des notifications
 *
 * @fn IHMDomotifications::acquitterNotification
 * @details Acquitte les notifications envoyés par le système de notification.
 */
void IHMDomotifications::acquitterNotification()
{
    /**
     * @fixme Vérifier le moyen d'acquitter la notification
     */
    qDebug() << Q_FUNC_INFO;
}

#ifdef TEST_NOTIFICATIONS
void IHMDomotifications::testerNotification()
{
    domotification->notifier("La machine est finie !");
}
#endif

/**
 * @brief Initialise les widgets
 *
 * @fn IHMDomotifications::initialiserWidgets
 * @details Initialise les widgets de l'IHM.
 */
void IHMDomotifications::initialiserWidgets()
{
    widgetPrincipal       = new QWidget(this);
    layoutPrincipal       = new QVBoxLayout;
    layoutLogos           = new QVBoxLayout;
    layoutPoubelles       = new QHBoxLayout;
    layoutMachines        = new QHBoxLayout;
    layoutBoiteAuxLettres = new QHBoxLayout;

    poubelles = domotification->getPoubelles();
    machines  = domotification->getMachines();
    boite     = domotification->getBoite();

    for(auto i = 0; i < poubelles.size(); i++)
    {
        layoutsPoubelle.push_back(new QHBoxLayout);
    }

    for(auto i = 0; i < machines.size(); i++)
    {
        layoutsMachine.push_back(new QHBoxLayout);
    }

    layoutBoiteAuxLettres = new QHBoxLayout;

    for(auto i = 0; i < poubelles.size(); i++)
    {
        layoutsBoutonsPoubelle.push_back(new QVBoxLayout);
    }

    for(auto i = 0; i < machines.size(); i++)
    {
        layoutsBoutonsMachine.push_back(new QVBoxLayout);
    }

    layoutBoutonsBoiteAuxLettres = new QVBoxLayout;

    for(auto i = 0; i < poubelles.size(); i++)
    {
        boutonsActivationDesactivationPoubelle.push_back(new QPushButton(this));
        boutonsAcquittementPoubelle.push_back(new QPushButton(this));
    }

    for(auto i = 0; i < machines.size(); i++)
    {
        boutonsActivationDesactivationMachine.push_back(new QPushButton);
        boutonsAcquittementMachine.push_back(new QPushButton);
    }

    boutonActivationDesactivationBoiteAuxLettres = new QPushButton(this);
    boutonAcquittementBoiteAuxLettres            = new QPushButton(this);

    // boutonParametres = new QPushButton(this);

    for(auto i = 0; i < poubelles.size(); i++)
    {
        qDebug() << Q_FUNC_INFO << "module" << poubelles[i]->getNom() << "id"
                 << poubelles[i]->getId() << "type" << poubelles[i]->getType()
                 << poubelles[i]->recupererType();
        boutonsActivationDesactivationPoubelle[i]->setObjectName(poubelles[i]->recupererType());
        boutonsAcquittementPoubelle[i]->setObjectName(poubelles[i]->recupererType());
    }

    for(auto i = 0; i < machines.size(); i++)
    {
        qDebug() << Q_FUNC_INFO << "module" << machines[i]->getNom() << "id" << machines[i]->getId()
                 << "type" << machines[i]->getType() << machines[i]->recupererType();
        boutonsActivationDesactivationMachine[i]->setObjectName(machines[i]->recupererType());
        boutonsAcquittementMachine[i]->setObjectName(machines[i]->recupererType());
    }

    qDebug() << Q_FUNC_INFO << "module" << boite->getNom() << "type" << boite->getType()
             << boite->recupererType();
    boutonActivationDesactivationBoiteAuxLettres->setObjectName(boite->recupererType());
    boutonAcquittementBoiteAuxLettres->setObjectName(boite->recupererType());

    //----------------

    imageBoutonActivation    = new QPixmap(CHEMIN_BOUTON_ACTIVATION);
    imageBoutonDesactivation = new QPixmap(CHEMIN_BOUTON_DESACTIVATION);
    imageBoutonAcquittement  = new QPixmap(CHEMIN_BOUTON_ACQUITTEMENT);
    // imageLogoBTS             = new QPixmap(CHEMIN_LOGO_BTS_SN);
    // imageLogoParametre = new QPixmap(CHEMIN_LOGO_PARAMETRE);
    for(auto i = 0; i < poubelles.size(); i++)
    {
        imagesLogoPoubelle.push_back(
          new QPixmap(CHEMIN_LOGO_POUBELLE + QString::number(i + 1) + ".png"));
    }
    imageLogoMachine         = new QPixmap(CHEMIN_LOGO_MACHINE);
    imageLogoBoiteAuxLettres = new QPixmap(CHEMIN_LOGO_BOITE_AUX_LETTRES);

    // logoBTS             = new QLabel(this);
    logoBoiteAuxLettres = new QLabel(this);
    for(auto i = 0; i < machines.size(); i++)
    {
        logosMachine.push_back(new QLabel(this));
    }
    for(auto i = 0; i < poubelles.size(); i++)
    {
        logosPoubelle.push_back(new QLabel(this));
    }

    iconeActivation    = new QIcon(*imageBoutonActivation);
    iconeDesactivation = new QIcon(*imageBoutonDesactivation);
    iconeAcquittement  = new QIcon(*imageBoutonAcquittement);
}

/**
 * @brief Affichage des boutons d'activation desactivation
 * @fn IHMDomotifications::afficherBoutonsActivationDesactivation
 * @details Affichage des boutons d'activation et de desactivation des différents modules
 */
void IHMDomotifications::afficherBoutonsActivationDesactivation()
{
    for(auto i = 0; i < machines.size(); i++)
    {
        boutonsActivationDesactivationMachine[i]->setIcon(*iconeActivation);
        afficherEtatBoutonActivationDesactivation(boutonsActivationDesactivationMachine[i], i);
        /*boutonsActivationDesactivationMachine[i]->setIconSize(
          imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
        boutonsActivationDesactivationMachine[i]->setFixedSize(
          imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());*/
    }

    for(auto i = 0; i < poubelles.size(); i++)
    {
        boutonsActivationDesactivationPoubelle[i]->setIcon(*iconeActivation);
        afficherEtatBoutonActivationDesactivation(boutonsActivationDesactivationPoubelle[i], i);
        /*boutonsActivationDesactivationPoubelle[i]->setIconSize(
          imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
        boutonsActivationDesactivationPoubelle[i]->setFixedSize(
          imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());*/
    }

    boutonActivationDesactivationBoiteAuxLettres->setIcon(*iconeActivation);
    afficherEtatBoutonActivationDesactivation(boutonActivationDesactivationBoiteAuxLettres, 0);
    /*boutonActivationDesactivationBoiteAuxLettres->setIconSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonActivationDesactivationBoiteAuxLettres->setFixedSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());*/
}

/**
 * @brief Affichage d'un bouton d'activation
 * @fn IHMDomotifications::afficherBoutonActivation
 * @param boutonModule
 */
void IHMDomotifications::afficherBoutonActivation(QPushButton* boutonModule)
{
    boutonModule->setIcon(*iconeActivation);
    /*boutonModule->setIconSize(imageBoutonAmessageIconctivation->scaled(HAUTEUR_IMAGE,
    LARGEUR_IMAGE).size()); boutonModule->setFixedSize(imageBoutonActivation->scaled(HAUTEUR_IMAGE,
    LARGEUR_IMAGE).size());*/
}

/**
 * @brief Affichage d'un bouton de désactivation
 * @fn IHMDomotifications::afficherBoutonDesactivation
 * @param boutonModule
 */
void IHMDomotifications::afficherBoutonDesactivation(QPushButton* boutonModule)
{
    boutonModule->setIcon(*iconeDesactivation);

    /*boutonModule->setIconSize(
      imageBoutonDesactivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonModule->setFixedSize(
      imageBoutonDesactivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());*/
}

/**
 * @brief Affichage des boutons d'acquittement
 * @fn IHMDomotifications::afficherBoutonAcquittement
 * @details Affichage des boutons d'acquittement des différents modules
 */
void IHMDomotifications::afficherBoutonAcquittement()
{
    for(auto i = 0; i < machines.size(); i++)
    {
        boutonsAcquittementMachine[i]->setIcon(*iconeAcquittement);
        gererEtatBoutonAcquittement(boutonsAcquittementMachine[i], i);
    }

    for(auto i = 0; i < poubelles.size(); i++)
    {
        boutonsAcquittementPoubelle[i]->setIcon(*iconeAcquittement);
        gererEtatBoutonAcquittement(boutonsAcquittementPoubelle[i], i);
    }

    boutonAcquittementBoiteAuxLettres->setIcon(*iconeAcquittement);
    gererEtatBoutonAcquittement(boutonAcquittementBoiteAuxLettres, 0);
}

/**
 * @brief Récupère l'id du module associé à ce bouton
 * @fn IHMDomotifications::recupererIdModule
 * @param boutonModule le QPushButton associé au module
 */
int IHMDomotifications::recupererIdModule(QPushButton* boutonModule)
{
    if(boutonModule->objectName() == Module::getType(Module::TypeModule::Poubelle))
    {
        for(int i = 0; i < boutonsActivationDesactivationPoubelle.size(); i++)
        {
            if(boutonModule == boutonsActivationDesactivationPoubelle[i])
            {
                return i;
            }
        }
        for(int i = 0; i < boutonsAcquittementPoubelle.size(); i++)
        {
            if(boutonModule == boutonsAcquittementPoubelle[i])
            {
                return i;
            }
        }
    }
    else if(boutonModule->objectName() == Module::getType(Module::TypeModule::Machine))
    {
        for(int i = 0; i < boutonsActivationDesactivationMachine.size(); i++)
        {
            if(boutonModule == boutonsActivationDesactivationMachine[i])
            {
                return i;
            }
        }
        for(int i = 0; i < boutonsAcquittementMachine.size(); i++)
        {
            if(boutonModule == boutonsAcquittementMachine[i])
            {
                return i;
            }
        }
    }
    else
    {
        return 0;
    }
    return 0; // supprime le warning
}

/**
 * @brief Récupère le type de module associé à ce bouton
 * @fn IHMDomotifications::recupererTypeModule
 * @param boutonModule le QPushButton associé au module
 */
QString IHMDomotifications::recupererTypeModule(QPushButton* boutonModule)
{
    return boutonModule->objectName();
}

/**
 * @brief Affiche les Widgets
 * @fn IHMDomotifications::afficherWidgets
 * @details Affiche les widget de l'IHM
 */
void IHMDomotifications::afficherWidgets()
{
    // boutonParametres->setIcon(QIcon(*imageLogoParametre));
    // logoBTS->setPixmap(QPixmap(CHEMIN_LOGO_BTS_SN));
    for(int i = 0; i < poubelles.size(); i++)
    {
        logosPoubelle[i]->setPixmap(
          imagesLogoPoubelle[i]->scaled(imagesLogoPoubelle[i]->width() / 3,
                                        imagesLogoPoubelle[i]->height() / 3));
    }
    for(int i = 0; i < machines.size(); i++)
    {
        logosMachine[i]->setPixmap(
          imageLogoMachine->scaled(imageLogoMachine->width() / 3, imageLogoMachine->height() / 3));
    }
    logoBoiteAuxLettres->setPixmap(
      imageLogoBoiteAuxLettres->scaled(imageLogoBoiteAuxLettres->width() / 3,
                                       imageLogoBoiteAuxLettres->height() / 3));

    afficherBoutonsActivationDesactivation();
    afficherBoutonAcquittement();

    for(int indexVecteurPoubelle = 0; indexVecteurPoubelle < poubelles.size();
        indexVecteurPoubelle++)
    {
        layoutsBoutonsPoubelle[indexVecteurPoubelle]->addWidget(
          boutonsAcquittementPoubelle[indexVecteurPoubelle]);
        layoutsBoutonsPoubelle[indexVecteurPoubelle]->addWidget(
          boutonsActivationDesactivationPoubelle[indexVecteurPoubelle]);
        layoutsPoubelle[indexVecteurPoubelle]->addWidget(logosPoubelle[indexVecteurPoubelle]);
        layoutsPoubelle[indexVecteurPoubelle]->addLayout(
          layoutsBoutonsPoubelle[indexVecteurPoubelle]);
    }

    for(int indexVecteurMachine = 0; indexVecteurMachine < machines.size(); indexVecteurMachine++)
    {
        layoutsBoutonsMachine[indexVecteurMachine]->addWidget(
          boutonsAcquittementMachine[indexVecteurMachine]);
        layoutsBoutonsMachine[indexVecteurMachine]->addWidget(
          boutonsActivationDesactivationMachine[indexVecteurMachine]);
        layoutsMachine[indexVecteurMachine]->addWidget(logosMachine[indexVecteurMachine]);
        layoutsMachine[indexVecteurMachine]->addLayout(layoutsBoutonsMachine[indexVecteurMachine]);
    }

    layoutBoutonsBoiteAuxLettres->addWidget(boutonAcquittementBoiteAuxLettres);
    layoutBoutonsBoiteAuxLettres->addWidget(boutonActivationDesactivationBoiteAuxLettres);
    layoutBoiteAuxLettres->addWidget(logoBoiteAuxLettres);
    layoutBoiteAuxLettres->addLayout(layoutBoutonsBoiteAuxLettres);
    layoutBoiteAuxLettres->addStretch();

    for(int i = 0; i < poubelles.size(); i++)
    {
        layoutPoubelles->addLayout(layoutsPoubelle[i]);
    }
    for(int indexMachine = 0; indexMachine < machines.size(); indexMachine++)
    {
        layoutMachines->addLayout(layoutsMachine[indexMachine]);
    }

    //----------------

    layoutPrincipal->addLayout(layoutLogos);
    layoutPoubelles->addStretch();
    layoutPrincipal->addLayout(layoutPoubelles);
    layoutMachines->addStretch();
    layoutPrincipal->addLayout(layoutMachines);
    layoutPrincipal->addLayout(layoutBoiteAuxLettres);
    layoutPrincipal->addStretch();
}

/**
 * @brief Initialise le widget central
 * @fn IHMDomotifications::initialiserFenetrePrincipale
 */
void IHMDomotifications::initialiserFenetrePrincipale()
{
    widgetPrincipal->setLayout(layoutPrincipal);
    setCentralWidget(widgetPrincipal);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    resize(screenGeometry.width(), screenGeometry.height());
}

/**
 * @brief Initialise l'interface graphique
 *
 * @fn IHMDomotifications::initialiserGUI
 * @details Génère la page graphique d'interface
 */
void IHMDomotifications::initialiserGUI()
{
    initialiserWidgets();
    afficherWidgets();
    initialiserFenetrePrincipale();
}

/**
 * @brief Initialise la Barre de taches
 *
 * @fn IHMDomotifications::initialiserBarreDeTaches
 * @details Initialise l'icone et l'application en arrière plan
 */
void IHMDomotifications::initialiserBarreDeTaches()
{
    creerActionsMenu();

    connecterActions();

    creerMenu();

    creerIconeBarreDesTaches();

    afficherIconeBarreDesTaches();
}

/**
 * @brief Créer les actions du menu
 *
 * @fn IHMDomotifications::creerActionsMenu
 * @details Créer les actions du menu de l'application en fond de tâche.
 */
void IHMDomotifications::creerActionsMenu()
{
    actionMinimiser = new QAction(QString::fromUtf8("Minimiser"), this);
    actionMaximiser = new QAction(QString::fromUtf8("Maximiser"), this);
    actionRestaurer = new QAction(QString::fromUtf8("Restaurer"), this);
    actionQuitter   = new QAction(QString::fromUtf8("&Quitter"), this);
}

/**
 * @brief Connection des actions
 *
 * @fn IHMDomotifications::connecterActions
 * @details Fait la connection à l'aide de connect pour relier les signaux du menu aux slots
 * associés.
 */
void IHMDomotifications::connecterActions()
{
    connect(actionMinimiser, SIGNAL(triggered(bool)), this, SLOT(hide()));
    connect(actionMaximiser, SIGNAL(triggered(bool)), this, SLOT(showMaximized()));
    connect(actionRestaurer, SIGNAL(triggered(bool)), this, SLOT(showNormal()));
    connect(actionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

/**
 * @brief Creation du menu
 *
 * @fn IHMDomotifications::creerMenu
 * @details Crée le menu pour la barre des tâches
 */
void IHMDomotifications::creerMenu()
{
    menuIconeSysteme = new QMenu(this);
    menuIconeSysteme->addAction(actionMinimiser);
    menuIconeSysteme->addAction(actionMaximiser);
    menuIconeSysteme->addAction(actionRestaurer);
    menuIconeSysteme->addSeparator();
    menuIconeSysteme->addAction(actionQuitter);
}

/**
 * @brief Creation des icones de la barre des tâches
 *
 * @fn IHMDomotifications::creerIconeBarreDesTaches
 * @details Crée l'icone de l'application en fond sur la barre des tâches
 */
void IHMDomotifications::creerIconeBarreDesTaches()
{
    iconeSysteme = new QSystemTrayIcon(this);
    iconeSysteme->setContextMenu(menuIconeSysteme);
    iconeSysteme->setToolTip(TITRE_APPLICATION);
}

/**
 * @brief Affichage dans la barre des tâches
 *
 * @fn IHMDomotifications::afficherIconeBarreDesTaches
 */
void IHMDomotifications::afficherIconeBarreDesTaches()
{
    iconeSysteme->show();
    etatInitialIconeSysteme = true;
}

/**
 * @brief Initialise les signaux et les slots
 *
 * @fn IHMDomotifications::initialiserSignauxSlots
 * @details Initialise les connects des signaux et des slots
 */
void IHMDomotifications::initialiserSignauxSlots()
{
    connect(iconeSysteme, SIGNAL(messageClicked()), this, SLOT(acquitterNotification()));
    connect(domotification,
            SIGNAL(nouvelleNotification(QString)),
            this,
            SLOT(visualiserNotification(QString)));
#ifdef TEST_NOTIFICATIONS
    connect(boutonParametres, SIGNAL(clicked(bool)), this, SLOT(testerNotification()));
#endif

    // les boutons d'activation/désactivation des modules
    for(int index = 0; index < poubelles.size(); index++)
    {
        connect(boutonsActivationDesactivationPoubelle[index],
                SIGNAL(clicked(bool)),
                this,
                SLOT(gererBoutonActivationDesactivation()));
        connect(boutonsAcquittementPoubelle[index],
                SIGNAL(clicked(bool)),
                this,
                SLOT(gererBoutonAcquittement()));
    }
    for(int index = 0; index < machines.size(); index++)
    {
        connect(boutonsActivationDesactivationMachine[index],
                SIGNAL(clicked(bool)),
                this,
                SLOT(gererBoutonActivationDesactivation()));
        connect(boutonsAcquittementMachine[index],
                SIGNAL(clicked(bool)),
                this,
                SLOT(gererBoutonAcquittement()));
    }
    connect(boutonActivationDesactivationBoiteAuxLettres,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererBoutonActivationDesactivation()));
    connect(boutonAcquittementBoiteAuxLettres,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererBoutonAcquittement()));

    connect(this,
            SIGNAL(activationDesactivationModule(QString, int)),
            domotification,
            SLOT(gererActivationModule(QString, int)));
    connect(this,
            SIGNAL(acquittementNotification(QString, int)),
            domotification,
            SLOT(gererAcquittement(QString, int)));
}

/**
 * @brief Gère les boutons d'activation et de desactivation
 * @fn IHMDomotifications::gererBoutonActivationDesactivation
 * @details Envoie les signaux de chaque bouton d'activation/désactivation vers leur slots
 * respectifs
 */
void IHMDomotifications::gererBoutonActivationDesactivation()
{
    QPushButton* boutonModule = qobject_cast<QPushButton*>(sender());
    QString      typeModule   = recupererTypeModule(boutonModule);
    int          id           = recupererIdModule(boutonModule);
    qDebug() << Q_FUNC_INFO << "typeModule" << typeModule << "id" << id;

    emit activationDesactivationModule(typeModule, id);
    afficherEtatBoutonActivationDesactivation(boutonModule, id);
}

void IHMDomotifications::afficherEtatBoutonActivationDesactivation(QPushButton* boutonModule,
                                                                   int          id)
{
    qDebug() << Q_FUNC_INFO << "boutonModule" << boutonModule->objectName() << "id" << id << "actif"
             << domotification->getActivationModule(boutonModule->objectName(), id);
    if(boutonModule == nullptr)
        return;
    if(domotification->getActivationModule(boutonModule->objectName(), id))
    {
        afficherBoutonDesactivation(boutonModule);
    }
    else
    {
        afficherBoutonActivation(boutonModule);
    }
}

void IHMDomotifications::gererEtatBoutonAcquittement(QPushButton* boutonModule, int id)
{
    if(boutonModule == nullptr)
        return;
    if(domotification->getNotificationModule(boutonModule->objectName(), id))
    {
        boutonModule->setEnabled(false);
    }
    else
    {
        boutonModule->setEnabled(true);
    }
}

/**
 * @brief Gère les boutons d'acquittement
 * @fn IHMDomotifications::gererBoutonAcquittement
 * @details Envoie les signaux de chaque bouton d'acquittement vers leur slots
 * respectifs
 */
void IHMDomotifications::gererBoutonAcquittement()
{
    QPushButton* boutonModule = qobject_cast<QPushButton*>(sender());
    QString      typeModule   = recupererTypeModule(boutonModule);
    int          id           = recupererIdModule(boutonModule);

    qDebug() << Q_FUNC_INFO << "boutonmodule" << boutonModule << "typeModule" << typeModule << "id"
             << id;

    emit acquittementNotification(typeModule, id);
    gererEtatBoutonAcquittement(boutonModule, id);
}
