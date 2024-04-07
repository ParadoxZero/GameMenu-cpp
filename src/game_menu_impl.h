#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game_menu/game_menu.h"

namespace game_menu
{
	struct Item
	{
		MenuItem Data;
		sf::Vector2f Location;
	};

	class Menu
	{
	public:
		Menu(sf::RenderTarget& window, const MenuConfig& config);

		void HandleEvent(const sf::Event& event);
		void Render();

	private:
		void SetMenu();
		void DrawMenu();
		void WriteText(const std::string& str, const sf::Font& font, const float& size, const float& x, const float& y, const sf::Color& color);

		sf::RenderTarget& _window;
		Style _style;
		std::string _title;
		std::vector<Item> _items;
		sf::Vector2f _titleLocation;
		std::int32_t _currentlySelectedItem = 0;
	};
}
