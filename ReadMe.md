#GameMenu 

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)   ![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square)   [![Build Status](https://travis-ci.org/ParadoxZero/GameMenu-cpp.svg?branch=master)](https://travis-ci.org/ParadoxZero/GameMenu-cpp)  

 
This is a C++ library to help create Menu UI for games based of sfml. It provides simple and direct pathways to create Menu, add action to it etc.

##How to use?
The main purpose of the library is to make creation of menu's in games easy. This achieves it by dividing the Menu into two parts:
  * UI - Options to display
  * Function - The action to perform
 
####To use the library
  
  * First create a `gmenu::Menu` object, the will constructor need:
  
    * `sf::Renderwindow *` the main screen where Menu will be displayed.
    *  `std::string` Menu title - The main heading of menu
    *  `sf::Font` The font title will be displayed in
    *  `gmenu::MenuItems *` This is an pointer to array of **MenuItem - the structure representing a menu option**.
      
      ```cpp
        struct MenuItem {
          Action *action;
          std::string title;
          sf::Font font;
        };
      ```
        Here `Action` is an **abstract class** with one virtual method `bool start` This is where you will implement the action to be performed when the option is selected.
        
*  `menu.createMenu()` to start the menu
     

##Dependencies
  * [Simple and Fast Multimedia Library](http://www.sfml-dev.org/index.php)
  
    * ####How to install on linux
      
      ```
        $ sudo apt-get install libsfml-dev
      ```
      
    * ####How to install in Windows (visual studio)
    
      * Download the binaries from [sfml](http://www.sfml-dev.org/download.php)
      * Open project settings
      * In c/c++ option
      * Add new include dir as `<Path to sfml>/include`
      * In linker additional external libraries
      * Add `<path to sfml>/lib`
      
##Installing

####Linux
  
* Clone/Download source
* Go to Project dir
  eg:

  ```
    $ cd GameMenu
  ```

* type

  ```
    $ make
  ```

* Now copy the contents of `GameMenu/include` to your project's **include directory**.
* Copy `lib/libGameMenu.a` to your projects **lib directory**.
* Include the path `/path/to/GameMenu/include/` within you project.
* Now you can use the GameMenu by linking `bin/libGameMenu.a` to your executable.

  eg
    ```
      $ g++ your_source.cpp -I./include -o your_output.o
      $ g++ your_output.o -L./lib -lGameMenu -o your_executable
    ```
 
####Windows (Visual Studio)
 
 * Clone/Download the GameMenu
 * Build for the required platform
 * Copy the content of `GameMenu/include` to your folder's **include directory**.
 * Copy the *.lib* `GameMenu.lib` to your projects **lib directory**.
 * Add the GameMenu.lib to your linker input files list.
 * Build and enjoy.
 
 
 ##Contributions
 If you are looking to contribute, then feel free to create a pull request.
 
 ####Future Possibilities
  * Mouse integration
  * Menu style system. Abiity to alter the menu apearance as per need.
    (Create a style object with nessary specifications, which will be passed to the Menu)
  * Sound. 
