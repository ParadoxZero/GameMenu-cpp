/*
	Copyright (c) 2024 Sidhin S Thomas. All rights reserved
*/

#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "game_menu/Menu.h"

namespace Menu
{
	class MenuImpl : public IMenu
	{
	public:
		MenuImpl(const MenuConfig& config, const sf::Vector2u& windowSize);
		virtual ~MenuImpl();

		void Draw(sf::RenderTarget& window) override;
		void HandleEvent(const sf::Event& event, sf::RenderTarget& window) override;

	private:
		const sf::Color _selectedColor;
		const sf::Color _unselectedColor;

		sf::Text _title;
		std::vector<std::pair<sf::Text, std::function<void(sf::RenderTarget&)>>> _items;
		
		size_t _currentlySelectedItem = 0;
	};
}
