#ifndef IHMDOMOTIFICATIONS_H
#define IHMDOMOTIFICATIONS_H

/**
 * @file IhmDomotifications.h
 *
 * @brief Déclaration de la classe IhmDomotifications
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include "Constantes.h"
#include <QtWidgets>

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
    QWidget*                widgetPrincipal; //!< Le widget central
    QVBoxLayout*            layoutPrincipal;
    Ui::IHMDomotifications* ui;               //!< La GUI
    Domotification*         domotification;   //!< l'objet contrôleur de l'application
    QSystemTrayIcon*        iconeSysteme;     //!< L'icône de l'application pour la barre système
    QMenu*                  menuIconeSysteme; //!< Le menu de l'application
    QAction*                actionMinimiser;  //!< L'action minimiser l'application
    QAction*                actionMaximiser;  //!< L'action maximiser l'application
    QAction*                actionRestaurer;  //!< L'action restaurer l'application
    QAction*                actionQuitter;    //!< L'action quitter l'application
    bool                    etatInitialIconeSysteme; //!< Booléen indiquant si c'est la première
                                                     //!< demande Quitter
    QPushButton* boutonActivationDesactivationMachine;
    QPushButton* boutonActivationDesactivationBoiteAuxLettres;
    QPushButton* boutonActivationDesactivationPoubelle;
    QPushButton* boutonAcquittementMachine;
    QPushButton* boutonAcquittementPoubelle;
    QPushButton* boutonAcquittementBoiteAuxLettres;

    QPixmap* imageBoutonActivation;
    QPixmap* imageBoutonAcquittement;
    QPixmap* imageLogoBTS;
    QPixmap* imageLogoParametre;
    QPixmap* imageLogoPoubelle;

    QLabel* logoBTS;
    QLabel* logoParametre;
    QLabel* logoMachine;
    QLabel* logoBoiteAuxLettres;
    QLabel* logoPoubelle;

    QIcon* iconeActivation;
    QIcon* iconeAcquittement;

    QRect* rect;

#ifdef TEST_NOTIFICATIONS

    QPushButton* boutonNotifier;      //!< Le bouton permettant de tester une notification
    QLineEdit*   messageNotification; //!< Le message de la notification
#endif

  public:
    IHMDomotifications(QWidget* parent = nullptr);
    ~IHMDomotifications();

    void initialiserGUI();
    void initialiserBarreDeTaches();
    void initialiserSignauxSlots();

    void initialiserWidget();

    void afficherWidget();

    void creerActionsMenu();

    void connecterActions();

    void creerMenu();

    void creerIconeBarreDesTache();

    void afficherBoutonActivationDesactivation();

    void afficherBoutonAcquittement();

  public slots:
#ifdef TEST_NOTIFICATIONS
    void testerNotification();
#endif
    void visualiserNotification(
      QString          message,
      TypeNotification type = IHMDomotifications::TypeNotification::Information);
    void acquitterNotification();
};

#endif // IHMDOMOTIFICATIONS_H
