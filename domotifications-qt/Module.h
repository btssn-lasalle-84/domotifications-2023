#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QString>

class Module : public QObject
{
    Q_OBJECT
  public:
    enum TypeModule
    {
        Inconnu,
        BoiteAuxLettres,
        Machine,
        Poubelle,
    };

  private:
    QString    nomModule;
    TypeModule typeModule;
    bool       estActive;
    bool       estNotifie;

  public:
    Module(QObject* parent = nullptr);
    ~Module();
};

#endif // MODULE_H
