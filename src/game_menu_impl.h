#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "game_menu/game_menu.h"

namespace game_menu
{
	struct Coordinates
	{
		float X = 0;
		float Y = 0;
	};

	struct Item
	{
		MenuItem Data;
		Coordinates Location;
	};

	class Menu
	{
	public:
		Menu(sf::RenderTarget& window, MenuConfig config)
			: _window(window)
			, _style(config.style)
			, _title(config.title)
		{
			for (auto& menu_item : config.items)
			{
				_items.push_back({ menu_item, {0, 0} });
				std::cout << " Processing item " << menu_item.name << std::endl;
			}

			std::cout << "Size of items : " << _items.size() << std::endl;
		}

		void HandleEvent(sf::Event& event);
		void Render();

	private:
		void SetMenu();
		void DrawMenu();
		void WriteText(std::string str, sf::Font* font, unsigned int size, float x, float y, const Color color);

		sf::RenderTarget& _window;
		Style _style;
		std::string _title;
		std::vector<Item> _items;
		Coordinates _titleLocation;
		int _currentlySelectedItem = 0;
	};
}
