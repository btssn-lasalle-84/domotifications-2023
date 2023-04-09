#include "IhmDomotifications.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Domotifications
 * @author Mathieu MOYAERTS
 * @version 1.0
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char* argv[])
{
    QApplication       a(argc, argv);
    IHMDomotifications ihmDomotifications;

    ihmDomotifications.show();

    return a.exec();
}
