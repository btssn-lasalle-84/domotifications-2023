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
void IHMDomotifications::initialiserSysteme()
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
    iconeSysteme->setToolTip("MainWindow");
    // QIcon icone(":/icone1.png");
    // iconeSysteme->setIcon(icone);
    // setWindowIcon(icone);

    connect(iconeSysteme, SIGNAL(messageClicked()), this, SLOT(acquitterNotification()));
    connect(iconeSysteme,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(aActiveIconeSysteme(QSystemTrayIcon::ActivationReason)));

    iconeSysteme->show();
    etatInitialIconeSysteme = true;
}

IHMDomotifications::IHMDomotifications(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMDomotifications)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    /* setWindowTitle(TITRE_APPLICATION);
     resize(qApp->desktop()->availableGeometry(this).width(),
            qApp->desktop()->availableGeometry(this).height());
     // showMaximized();
 */
    initialiserSysteme();
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

void IHMDomotifications::afficherModules()
{
}

void IHMDomotifications::gererEtatModule()
{
}

void IHMDomotifications::gererActivationModule()
{
}

void IHMDomotifications::visualiserNotification(QString titre,
                                                QString message,
                                                int     niveau,
                                                int     duree)
{
    QSystemTrayIcon::MessageIcon messageIcon;
    switch(niveau)
    {
        case 0:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::NoIcon);
            break;
        case 1:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
            break;
        case 2:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Warning);
            break;
        case 3:
            messageIcon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Critical);
            break;
    }
    if(niveau < (listeNiveau->count()) - 1)                            // sauf le dernier
        iconeSysteme->showMessage(titre, message, messageIcon, duree); // duree en ms
}

void IHMDomotifications::acquitterNotification()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMDomotifications::parametrer()
{
}

void IHMDomotifications::testerNotification()
{
    if(!message->text().isEmpty())
        visualiserNotification("Domotification", message->text(), listeNiveau->currentIndex());
}

void IHMDomotifications::initialiserGUI()
{
    centralWidget = new QWidget;

    btNotifier = new QPushButton("Notifier", this);
    message    = new QLineEdit(this);
    message->setText("La machine est finie !");
    message->setFont(QFont("Courier New", 14, QFont::Bold));
    listeNiveau = new QComboBox(this);
    listeNiveau->addItem("NoIcon");
    listeNiveau->addItem("Information");
    listeNiveau->addItem("Warning");
    listeNiveau->addItem("Critical");
    listeNiveau->addItem("Other");

    QVBoxLayout* mainLayout     = new QVBoxLayout;
    QHBoxLayout* hLayoutBoutons = new QHBoxLayout;
    QHBoxLayout* hLayoutMessage = new QHBoxLayout;
    hLayoutMessage->addWidget(message);
    mainLayout->addLayout(hLayoutMessage);
    hLayoutBoutons->addWidget(listeNiveau);
    hLayoutBoutons->addWidget(btNotifier);
    mainLayout->addLayout(hLayoutBoutons);
    mainLayout->addStretch();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    qApp->desktop()->availableGeometry()));

    connect(btNotifier, SIGNAL(clicked(bool)), this, SLOT(testerNotification()));
}
