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

/**
 * @brief Visualisation des notifications
 *
 * @fn IHMDomotifications::visualiserNotification
 * @details Affiche une notification système avec un type de message et un message prédéfinis
 *
 * @param titre pour le titre de la notification
 * @param message de la notification
 * @param type pour les différents types de notifications en fonction de la gravité
 */
void IHMDomotifications::visualiserNotification(QString          titre,
                                                QString          message,
                                                TypeNotification type)
{
    /**
     * @todo Décider de conserver les types de notifications ?
     */
    QSystemTrayIcon::MessageIcon messageIcon =
      QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

    /**
     * @todo Choisir une durée associée ?
     */
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
    if(type < IHMDomotifications::TypeNotification::NbTypes)
        iconeSysteme->showMessage(titre, message, messageIcon);
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
    if(!messageNotification->text().isEmpty())
        visualiserNotification("Domotification",
                               messageNotification->text()/*,
                               IHMDomotifications::TypeNotification::Attention*/);
}
#endif

/**
 * @brief Initialise la page
 *
 * @fn IHMDomotifications::initialiserGUI
 * @details Génère la page graphique d'interface
 */
void IHMDomotifications::initialiserGUI()
{
#ifdef TEST_NOTIFICATIONS
    centralWidget = new QWidget;

    boutonNotifier      = new QPushButton("Notifier", this);
    messageNotification = new QLineEdit(this);
    messageNotification->setText("La machine est finie !");
    messageNotification->setFont(QFont("Courier New", 14, QFont::Bold));

    QVBoxLayout* mainLayout     = new QVBoxLayout;
    QHBoxLayout* hLayoutBoutons = new QHBoxLayout;
    QHBoxLayout* hLayoutMessage = new QHBoxLayout;
    hLayoutMessage->addWidget(messageNotification);
    mainLayout->addLayout(hLayoutMessage);
    hLayoutBoutons->addWidget(boutonNotifier);
    mainLayout->addLayout(hLayoutBoutons);
    mainLayout->addStretch();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(boutonNotifier, SIGNAL(clicked(bool)), this, SLOT(testerNotification()));
#endif
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    qApp->desktop()->availableGeometry()));
}

/**
 * @brief Initialise la Barre de taches
 *
 * @fn IHMDomotifications::initialiserBarreDeTaches
 * @details Initialise l'icone et l'application en arrière plan
 */
void IHMDomotifications::initialiserBarreDeTaches()
{
    actionMinimiser = new QAction(QString::fromUtf8("Minimiser"), this);
    actionMaximiser = new QAction(QString::fromUtf8("Maximiser"), this);
    actionRestaurer = new QAction(QString::fromUtf8("Restaurer"), this);
    actionQuitter   = new QAction(QString::fromUtf8("&Quitter"), this);

    // Connecte les actions
    connect(actionMinimiser, SIGNAL(triggered(bool)), this, SLOT(hide()));
    connect(actionMaximiser, SIGNAL(triggered(bool)), this, SLOT(showMaximized()));
    connect(actionRestaurer, SIGNAL(triggered(bool)), this, SLOT(showNormal()));
    connect(actionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    // Crée le menu
    menuIconeSysteme = new QMenu(this);
    menuIconeSysteme->addAction(actionMinimiser);
    menuIconeSysteme->addAction(actionMaximiser);
    menuIconeSysteme->addAction(actionRestaurer);
    menuIconeSysteme->addSeparator();
    menuIconeSysteme->addAction(actionQuitter);

    // Crée l'icône pour la barre de tâche
    iconeSysteme = new QSystemTrayIcon(this);
    iconeSysteme->setContextMenu(menuIconeSysteme);
    iconeSysteme->setToolTip("Domotifications");

    connect(iconeSysteme, SIGNAL(messageClicked()), this, SLOT(acquitterNotification()));

    iconeSysteme->show();
    etatInitialIconeSysteme = true;
}
