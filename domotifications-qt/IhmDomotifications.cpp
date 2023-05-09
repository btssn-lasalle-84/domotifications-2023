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
    delete imageLogoBTS;
    delete imageLogoParametre;
    delete imageLogoPoubelle;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Visualisation des notifications
 *
 * @fn IHMDomotifications::visualiserNotification
 * @details Affiche une notification système avec un type de message et un message prédéfinis
 *
 * @param message de la notification
 * @param type pour les différents types de notifications en fonction de la gravité
 */
void IHMDomotifications::visualiserNotification(QString message, TypeNotification type)
{
    QSystemTrayIcon::MessageIcon messageIcon =
      QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Critical);

    iconeSysteme->showMessage(TITRE_APPLICATION, message, messageIcon);
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
    widgetPrincipal              = new QWidget(this);
    layoutPrincipal              = new QVBoxLayout;
    layoutLogos                  = new QHBoxLayout;
    layoutMachine                = new QHBoxLayout;
    layoutBoiteAuxLettres        = new QHBoxLayout;
    layoutPoubelle               = new QHBoxLayout;
    layoutBoutonsMachine         = new QVBoxLayout;
    layoutBoutonsBoiteAuxLettres = new QVBoxLayout;
    layoutBoutonsPoubelle        = new QVBoxLayout;

    boutonParametres = new QPushButton(this);

    /**
     * @todo Gérer un conteneur pour les machines et poubelles
     */
    machines = domotification->getMachines();
    for(auto i = 0; i < machines.size(); i++)
    {
        qDebug() << Q_FUNC_INFO << "module" << machines[i]->getNom() << "id" << machines[i]->getId()
                 << "type" << machines[i]->getType();
    }

    poubelles = domotification->getPoubelles();
    for(auto i = 0; i < poubelles.size(); i++)
    {
        qDebug() << Q_FUNC_INFO << "module" << poubelles[i]->getNom() << "id"
                 << poubelles[i]->getId() << "type" << poubelles[i]->getType();
    }

    boutonActivationDesactivationMachine = new QPushButton(this);
    boutonActivationDesactivationMachine->setObjectName("Machine");
    boutonActivationDesactivationBoiteAuxLettres = new QPushButton(this);
    boutonActivationDesactivationBoiteAuxLettres->setObjectName("BoiteAuxLettres");
    boutonActivationDesactivationPoubelle = new QPushButton(this);
    boutonActivationDesactivationPoubelle->setObjectName("Poubelle");

    boutonAcquittementPoubelle        = new QPushButton(this);
    boutonAcquittementBoiteAuxLettres = new QPushButton(this);
    boutonAcquittementMachine         = new QPushButton(this);

    imageBoutonActivation    = new QPixmap(CHEMIN_BOUTON_ACTIVATION);
    imageBoutonDesactivation = new QPixmap(CHEMIN_BOUTON_DESACTIVATION);
    imageBoutonAcquittement  = new QPixmap(CHEMIN_BOUTON_ACQUITTEMENT);
    imageLogoBTS             = new QPixmap(CHEMIN_LOGO_BTS_SN);
    imageLogoParametre       = new QPixmap(CHEMIN_LOGO_PARAMETRE);
    imageLogoPoubelle        = new QPixmap(CHEMIN_LOGO_POUBELLE);

    logoBTS             = new QLabel(this);
    logoBoiteAuxLettres = new QLabel(this);
    logoMachine         = new QLabel(this);
    logoPoubelle        = new QLabel(this);

    iconeActivation    = new QIcon(*imageBoutonActivation);
    iconeDesactivation = new QIcon(*imageBoutonDesactivation);
    iconeAcquittement  = new QIcon(*imageBoutonAcquittement);
}

/**
 * @brief Affichage des boutons d'activation/desactivation
 * @fn IHMDomotifications::afficherBoutonActivationDesactivation
 * @details Affichage des boutons d'activation et de desactivation des différents modules
 */
void IHMDomotifications::afficherBoutonsActivationDesactivation()
{
    boutonActivationDesactivationMachine->setIcon(*iconeActivation);
    boutonActivationDesactivationMachine->setIconSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonActivationDesactivationMachine->setFixedSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());

    boutonActivationDesactivationPoubelle->setIcon(*iconeActivation);
    boutonActivationDesactivationPoubelle->setIconSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonActivationDesactivationPoubelle->setFixedSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());

    boutonActivationDesactivationBoiteAuxLettres->setIcon(*iconeActivation);
    boutonActivationDesactivationBoiteAuxLettres->setIconSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonActivationDesactivationBoiteAuxLettres->setFixedSize(
      imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
}

/**
 * @brief Affichage d'un bouton d'activation
 */
void IHMDomotifications::afficherBoutonActivation(QPushButton* boutonModule)
{
    boutonModule->setIcon(*iconeActivation);
    boutonModule->setIconSize(imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonModule->setFixedSize(imageBoutonActivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
}

/**
 * @brief Affichage d'un bouton de désactivation
 */
void IHMDomotifications::afficherBoutonDesactivation(QPushButton* boutonModule)
{
    boutonModule->setIcon(*iconeDesactivation);
    boutonModule->setIconSize(
      imageBoutonDesactivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonModule->setFixedSize(
      imageBoutonDesactivation->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
}

/**
 * @brief Affichage des boutons d'acquittement
 * @fn IHMDomotifications::afficherBoutonAcquittement
 * @details Affichage des boutons d'acquittement des différents modules
 */
void IHMDomotifications::afficherBoutonAcquittement()
{
    boutonAcquittementMachine->setIcon(*iconeAcquittement);
    boutonAcquittementMachine->setIconSize(
      imageBoutonAcquittement->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonAcquittementMachine->setFixedSize(
      imageBoutonAcquittement->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());

    boutonAcquittementPoubelle->setIcon(*iconeAcquittement);
    boutonAcquittementPoubelle->setIconSize(
      imageBoutonAcquittement->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonAcquittementPoubelle->setFixedSize(
      imageBoutonAcquittement->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());

    boutonAcquittementBoiteAuxLettres->setIcon(*iconeAcquittement);
    boutonAcquittementBoiteAuxLettres->setIconSize(
      imageBoutonAcquittement->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
    boutonAcquittementBoiteAuxLettres->setFixedSize(
      imageBoutonAcquittement->scaled(HAUTEUR_IMAGE, LARGEUR_IMAGE).size());
}

/**
 * @brief Affiche les Widgets
 * @fn IHMDomotifications::afficherWidgets
 * @details Affiche les widget de l'IHM
 */
void IHMDomotifications::afficherWidgets()
{
    boutonParametres->setIcon(QIcon(*imageLogoParametre));

    logoBTS->setPixmap(QPixmap(CHEMIN_LOGO_BTS_SN));
    logoPoubelle->setPixmap(QPixmap(CHEMIN_LOGO_POUBELLE));
    logoBoiteAuxLettres->setPixmap(QPixmap(CHEMIN_LOGO_BOITE_AUX_LETTRES));
    logoMachine->setPixmap(QPixmap(CHEMIN_LOGO_MACHINE));

    afficherBoutonsActivationDesactivation();
    afficherBoutonAcquittement();

    layoutLogos->addWidget(boutonParametres);
    layoutLogos->addStretch();
    layoutLogos->addWidget(logoBTS);
    for(auto i = 0; i < poubelles.size(); i++)
    {
        layoutBoutonsPoubelle->addWidget(boutonAcquittementPoubelle);
        layoutBoutonsPoubelle->addWidget(boutonActivationDesactivationPoubelle);
        // layoutPoubelle->addWidget(logoPoubelle);
    }
    layoutPoubelle->addLayout(layoutBoutonsPoubelle);
    layoutPoubelle->addStretch();

    layoutBoutonsMachine->addWidget(boutonAcquittementMachine);
    layoutBoutonsMachine->addWidget(boutonActivationDesactivationMachine);
    // layoutMachine->addWidget(logoMachine);
    layoutMachine->addLayout(layoutBoutonsMachine);
    layoutMachine->addStretch();

    layoutBoutonsBoiteAuxLettres->addWidget(boutonAcquittementBoiteAuxLettres);
    layoutBoutonsBoiteAuxLettres->addWidget(boutonActivationDesactivationBoiteAuxLettres);
    // layoutBoiteAuxLettres->addWidget(logoBoiteAuxLettres);
    layoutBoiteAuxLettres->addLayout(layoutBoutonsBoiteAuxLettres);
    layoutBoiteAuxLettres->addStretch();

    layoutPrincipal->addLayout(layoutLogos);
    layoutPrincipal->addLayout(layoutPoubelle);
    layoutPrincipal->addLayout(layoutMachine);
    layoutPrincipal->addLayout(layoutBoiteAuxLettres);
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

#ifdef TEST_NOTIFICATIONS
    connect(boutonParametres, SIGNAL(clicked(bool)), this, SLOT(testerNotification()));
#endif
    connect(domotification,
            SIGNAL(nouvelleNotification(QString)),
            this,
            SLOT(visualiserNotification(QString)));
    // les boutons d'activation/désactivation des modules
    connect(boutonActivationDesactivationMachine,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererBoutonActivationDesactivation()));
    connect(boutonActivationDesactivationBoiteAuxLettres,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererBoutonActivationDesactivation()));
    connect(boutonActivationDesactivationPoubelle,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererBoutonActivationDesactivation()));
    connect(this,
            SIGNAL(activationDesactivationModule(QString, int)),
            domotification,
            SLOT(gererActivationModule(QString, int)));
}

/**
 * @brief Gère les boutons d'activation et de desactivation
 * @fn IHMDomotifications::gererBoutonActivationDesactivation
 * @details Envoie les signaux de chaque bouton d'activation/désactivation vers leur slots
 * respectifs
 */
void IHMDomotifications::gererBoutonActivationDesactivation()
{
    int          i            = 0;
    QPushButton* boutonModule = qobject_cast<QPushButton*>(sender());
    qDebug() << Q_FUNC_INFO << "bouton" << boutonModule->objectName();
    if(boutonModule == boutonActivationDesactivationMachine)
    {
        /**
         * @todo Gérer l'id du module
         */
        emit activationDesactivationModule(boutonModule->objectName(), machines[i]->getId());
        if(domotification->getActivationModule(boutonModule->objectName()))
            afficherBoutonActivation(boutonModule);
        else
            afficherBoutonDesactivation(boutonModule);
    }
    else if(boutonModule == boutonActivationDesactivationBoiteAuxLettres)
    {
        emit activationDesactivationModule(boutonModule->objectName(), 0);
        if(domotification->getActivationModule(boutonModule->objectName()))
        {
            afficherBoutonActivation(boutonModule);
        }
        else
        {
            afficherBoutonDesactivation(boutonModule);
        }
    }
    else if(boutonModule == boutonActivationDesactivationPoubelle)
    {
        /**
         * @todo Gérer l'id du module
         */
        emit activationDesactivationModule(boutonModule->objectName(), poubelles[i]->getId());
        if(domotification->getActivationModule(boutonModule->objectName()))
        {
            afficherBoutonActivation(boutonModule);
        }
        else
        {
            afficherBoutonDesactivation(boutonModule);
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "bouton inconnu !";
    }
}
