#ifndef IHMDOMOTIFICATIONS_H
#define IHMDOMOTIFICATIONS_H

/**
 * @file IhmDomotifications.h
 *
 * @brief Déclaration de la classe IhmDomotifications
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "Constantes.h"
#include "Module.h"
#include <QtWidgets>
#include <QObject>
#include <QVector>

namespace Ui
{
class IHMDomotifications;
}

class Domotification;
class Module;

/**
 * @class IHMDomotifications
 * @brief La fenêtyre principale de l'application Domotifications
 */
class IHMDomotifications : public QMainWindow
{
    Q_OBJECT

  public:
    /**
     * @enum TypeNotification
     * @brief Une liste de types de notification
     */
    enum TypeNotification
    {
        Information,
        Attention,
        Critique,
        NbTypes
    };

  private:
    Ui::IHMDomotifications* ui;             //!< La GUI
    Domotification*         domotification; //!< L'objet contrôleur de l'application
    QVector<Module*>        machines;
    QVector<Module*>        poubelles;
    Module*                 boite;
    bool                    etatInitialIconeSysteme; //!< Booléen indiquant si c'est la première
                                                     //!< demande Quitter

    // Widgets
    QWidget* widgetPrincipal; //!< Le widget central
    // La barre système
    QSystemTrayIcon* iconeSysteme;     //!< L'icône de l'application pour la barre système
    QMenu*           menuIconeSysteme; //!< Le menu de l'application
    QAction*         actionMinimiser;  //!< L'action minimiser l'application
    QAction*         actionMaximiser;  //!< L'action maximiser l'application
    QAction*         actionRestaurer;  //!< L'action restaurer l'application
    QAction*         actionQuitter;    //!< L'action quitter l'application
    // Les layouts
    QVBoxLayout*          layoutPrincipal;
    QVBoxLayout*          layoutLogos;
    QHBoxLayout*          layoutPoubelles;
    QHBoxLayout*          layoutMachines;
    QHBoxLayout*          layoutBoiteAuxLettres;
    QVector<QHBoxLayout*> layoutsPoubelle;
    QVector<QHBoxLayout*> layoutsMachine;
    QVector<QVBoxLayout*> layoutsBoutonsPoubelle;
    QVector<QVBoxLayout*> layoutsBoutonsMachine;
    QVBoxLayout*          layoutBoutonsBoiteAuxLettres;
    // Les boutons
    QVector<QPushButton*> boutonsActivationDesactivationPoubelle;
    QVector<QPushButton*> boutonsActivationDesactivationMachine;
    QPushButton*          boutonActivationDesactivationBoiteAuxLettres;
    QVector<QPushButton*> boutonsAcquittementPoubelle;
    QVector<QPushButton*> boutonsAcquittementMachine;
    QPushButton*          boutonAcquittementBoiteAuxLettres;
    QPushButton*          boutonParametres;
    // Les images
    QPixmap*          imageBoutonActivation;
    QPixmap*          imageBoutonDesactivation;
    QPixmap*          imageBoutonAcquittement;
    QPixmap*          imageLogoBTS;
    QPixmap*          imageLogoParametre;
    QVector<QPixmap*> imagesLogoPoubelle;
    QPixmap*          imageLogoMachine;
    QPixmap*          imageLogoBoiteAuxLettres;
    QIcon*            iconeActivation;
    QIcon*            iconeDesactivation;
    QIcon*            iconeAcquittement;
    // Les labels
    QLabel*          logoBTS;
    QVector<QLabel*> logosMachine;
    QLabel*          logoBoiteAuxLettres;
    QVector<QLabel*> logosPoubelle;

#ifdef TEST_REQUETE
    // Widgets
    QLabel*      labelURLStation;
    QLineEdit*   editionURLStation;
    QLabel*      labelJSON;
    QLineEdit*   editionJSON;
    QPushButton* boutonGet;
    QPushButton* boutonPost;
    QTextEdit*   journal;
#endif

  public:
    IHMDomotifications(QWidget* parent = nullptr);
    ~IHMDomotifications();

    void    initialiserGUI();
    void    initialiserBarreDeTaches();
    void    initialiserSignauxSlots();
    void    initialiserWidgets();
    void    afficherWidgets();
    void    initialiserFenetrePrincipale();
    void    creerActionsMenu();
    void    connecterActions();
    void    creerMenu();
    void    creerIconeBarreDesTaches();
    void    afficherIconeBarreDesTaches();
    void    afficherBoutonsActivationDesactivation();
    void    afficherBoutonActivation(QPushButton* boutonModule);
    void    afficherBoutonDesactivation(QPushButton* boutonModule);
    void    afficherBoutonAcquittement();
    int     recupererIdModule(QPushButton* boutonModule);
    QString recupererTypeModule(QPushButton* boutonModule);
    void    afficherEtatBoutonActivationDesactivation(QPushButton* boutonModule, int id);
    void    gererEtatBoutonAcquittement(QPushButton* boutonModule, int id);

  signals:
    void activationDesactivationModule(QString nomModule, int id);
    void acquittementNotification(QString typeModule, int id);

  public slots:
#ifdef TEST_NOTIFICATIONS
    void testerNotification();
#endif
    void gererBoutonActivationDesactivation();
    void gererBoutonAcquittement();

    void visualiserNotification(QString message);
    void acquitterNotification();
};

#endif // IHMDOMOTIFICATIONS_H
