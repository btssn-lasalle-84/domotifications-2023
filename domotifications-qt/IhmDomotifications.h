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

  private:
    QSystemTrayIcon* iconeSysteme;            //!< L'icône de l'application pour la barre système
    QMenu*           menuIconeSysteme;        //!< Le menu de l'application
    QAction*         actionMinimiser;         //!< L'action minimiser l'application
    QAction*         actionMaximiser;         //!< L'action maximiser l'application
    QAction*         actionRestaurer;         //!< L'action restaurer l'application
    QAction*         actionQuitter;           //!< L'action quitter l'application
    bool             etatInitialIconeSysteme; //!< Booléen indiquant si c'est la première
                                              //!< demande Quitter
    QWidget*     centralWidget;               //!< Le widget central
    QPushButton* btNotifier;                  //!< Le bouton permettant de tester une notification
    QLineEdit*   message;                     //!< Le message de la notification
    QComboBox*   listeNiveau;                 //!< Une liste de niveaux et donc d'icônes pour le
                                              //!< type de notification

  public:
    IHMDomotifications(QWidget* parent = nullptr);
    ~IHMDomotifications();

    void afficherModules();
    void gererEtatModule();
    void gererActivationModule();
    void visualiserNotification(QString titre, QString message, int niveau, int duree = 1000);

    void parametrer();
    void initialiserGUI();
    void initialiserSysteme();

  private:
    Ui::IHMDomotifications* ui; //!< la GUI

  public slots:
    void testerNotification();
    void acquitterNotification();
};

#endif // IHMDOMOTIFICATIONS_H
