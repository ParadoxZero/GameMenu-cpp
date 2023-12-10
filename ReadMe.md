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
  * Create A vector of `game_menu::MenuItem`. Which contains the title of the item and Action it will perform.
    
  * Now create a style. `gmenu::Style`
     * It requires two paramenters ( `sf::Font` ) to initialize.
     * `gmenu::Style` can be used to define the look of the menu.
     
     ```cpp
      game_menu::Style style {
          .ItemFont = &font,
          .TitleFont = &font,
          .TitleFontSize = 36,
          .ItemFontSize = 24,
          .MenuTitleScaleFactor = 1,
          .MenuItemScaleFactor = 1.5,
          .ColorScheme = {
            .TitleColor = 0xFFFFFF,
            .ItemColor = 0xFFFFFF,
            .SelectedColor = 0xFF22F1
          },
          .PaddingTitle = {
            .top = 100,
            .left = 0,
          },
          .PaddingItems = {
            .top = 40,
          },
          .TitleAlign = game_menu::Align::Center,
          .ItemAlign = game_menu::Align::Center
        };
     ```
     
  * Now create an context of `Menu`:
    ```cpp
    auto menu_ptr = create_menu_context(w, config);
	  std::unique_ptr<game_menu::MENU, decltype(&menu_destroy_context)> menu(menu_ptr, &menu_destroy_context);
    ```
 
* Now integrate the event handling and render into the event loop - 
```cpp
    while (w.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				is_exit_requested = true;
			}
			menu_handle_event(menu.get(), event);
		}
		w.clear();
		menu_render(menu.get());
		w.display();
```
     

## [Screenshots!](Screenshots.md)

## Dependencies
  * [Simple and Fast Multimedia Library](http://www.sfml-dev.org/index.php)
      
## Installing
Install via cmake's FetchContent script - 
```cmake
FetchContent_Declare(game_menu
    GIT_REPOSITORY https://github.com/ParadoxZero/GameMenu-cpp.git
    GIT_TAG <commit hash>
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(game_menu)

target_link_libraries(mygame PRIVATE game_menu)
```
 
## Contributions
If you are looking to contribute, then feel free to create a pull request.

#### Future Possibilities
* Mouse integration
* Menu style system. Abiity to alter the menu apearance as per need.
  (Create a style object with nessary specifications, which will be passed to the Menu)
* Sound. 
