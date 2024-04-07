/*
	Copyright (c) 2023 Sidhin S Thomas. All rights reserved
*/
#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>

namespace game_menu
{
	typedef struct __menu_context MENU;

	enum class Align
	{
		Left = 0,
		Center = 1,
		Right = 2 
	};

	struct MenuItem
	{
		std::string name;
		std::function<void(sf::RenderTarget&)> action;
	};

	struct ColorScheme
	{
		sf::Color titleColor;
		sf::Color itemColor;
		sf::Color selectedColor;
	};

	struct Padding
	{
		float top;
		float left;
		float bottom;
		float right;
	};

	struct Style
	{
		sf::Font& TitleFont;
		sf::Font& ItemFont;

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

	struct MenuConfig
	{
		std::string title;
		std::vector<MenuItem> items;
		Style style;
	};
} // namespace game_menu

extern "C" 
{
	game_menu::MENU* create_menu_context(sf::RenderWindow& wnd, game_menu::MenuConfig& config);
	void menu_destroy_context(game_menu::MENU* menu);
	void menu_handle_event(game_menu::MENU* menu, sf::Event& event);
	void menu_render(game_menu::MENU* menu);
}
