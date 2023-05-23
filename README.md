![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=plastic) ![Espressif Badge](https://img.shields.io/badge/Espressif-E7352C?logo=espressif&logoColor=fff&style=plastic)

![](https://badgen.net/badge/Qt/5.12.8/green) [![qt-build](https://github.com/btssn-lasalle-84/domotifications-2023/actions/workflows/make-qt.yml/badge.svg)](https://github.com/btssn-lasalle-84/domotifications-2023/actions/workflows/make-qt.yml) [![platformio-build](https://github.com/btssn-lasalle-84/domotifications-2023/actions/workflows/build-platformio.yml/badge.svg)](https://github.com/btssn-lasalle-84/domotifications-2023/actions/workflows/build-platformio.yml) [![pages-build-deployment](https://github.com/btssn-lasalle-84/domotifications-2023/actions/workflows/pages/pages-build-deployment/badge.svg?branch=develop)](https://github.com/btssn-lasalle-84/domotifications-2023/actions/workflows/pages/pages-build-deployment)

# Le projet domotifications 2023

- [Le projet domotifications 2023](#le-projet-domotifications-2023)
  - [Documentation du code](#documentation-du-code)
  - [Versions](#versions)
    - [0.2](#02)
    - [0.1](#01)
  - [Protocole](#protocole)
  - [Auteurs](#auteurs)

---

Le système **domotifications** doit permettre de notifier visuellement des évènements domotiques (quand et quelle poubelle sortir, quand est-ce qu’un colis a été livré dans la boîte aux lettres et quand est-ce qu’une des machines à laver ou sécher le linge a terminé, ...).

La [station de notifications lumineuses](station-notifications-lumineuses/README.md) est composée d’un bandeau circulaire à leds piloté par un ESP32. Celui-ci est découpé en trois groupes distincts pour les notifications :

- en vert : la notification d’une machine terminée (le système peut gérer jusqu’à _n_ machines individuellement),
- en rouge : la présence d’un colis dans la boîte aux lettres,
- en rouge/bleu/vert/gris/jaune : la notification d'une poubelle de tri à sortir.

L’application PC Desktop permet de configurer l’ensemble du système, activer/désactiver un module et afficher/acquitter une notification.

## Documentation du code

https://btssn-lasalle-84.github.io/domotifications-2023/

## Versions

![](images/livraisons.png)

### 0.2

![](images/jira-tickets-v0.2.png)

![](images/screenshot-qt-domotifications-v0.2.png)

### 0.1

![](images/jira-tickets-v0.1.png)

## Protocole

- [Protocole HTTP Domotifications.pdf](docs/Protocole%20HTTP%20Domotifications.pdf)

## Auteurs

- Étudiant IR : Alexis VAILLEN ([Station ESP32](station-notifications-lumineuses/README.md))
- Étudiant IR : Mathieu MOYAERTS (Application Qt)

---
©️ LaSalle Avignon 2023
