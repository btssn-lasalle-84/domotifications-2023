#ifndef MODULE_H
#define MODULE_H

/**
 * @file Module.h
 *
 * @brief Déclaration de la classe Module
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include <QObject>
#include <QString>

class Module : public QObject
{
    Q_OBJECT
  public:
    /**
     * @enum TypeModule
     * @brief Les différents types de module
     */
    enum TypeModule
    {
        Inconnu,
        BoiteAuxLettres,
        Machine,
        Poubelle,
    };

  private:
    int        id;
    QString    nomModule;
    TypeModule typeModule;
    bool       actif;
    bool       notifie;

  public:
    Module(QString nomModule, Module::TypeModule type, int id, QObject* parent = nullptr);
    ~Module();
    /**
     * @todo Ajouter accesseurs/mutateurs
     */
    int                getId() const;
    Module::TypeModule getType() const;
    bool               estActif() const;
    bool               estNotifie() const;
    void               setActif(bool actif);
    static QString     getType(Module::TypeModule type);
};

#endif // MODULE_H
