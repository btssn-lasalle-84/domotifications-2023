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

  public:
    IHMDomotifications(QWidget* parent = nullptr);
    ~IHMDomotifications();

    void afficherModules();
    void gererEtatModule();
    void gererActivationModule();
    void visualiserNotification();
    void acquitterNotification();
    void parametrer();

  private:
    Ui::IHMDomotifications* ui; //!< la GUI
};

#endif // IHMDOMOTIFICATIONS_H
