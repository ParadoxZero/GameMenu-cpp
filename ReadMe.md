# GameMenu 

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5d324ea6258443a99146a2af7cc38aca)](https://www.codacy.com/app/ParadoxZero/GameMenu-cpp?utm_source=github.com&utm_medium=referral&utm_content=ParadoxZero/GameMenu-cpp&utm_campaign=badger)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)   ![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square)   [![Build Status](https://travis-ci.org/ParadoxZero/GameMenu-cpp.svg?branch=master)](https://travis-ci.org/ParadoxZero/GameMenu-cpp)  

 
This is a C++ library to help create Menu UI for games based of sfml. It provides simple and direct pathways to create Menu, add action to it etc.

## How to use?
The main purpose of the library is to make creation of menu's in games easy. This achieves it by dividing the Menu into two parts:
  * UI - Options to display
  * Function - The action to perform
 
#### To use the library
  
  * First Need to decide the menu items, ie the options available (eg Start, Exit, Highscore etc)
  * Create A vector of `gmenu::MenuItem`. Which contains the title of the item and Action it will perform.
  
  The definition of `gmenu::MenuItem` is:
    
    ```cpp
       struct MenuItem {
           std::shared_ptr<Action> action;
           std::string title;
       };
    ```
    
     Here `gmenu::Action` is an abstract Class that acts as an interface.
     The virtual method `bool DerivedAction::start()` will be called by the Menu when that item is selected.
    
 
* Now create a style. `gmenu::Style`
     * It requires two paramenters ( `sf::Font` ) to initialize.
     * `gmenu::Style` can be used to define the look of the menu.
     
     ```cpp
      sf::Font &TitleFont;
      sf::Font &ItemFont;

      sf::Color TitleColor = sf::Color::Green;;
      sf::Color ItemColor = sf::Color::Red ;
      sf::Color Selected = sf::Color::Blue; 

      unsigned int TitleFontSize = 50;
      unsigned int ItemFontSize = 20;
      
      float MenuItemScaleFactor = 0.25; // This determines the distance between options. 
      
      int layout = Layout::Default; // Bitflag, Defines the layout of menu. eg. Layout::ItemLeft| Layout::TitleCentre

      struct {
       signed int top, left;
      } PaddingTitle, PaddingItems; // this is the padding that will extra displacement that will always be added.
     ```
     
* Now create an object of `gmenuMenu` which require the following parameters:
  * `sf::RenderWindow` : Where menu is to be created
  * `std::vector<gmenu::MenuItem>` : Vector containing MenuItems.
  * `gmenu::Style`: That defines the style.
 
* Vola, your menu is ready to be used.
     

## [Screenshots!](Screenshots.md)

## Dependencies
  * [Simple and Fast Multimedia Library](http://www.sfml-dev.org/index.php)
      
## Installing
> TODO 
 
## Contributions
If you are looking to contribute, then feel free to create a pull request.

#### Future Possibilities
* Mouse integration
* Menu style system. Abiity to alter the menu apearance as per need.
  (Create a style object with nessary specifications, which will be passed to the Menu)
* Sound. 
