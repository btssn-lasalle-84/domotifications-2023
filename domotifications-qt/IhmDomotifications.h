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

namespace Ui
{
class IHMDomotifications;
}

class Domotification;

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
    Ui::IHMDomotifications* ui;               //!< La GUI
    Domotification*         domotification;   //!< l'objet contrôleur de l'application
    QVector<QObject*>       poubelles; //!< Vecteur de poubelles
    QVector<QObject*>        machines; //!< Vecteur de machines
    QSystemTrayIcon*        iconeSysteme;     //!< L'icône de l'application pour la barre système
    QMenu*                  menuIconeSysteme; //!< Le menu de l'application
    QAction*                actionMinimiser;  //!< L'action minimiser l'application
    QAction*                actionMaximiser;  //!< L'action maximiser l'application
    QAction*                actionRestaurer;  //!< L'action restaurer l'application
    QAction*                actionQuitter;    //!< L'action quitter l'application
    bool                    etatInitialIconeSysteme; //!< Booléen indiquant si c'est la première
                                                     //!< demande Quitter

    QWidget*     widgetPrincipal;                    //!< Le widget central
    QVBoxLayout* layoutPrincipal;
    QHBoxLayout* layoutLogos;
    QHBoxLayout* layoutPoubelle;
    QHBoxLayout* layoutMachine;
    QHBoxLayout* layoutBoiteAuxLettres;
    QVBoxLayout* layoutBoutonsPoubelle;
    QVBoxLayout* layoutBoutonsMachine;
    QVBoxLayout* layoutBoutonsBoiteAuxLettres;
    QPushButton* boutonParametres;
    /**
     * @todo Gérer un conteneur pour les machines et poubelles
     */
    QPushButton* boutonActivationDesactivationMachine;
    QPushButton* boutonActivationDesactivationBoiteAuxLettres;
    QPushButton* boutonActivationDesactivationPoubelle;
    /**
     * @todo Gérer un conteneur pour les machines et poubelles
     */
    QPushButton* boutonAcquittementMachine;
    QPushButton* boutonAcquittementPoubelle;
    QPushButton* boutonAcquittementBoiteAuxLettres;
    QPixmap*     imageBoutonActivation;
    QPixmap*     imageBoutonDesactivation;
    QPixmap*     imageBoutonAcquittement;
    QPixmap*     imageLogoBTS;
    QPixmap*     imageLogoParametre;
    QPixmap*     imageLogoPoubelle;
    QLabel*      logoBTS;
    QLabel*      logoMachine;
    QLabel*      logoBoiteAuxLettres;
    QLabel*      logoPoubelle;
    QIcon*       iconeActivation;
    QIcon*       iconeDesactivation;
    QIcon*       iconeAcquittement;

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

    void initialiserGUI();
    void initialiserBarreDeTaches();
    void initialiserSignauxSlots();
    void initialiserWidgets();
    void afficherWidgets();
    void creerActionsMenu();
    void connecterActions();
    void creerMenu();
    void creerIconeBarreDesTaches();
    void afficherIconeBarreDesTaches();
    void afficherBoutonsActivationDesactivation();
    void afficherBoutonActivation(QPushButton* boutonModule);
    void afficherBoutonDesactivation(QPushButton* boutonModule);
    void afficherBoutonAcquittement();

  signals:
    void activationDesactivationModule(QString nomModule);

  public slots:
#ifdef TEST_NOTIFICATIONS
    void testerNotification();
#endif
    void gererBoutonActivationDesactivation();

    void visualiserNotification(
      QString          message,
      TypeNotification type = IHMDomotifications::TypeNotification::Information);
    void acquitterNotification();
};

#endif // IHMDOMOTIFICATIONS_H
