#ifndef MODULE_H
#define MODULE_H

#include <QObject>

class Module : public QObject
{
    Q_OBJECT
  private:
    string nomModule;
    bool   estActive;
    bool   estNotifie;
    enum TypeModule
    {
        BoiteAuxLettres,
        Machine,
        Poubelle,
    };

  public:
    Module(QObject* parent = nullptr);
};

#endif // MODULE_H
