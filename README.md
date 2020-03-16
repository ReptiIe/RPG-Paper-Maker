# RPG Paper Maker

[![Build](https://travis-ci.org/RPG-Paper-Maker/RPG-Paper-Maker.svg?branch=develop)](https://travis-ci.org/RPG-Paper-Maker/RPG-Paper-Maker)
[![Build](https://ci.appveyor.com/api/projects/status/iee74loc36pu1r0t?svg=true)](https://ci.appveyor.com/project/Wano-k/rpg-paper-maker)
[![Join to the community at https://discordapp.com/invite/QncEnCE](https://img.shields.io/badge/Discord-RPG%20Paper%20Maker%20Community-blueviolet?logo=discord)](https://discordapp.com/invite/QncEnCE)

## Overview

RPG Paper Maker is a game making engine, free for non commercial use, allowing you to create a 3D universe with many 2D sprites and even 3D objects using a simple interface for all available platforms: Windows, Linux, and MacOS.

## :open_file_folder: Project organization

The [organization](https://github.com/RPG-Paper-Maker) contains some independent repositories. If you want to fork several repositories, **you should put them all in the same parent root**. Example:

```bash
--- RPM                    <- A parent folder containing all your repos
    |--- RPG-Paper-Maker   <- The engine repo that will use infos from your local Game-Scripts repo
    |--- Game-Scripts      <- The repo editing game scripts
    |--- ... (other repos)
```

- [RPG-Paper-Maker](https://github.com/RPG-Paper-Maker/RPG-Paper-Maker) is the game editor software (RPG Paper Maker). It is entirely written in `C++` and is managing all the `json` files linked to a project such as maps, statistics...
- [Game-Scripts](https://github.com/RPG-Paper-Maker/Game-Scripts) is all the stuff needed for building a game (mainly Javascript scripts). We are using the executable and scripts in order to create a fresh new project in the software. This program is using `QML` and `Javascript`. It is also interpreting all the `json` files that are generated by the RPG Paper Maker engine.
- [Game-documentation](https://github.com/RPG-Paper-Maker/Game-documentation) contains all the stuff for generating javascript game documentation for users.
- [Basic-Ressources](https://github.com/RPG-Paper-Maker/Basic-Ressources) contains all the basic ressources that the users can use for there projects (pictures, musics...).
- [Updater](https://github.com/RPG-Paper-Maker/Updater) is the updater that installs and check for RPG Paper Maker updates.

## How to build the project

- Install Qt on your OS with
[the Open Source installation](https://www.qt.io/download-open-source/#section-2). During the installation, you should select the most recent Qt version (**/!\ Linux users should use Qt5.8 for having musics working**). We recommend you to use the QtCreator IDE too. You should also install gcc compiler if it is not already done.
- Clone and go to this repo
- Update the modules with the command:

Linux:

```bash
./update-mods
```

Windows:

```bash
./update-mods.bat
```

> **NOTE**: You should run this script when you want to update the recent dev changes for Basic Ressources and Game Scripts. This will first search your local changes, and then module github repo if you didn't clone it.

- Open QtCreator
- Open the `RPG-Paper-Maker.pro` file.
- Run qmake (right click on project root).
- Select the project to run (EditorApp or Test) in the bottom-left configuration pop-up
- Build and run the project

If you are having any error that means that you are missing a package. Check the error and try to find out what's missing. Please report any kind of error at Wanok.rpm@gmail.com to help other contributors.

## :mortar_board: Project structure

### Folder Tree

```bash
--- RPG-Paper-Maker
    |--- RPG-Paper-Maker.pro            <- The .pro for opening the project with Qt Creator
    |--- update-mods / update-mods.bat  <- Script for copying dev changes done in other git repos
    |--- versions.json / trees.json     <- Json used by the updater for checking files to update
    |--- .appveyor.yml / .travis.yml    <- Automated build tests
    |--- Editor
    |--- Editor.pro                     <- The sub-project to build the editor library
    |--- ressources.qrc                 <- Linking all the ressources (shaders, images...) used in the editor
    |--- Content                        <- Content is a folder that will contain all the stuff that needs to be copied in the build folder
        |--- basic                      <- The basic Content folder to copy when creating a new project
    |--- Controls                       <- Controllers used for complex dialog boxes or widgets / panels. Should contain all the actions to do on the dialog model
        |--- MapEditor                  <- The map editor controller separated in several files
    |--- CustomWidgets                  <- All the common custom widgets that can be re-used often are here. These components inherit from QWidget classes.
    |--- Dialogs                        <- All the dialog boxes
        |--- Commands                   <- All the dialog boxes used for object event commands
        |--- SpecialElements            <- All the dialog boxes used for special elements (autotiles, walls, 3D objects)
        |--- Systems                    <- All the dialog boxes used for system elements (SuperListItem classes)
    |--- Enums                          <- All the enumerations
    |--- MapEditor                      <- All the map editor models (sprite, floor, etc.)
        |--- Map                        <- The map model (separated in several files)
    |--- MathUtils                      <- Copy of math utils from an old Qt version for 3D drawings
    |--- Models                         <- All the models used for the database
        |--- GameDatas                  <- All the gamedata files models
        |--- System                     <- All the models used for system elements (SuperListItem classes)
    |--- Ressources                     <- All the images (icons) used for the editor
    |--- Shaders                        <- All the shaders programs
    |--- Singletons                     <- Contains RPM singleton
    |--- Themes                         <- All the themes of the editor
    |--- EditorApp
    |--- EditorApp.pro                  <- The sub-project to build the editor executable
    |--- main.cpp                       <- The main function instructions
    |--- Test
    |--- Test.pro                       <- The sub-project to build the test executable
```

### RPM Singleton

`RPM` singleton is used for storing constants such as fix paths, integer values, etc. It also stores pointers to the current opened project and engine settings in order to have an access to it at any time in the program. Common functions are also available. For example, a function to write a `Serializable` class in a .json file is available.

### :sparkles: UI design

We are using the Qt creator designer for generating XML files for all the widgets. These files have a .ui extension.

### SuperListItem

The `SuperListItem` class is used for being displayed with `PanelSuperList` or `WidgetSuperTree`, and stored easily in .json files. It has at least an ID and a name. For example, a monster in a game is a `SuperListItem` (`SystemMonster` class).

A list of `SuperListItem` will be stored in a `QStandardItemModel` model class. Here is a common way to add a `SuperListItem` to a model list:

```bash
    QStandardItem * item = new QStandardItem();
    SuperListItem* super = new SuperListItem(i, "My item"); // COuld be SystemItem class for example
    item->setData(QVariant::fromValue(reinterpret_cast<quintptr>(super)));
    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    item->setText(super->toString());
    model->invisibleRootItem()->appendRow(item);
```

## :construction_worker: Contributing

Thank you for considering contributing to the RPM! Just see our [Contributing Guide](.github/CONTRIBUTING.md).

### :innocent: Code of Conduct

In order to ensure that the CodeZipCore community is welcoming to all, please review and abide by the [Code of Conduct](.github/CODE_OF_CONDUCT.md).

## :mega: Feature requests

Check out the [feathub](https://feathub.com/RPG-Paper-Maker/RPG-Paper-Maker) for voting for your favorite next coming soon feature or even proposing your own one!

[![Feature Requests](http://feathub.com/RPG-Paper-Maker/RPG-Paper-Maker?format=svg)](http://feathub.com/RPG-Paper-Maker/RPG-Paper-Maker)
