#include "game_menu_impl.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>

game_menu::MENU *create_menu_context(sf::RenderWindow &wnd,
                                     game_menu::MenuConfig &config) {
    return reinterpret_cast<game_menu::MENU *>(new game_menu::Menu(wnd, config));
}

void menu_destroy_context(game_menu::MENU *menu) {
    delete reinterpret_cast<game_menu::Menu *>(menu);
}

void menu_handle_event(game_menu::MENU *menu, sf::Event &event) {
    reinterpret_cast<game_menu::Menu *>(menu)->handleEvent(event);
}

void menu_render(game_menu::MENU *menu) {
    reinterpret_cast<game_menu::Menu *>(menu)->render();
}

namespace game_menu {

void Menu::handleEvent(sf::Event &event) {
    auto max_items = _items.size();

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            _currently_selected_item = (_currently_selected_item + max_items - 1) % max_items;
            _click_sound.play();
        } else if (event.key.code == sf::Keyboard::Down) {
            _currently_selected_item = (_currently_selected_item + 1) % max_items;
            _click_sound.play();
        } else if (event.key.code == sf::Keyboard::Return) {
            _items[_currently_selected_item].data.action(_window);
            _select_sound.play();
        }
    }
}

void Menu::render() {
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
        x = textRect.width / 2 + _style.PaddingTitle.left;
    }
    if (x + textRect.width / 2.0f > _window.getSize().x) {
        x = _window.getSize().x - textRect.width / 2 + _style.PaddingTitle.left;
    }
    text.setPosition(sf::Vector2f(x, y));
    _window.draw(text);
}

void Menu::setMenu() {
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
    float x = (float)_window.getSize().x * offset_coefficient ,
          y = _style.PaddingTitle.top;
    _title_location.x = (x + _style.PaddingTitle.left);
    _title_location.y = y;

    float menu_screen_height = _title_location.y + _style.PaddingItems.top;
    float block_height = (float)_style.ItemFontSize * _style.MenuItemScaleFactor;

    float offset_coefficient_items = 0.5;
    switch (_style.ItemAlign) {
    case Align::Center:
        offset_coefficient_items = 0.5;
        break;
    case Align::Left:
        offset_coefficient_items = 0.25;
        break;
    case Align::Right:
        offset_coefficient_items = 0.75;
        break;
    }

    float x_items = (float)_window.getSize().x * offset_coefficient_items +
                    _style.PaddingItems.left;
    float y_items = menu_screen_height +
                    block_height + _style.PaddingItems.top;

    for (int8_t i = 0; i < _items.size(); ++i) {
        coordinates crd;
        crd.x = x_items;
        crd.y = y_items;
        _items[i].location = crd;
        y_items += block_height;
    }
}

void Menu::drawMenu() {
    writeText(_title, _style.ItemFont, _style.TitleFontSize, _title_location.x,
              _title_location.y, _style.colorScheme.titleColor);
    game_menu::Color color(_style.colorScheme.itemColor);
    for (int i = 0; i < _items.size(); ++i) {
        if (i == _currently_selected_item) {
            color = _style.colorScheme.selectedColor;
        } else {
            color = _style.colorScheme.itemColor;
        }
        writeText(_items[i].data.name, _style.ItemFont, _style.ItemFontSize,
                  _items[i].location.x, _items[i].location.y, color);
    }
}

} // namespace game_menu
