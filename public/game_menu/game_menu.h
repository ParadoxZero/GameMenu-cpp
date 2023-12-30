/*
    Copyright (c) 2023 Sidhin S Thomas. All rights reserved
*/
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Graphics.hpp>

#include <functional>
#include <string>

namespace game_menu {

typedef struct __menu_context MENU;

typedef uint32_t Color;

enum Align { Left = 0, Center = 1, Right = 2 };

struct MenuItem {
  std::string name;
  std::function<void(sf::RenderTarget &)> action;
};

struct ColorScheme {
  Color titleColor;
  Color itemColor;
  Color selectedColor;
};

struct Padding {
  int top;
  int left;
  int bottom;
  int right;
};

struct Style {
  sf::Font *TitleFont;
  sf::Font *ItemFont;

  uint32_t TitleFontSize;
  uint32_t ItemFontSize;

  float MenuTitleScaleFactor;
  float MenuItemScaleFactor;

  ColorScheme colorScheme;

  Padding PaddingTitle;
  Padding PaddingItems;

  Align TitleAlign;
  Align ItemAlign;
};

struct MenuConfig {
  std::string title;
  std::vector<MenuItem> items;
  Style style;
};

} // namespace game_menu

extern "C" {

game_menu::MENU* create_menu_context(sf::RenderWindow &wnd, game_menu::MenuConfig &config);
void menu_destroy_context(game_menu::MENU* menu);
void menu_handle_event(game_menu::MENU* menu, sf::Event &event);
void menu_render(game_menu::MENU* menu);

}