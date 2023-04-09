/**
 * @file IhmDomotifications.cpp
 *
 * @brief Définition de la classe IhmDomotifications
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include "IhmDomotifications.h"
#include "ui_IhmDomotifications.h"

#include "Domotification.h"
#include "Constantes.h"

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
    delete imageBoutonAcquittement;
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

    /**
     * @todo Choisir une durée associée ?
     */

    /*
    switch(type)
    {
        case IHMDomotifications::TypeNotification::Information:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
            break;
        case IHMDomotifications::TypeNotification::Attention:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Warning);
            break;
        case IHMDomotifications::TypeNotification::Critique:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Critical);
            break;
        default:
            break;
    }
    */
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

    boutonParametres                             = new QPushButton(this);
    boutonActivationDesactivationMachine         = new QPushButton(this);
    boutonActivationDesactivationBoiteAuxLettres = new QPushButton(this);
    boutonActivationDesactivationPoubelle        = new QPushButton(this);
    boutonAcquittementPoubelle                   = new QPushButton(this);
    boutonAcquittementBoiteAuxLettres            = new QPushButton(this);
    boutonAcquittementMachine                    = new QPushButton(this);

    imageBoutonActivation   = new QPixmap(CHEMIN_BOUTON_ACTIVATION_DESACTIVATION);
    imageBoutonAcquittement = new QPixmap(CHEMIN_BOUTON_ACQUITTEMENT);
    imageLogoBTS            = new QPixmap(CHEMIN_LOGO_BTS_SN);
    imageLogoParametre      = new QPixmap(CHEMIN_LOGO_PARAMETRE);
    imageLogoPoubelle       = new QPixmap(CHEMIN_LOGO_POUBELLE);

    logoBTS             = new QLabel(this);
    logoBoiteAuxLettres = new QLabel(this);
    logoMachine         = new QLabel(this);
    logoPoubelle        = new QLabel(this);

    iconeAcquittement = new QIcon(*imageBoutonAcquittement);
    iconeActivation   = new QIcon(*imageBoutonActivation);
}

/**
 * @brief Affichage des boutons d'activation/desactivation
 * @fn IHMDomotifications::afficherBoutonActivationDesactivation
 * @details Affichage des boutons d'activation et de desactivation des différents modules
 */
void IHMDomotifications::afficherBoutonActivationDesactivation()
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

    afficherBoutonActivationDesactivation();
    afficherBoutonAcquittement();

    layoutLogos->addWidget(boutonParametres);
    layoutLogos->addStretch();
    layoutLogos->addWidget(logoBTS);

    layoutBoutonsPoubelle->addWidget(boutonAcquittementPoubelle);
    layoutBoutonsPoubelle->addWidget(boutonActivationDesactivationPoubelle);
    layoutPoubelle->addWidget(logoPoubelle);
    layoutPoubelle->addLayout(layoutBoutonsPoubelle);
    layoutPoubelle->addStretch();

    layoutBoutonsMachine->addWidget(boutonAcquittementMachine);
    layoutBoutonsMachine->addWidget(boutonActivationDesactivationMachine);
    layoutMachine->addWidget(logoMachine);
    layoutMachine->addLayout(layoutBoutonsMachine);
    layoutMachine->addStretch();

    layoutBoutonsBoiteAuxLettres->addWidget(boutonAcquittementBoiteAuxLettres);
    layoutBoutonsBoiteAuxLettres->addWidget(boutonActivationDesactivationBoiteAuxLettres);
    layoutBoiteAuxLettres->addWidget(logoBoiteAuxLettres);
    layoutBoiteAuxLettres->addLayout(layoutBoutonsBoiteAuxLettres);
    layoutBoiteAuxLettres->addStretch();

    layoutPrincipal->addLayout(layoutLogos);
    layoutPrincipal->addLayout(layoutPoubelle);
    layoutPrincipal->addLayout(layoutMachine);
    layoutPrincipal->addLayout(layoutBoiteAuxLettres);
}

/**
 * @brief Initialise la page
 *
 * @fn IHMDomotifications::initialiserGUI
 * @details Génère la page graphique d'interface
 */
void IHMDomotifications::initialiserGUI()
{
    initialiserWidgets();
    afficherWidgets();

    widgetPrincipal->setLayout(layoutPrincipal);
    setCentralWidget(widgetPrincipal);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    resize(screenGeometry.width(), screenGeometry.height());
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

    creerIconeBarreDesTache();

    iconeSysteme->show();
    etatInitialIconeSysteme = true;
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
 * @fn IHMDomotifications::creerIconeBarreDesTache
 * @details Crée l'icone de l'application en fond sur la barre des tâches
 */
void IHMDomotifications::creerIconeBarreDesTache()
{
    iconeSysteme = new QSystemTrayIcon(this);
    iconeSysteme->setContextMenu(menuIconeSysteme);
    iconeSysteme->setToolTip(TITRE_APPLICATION);
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
}
