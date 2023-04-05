#ifndef IHMDOMOTIFICATIONS_H
#define IHMDOMOTIFICATIONS_H

/**
 * @file IhmDomotifications.h
 *
 * @brief Déclaration de la classe IhmDomotifications
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include <QtWidgets>

/**
 * @def TITRE_APPLICATION
 * @brief Le nom de l'appilcation dans la barre de titre
 */
#define TITRE_APPLICATION "Domotifications"

//#define TEST_NOTIFICATIONS

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMDomotifications;
}
QT_END_NAMESPACE

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
    QSystemTrayIcon* iconeSysteme;            //!< L'icône de l'application pour la barre système
    QMenu*           menuIconeSysteme;        //!< Le menu de l'application
    QAction*         actionMinimiser;         //!< L'action minimiser l'application
    QAction*         actionMaximiser;         //!< L'action maximiser l'application
    QAction*         actionRestaurer;         //!< L'action restaurer l'application
    QAction*         actionQuitter;           //!< L'action quitter l'application
    bool             etatInitialIconeSysteme; //!< Booléen indiquant si c'est la première
                                              //!< demande Quitter
#ifdef TEST_NOTIFICATIONS
    QWidget*     centralWidget;       //!< Le widget central
    QPushButton* boutonNotifier;      //!< Le bouton permettant de tester une notification
    QLineEdit*   messageNotification; //!< Le message de la notification
#endif

  public:
    IHMDomotifications(QWidget* parent = nullptr);
    ~IHMDomotifications();

    void initialiserGUI();
    void initialiserBarreDeTaches();

    void visualiserNotification(
      QString          titre,
      QString          messageNotification,
      TypeNotification type = IHMDomotifications::TypeNotification::Information);

  private:
    Ui::IHMDomotifications* ui; //!< la GUI

  public slots:
#ifdef TEST_NOTIFICATIONS
    void testerNotification();
#endif
    void acquitterNotification();
};

#endif // IHMDOMOTIFICATIONS_H
