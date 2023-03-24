#ifndef IHMDOMOTIFICATIONS_H
#define IHMDOMOTIFICATIONS_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMDomotifications;
}
QT_END_NAMESPACE

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
    Ui::IHMDomotifications* ui;
};
#endif // IHMDOMOTIFICATIONS_H
