#ifndef GMENU_IMPL_H
#define GMENU_IMPL_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "game_menu/game_menu.h"

#include "SFML/Graphics.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace game_menu {
    struct Coordinates {
        float x = 0;
        float y = 0;
    };

    struct Item {
        MenuItem data;
        Coordinates location;
    };

    class Menu {
    public:
        Menu(sf::RenderTarget& window, MenuConfig config)
                : _window(window), _style(config.style), _title(config.title) {
            try {
                loadFont();  // Handle font loading, throw exception on failure
                processItems(config.items);
            } catch (const std::exception& e) {
                // Handle initialization failure
                std::cerr << "Menu initialization failed: " << e.what() << std::endl;
            }
        }

        void handleEvent(sf::Event& event);
        void render();

    private:
        void setMenu();
        void drawMenu();
        void writeText(std::string str, sf::Font* font, unsigned int size, float x,
                       float y, const Color color);

        void loadFont() {
            // Implement font loading logic, throw std::runtime_error on failure
            if (!_style.ItemFont->loadFromFile("path/to/your/font.ttf")) {
                throw std::runtime_error("Failed to load font");
            }
        }

        void processItems(const std::vector<MenuItem>& items) {
            for (auto& menu_item : items) {
                _items.push_back({ menu_item, {0, 0} });
                std::cout << " Processing item " << menu_item.name << std::endl;
            }
            std::cout << "Size of items : " << _items.size() << std::endl;
        }

        sf::RenderTarget& _window;
        Style _style;
        std::string _title;
        std::vector<Item> _items;
        Coordinates _title_location;
        int _currently_selected_item = 0;
    };
} // namespace game_menu

#endif // GMENU_IMPL_H
