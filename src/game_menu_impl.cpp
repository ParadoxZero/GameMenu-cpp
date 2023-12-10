/*

*/

#include "game_menu_impl.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"

#include <string>

game_menu::MENU create_menu_context(sf::RenderWindow &wnd,
                                    game_menu::MenuConfig &config) {
  return reinterpret_cast<game_menu::MENU>(new game_menu::Menu(wnd, config));
}

void destroy_menu_context(game_menu::MENU menu) {
  delete reinterpret_cast<game_menu::Menu *>(menu);
}

void handle_event(game_menu::MENU menu, sf::Event &event) {
  reinterpret_cast<game_menu::Menu *>(menu)->handleEvent(event);
}

namespace game_menu {

void Menu::handleEvent(sf::Event &event) {
  auto max_items = _items.size();
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up) {
      _currently_selected_item =
          (_currently_selected_item + max_items - 1) % max_items;
    } else if (event.key.code == sf::Keyboard::Down) {
      _currently_selected_item = (_currently_selected_item + 1) % max_items;
    } else if (event.key.code == sf::Keyboard::Return) {
      _items[_currently_selected_item].item_data.action(_window);
    }
  }
  setMenu();
  drawMenu();
}

void Menu::writeText(std::string str, sf::Font *font, unsigned int size,
                     float x, float y, const Color color) {
  sf::Color textColor(color);
  sf::Text text;
  text.setString(str);
  text.setFont(*font);
  text.setFillColor(textColor);
  text.setCharacterSize(size);
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.width / 2.0f, 0);
  if (x - textRect.width / 2.0f < 0) {
    // std::cout << x << " " << textRect.width / 2.0f;
    x = textRect.width / 2 + _style.PaddingTitle.left;
  }
  if (x + textRect.width / 2.0f > _window.getSize().x) {
    // std::cout << x << " " << textRect.width / 2.0f;
    x = _window.getSize().x - textRect.width / 2 + _style.PaddingTitle.left;
  }
  text.setPosition(sf::Vector2f(x, y));
  _window.draw(text);
} // writeText(...)

void Menu::setMenu() {

  //   std::cout << "screen size:" << window.getSize().x << " " <<
  //   window.getSize().y
  //             << std::endl;

  /* Setting title of menu */
  {
    /* Small scope just to be able to freely use the variable names */
    float offset_coefficient = 0.5;

    switch (_style.TitleAlign) {
    case Align::Center:
      offset_coefficient = 0.5;
      break;
    case Align::Left:
      offset_coefficient = 0.25;
      break;
    case Align::Right:
      offset_coefficient = 0.75;
      break;
    }
    float x = (float)_window.getSize().x * offset_coefficient,
          y = _style.PaddingTitle.top;
    _title_location.x = (x + _style.PaddingTitle.left);
    _title_location.y = y;
  }

  float menu_screen_height =
      _window.getSize().y - _title_location.y + _style.PaddingItems.top;
  float block_height =
      (float)menu_screen_height / _items.size() * _style.MenuItemScaleFactor;

  float offset_coefficient = 0.5;
  switch (_style.ItemAlign) {
  case Align::Center:
    offset_coefficient = 0.5;
    break;
  case Align::Left:
    offset_coefficient = 0.25;
    break;
  case Align::Right:
    offset_coefficient = 0.75;
    break;
  }

  float x = (float)_window.getSize().x * offset_coefficient +
            _style.PaddingItems.left;
  float y = ((float)_window.getSize().y) - 0.75 * menu_screen_height +
            block_height * 1 / 8;
  /* Calculating Menu item locations */
  for (int8_t i = 0; i < _items.size(); ++i) {
    coordinates crd;
    crd.x = x;
    crd.y = y;
    _items[i].location = crd;
    y += block_height;
  }

} // setMenu()

void Menu::drawMenu() {
  writeText(_title, _style.ItemFont, _style.TitleFontSize, _title_location.x,
            _title_location.y, _style.ColorScheme.TitleColor);
  game_menu::Color color(_style.ColorScheme.ItemColor);
  for (int i = 0; i < _items.size(); ++i) {
    if (i == _currently_selected_item) {
      color = _style.ColorScheme.SelectedColor;
    }
    writeText(_items[i].item_data.name, _style.ItemFont, _style.ItemFontSize,
              _items[i].location.x, _items[i].location.y, color);
    color = _style.ColorScheme.ItemColor;
  }

} // drawMenu()

} // namespace game_menu