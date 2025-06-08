#ifndef GMENU_IMPL_H
#define GMENU_IMPL_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "game_menu/game_menu.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <vector>
#include <iostream>

namespace game_menu {

struct coordinates {
    float x = 0;
    float y = 0;
};

struct Item {
    MenuItem data;
    coordinates location;
};

class Menu {
public:
    Menu(sf::RenderTarget &window, MenuConfig config)
        : _window(window), _style(config.style), _title(config.title) {
        _click_sound.setBuffer(config.click_sound_effect);
        _select_sound.setBuffer(config.select_sound_effect);

        for (auto &menu_item : config.items) {
            _items.push_back({menu_item, {0, 0}});
            std::cout << " Processing item " << menu_item.name << std::endl;
        }
        std::cout << "Size of items : " << _items.size() << std::endl;
    }

    void handleEvent(sf::Event &event);
    void render();

private:
    void setMenu();
    void drawMenu();
    void writeText(std::string str, sf::Font *font, unsigned int size, float x,
                   float y, const Color color);

    sf::RenderTarget &_window;
    Style _style;
    std::string _title;
    std::vector<Item> _items;
    coordinates _title_location;
    int _currently_selected_item = 0;

    sf::Sound _click_sound;
    sf::Sound _select_sound;
};

} // namespace game_menu