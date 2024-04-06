#include <iostream>
#include <string>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"

#include "game_menu_impl.h"

game_menu::MENU* create_menu_context(sf::RenderWindow& wnd, game_menu::MenuConfig& config)
{
	return reinterpret_cast<game_menu::MENU*>(new game_menu::Menu(wnd, config));
}

void menu_destroy_context(game_menu::MENU* menu) 
{
	delete reinterpret_cast<game_menu::Menu*>(menu);
}

void menu_handle_event(game_menu::MENU* menu, sf::Event& event)
{
	reinterpret_cast<game_menu::Menu*>(menu)->handleEvent(event);
}

void menu_render(game_menu::MENU* menu)
{
	reinterpret_cast<game_menu::Menu*>(menu)->render();
}

namespace game_menu 
{
	static float GetOffsetCoefficient(const Align& alignment)
	{
		switch (alignment)
		{
		case Align::Left:
			return 0.25f;
		case Align::Right:
			return 0.75f;
		case Align::Center:
		default:
			// Center is the default alignment if unknown.
			return 0.5f;
		}
	}

	void Menu::handleEvent(sf::Event& event)
	{
		auto max_items = _items.size();
		if (event.type == sf::Event::KeyPressed) 
		{
			if (event.key.code == sf::Keyboard::Up) 
			{
				_currently_selected_item = (_currently_selected_item + max_items - 1) % max_items;
			}
			else if (event.key.code == sf::Keyboard::Down) 
			{
				_currently_selected_item = (_currently_selected_item + 1) % max_items;
			}
			else if (event.key.code == sf::Keyboard::Return) 
			{
				_items[_currently_selected_item].data.action(_window);
			}
		}
	}

	void Menu::render()
	{
		setMenu();
		drawMenu();
	}

	void Menu::writeText(std::string str, sf::Font* font, unsigned int size, float x, float y, const Color color)
	{
		sf::Color textColor(color);
		sf::Text text;
		text.setString(str);
		text.setFont(*font);
		text.setFillColor(textColor);
		text.setCharacterSize(size);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.width / 2.0f, 0);

		if (x - textRect.width / 2.0f < 0)
		{
			x = textRect.width / 2 + _style.PaddingTitle.left;
		}

		if (x + textRect.width / 2.0f > _window.getSize().x)
		{
			x = _window.getSize().x - textRect.width / 2 + _style.PaddingTitle.left;
		}

		text.setPosition(sf::Vector2f(x, y));
		_window.draw(text);
	}

	void Menu::setMenu()
	{
		/* Setting title of menu */
		const auto titleOffsetCoefficient = GetOffsetCoefficient(_style.TitleAlign);

		float titleX = (float)_window.getSize().x * titleOffsetCoefficient;
		float titleY = _style.PaddingTitle.top;
		_title_location.X = (titleX + _style.PaddingTitle.left);
		_title_location.Y = titleY;

		float menu_screen_height = _title_location.Y + _style.PaddingItems.top;
		float block_height = (float)_style.ItemFontSize * _style.MenuItemScaleFactor;
		float offset_coefficient = GetOffsetCoefficient(_style.ItemAlign);

		const auto x = (float)_window.getSize().x * offset_coefficient + _style.PaddingItems.left;
		auto y = menu_screen_height + block_height + _style.PaddingItems.top;

		/* Calculating Menu item locations */
		for (auto i = 0; i < _items.size(); ++i)
		{
			_items[i].location.X = x;
			_items[i].location.Y = x;
			y += block_height;
		}
	}

	void Menu::drawMenu() 
	{
		writeText(_title, _style.ItemFont, _style.TitleFontSize, _title_location.X, _title_location.Y, _style.colorScheme.titleColor);
		game_menu::Color color(_style.colorScheme.itemColor);

		for (auto i = 0; i < _items.size(); ++i)
		{
			color = i == _currently_selected_item ? _style.colorScheme.selectedColor : color = _style.colorScheme.itemColor;
			writeText(_items[i].data.name, _style.ItemFont, _style.ItemFontSize,_items[i].location.X, _items[i].location.Y, color);
		}
	}
}
