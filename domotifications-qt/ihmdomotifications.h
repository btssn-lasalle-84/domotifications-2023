#ifndef IHMDOMOTIFICATIONS_H
#define IHMDOMOTIFICATIONS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IHMDomotifications; }
QT_END_NAMESPACE

class IHMDomotifications : public QMainWindow
{
    Q_OBJECT

public:
    IHMDomotifications(QWidget *parent = nullptr);
    ~IHMDomotifications();

private:
    Ui::IHMDomotifications *ui;
};
#endif // IHMDOMOTIFICATIONS_H
