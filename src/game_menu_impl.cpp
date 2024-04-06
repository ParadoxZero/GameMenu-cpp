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
	reinterpret_cast<game_menu::Menu*>(menu)->HandleEvent(event);
}

void menu_render(game_menu::MENU* menu)
{
	reinterpret_cast<game_menu::Menu*>(menu)->Render();
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

	void Menu::HandleEvent(sf::Event& event)
	{
		const auto itemCount = _items.size();
		if (event.type == sf::Event::KeyPressed) 
		{
			if (event.key.code == sf::Keyboard::Up) 
			{
				_currentlySelectedItem = (_currentlySelectedItem + itemCount - 1) % itemCount;
			}
			else if (event.key.code == sf::Keyboard::Down) 
			{
				_currentlySelectedItem = (_currentlySelectedItem + 1) % itemCount;
			}
			else if (event.key.code == sf::Keyboard::Return) 
			{
				_items[_currentlySelectedItem].Data.action(_window);
			}
		}
	}

	void Menu::Render()
	{
		SetMenu();
		DrawMenu();
	}

	void Menu::WriteText(std::string str, sf::Font* font, unsigned int size, float x, float y, const Color color)
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

	void Menu::SetMenu()
	{
		/* Setting title of menu */
		const auto titleOffsetCoefficient = GetOffsetCoefficient(_style.TitleAlign);

		float titleX = (float)_window.getSize().x * titleOffsetCoefficient;
		float titleY = _style.PaddingTitle.top;
		_titleLocation.X = (titleX + _style.PaddingTitle.left);
		_titleLocation.Y = titleY;

		float menuScreenHeight = _titleLocation.Y + _style.PaddingItems.top;
		float blockHeight = (float)_style.ItemFontSize * _style.MenuItemScaleFactor;
		float offsetCoefficient = GetOffsetCoefficient(_style.ItemAlign);

		const auto x = (float)_window.getSize().x * offsetCoefficient + _style.PaddingItems.left;
		auto y = menuScreenHeight + blockHeight + _style.PaddingItems.top;

		/* Calculating Menu item locations */
		for (auto i = 0; i < _items.size(); ++i)
		{
			_items[i].Location.X = x;
			_items[i].Location.Y = y;
			y += blockHeight;
		}
	}

	void Menu::DrawMenu() 
	{
		WriteText(_title, _style.ItemFont, _style.TitleFontSize, _titleLocation.X, _titleLocation.Y, _style.colorScheme.titleColor);
		game_menu::Color color(_style.colorScheme.itemColor);

		for (auto i = 0; i < _items.size(); ++i)
		{
			color = i == _currentlySelectedItem ? _style.colorScheme.selectedColor : color = _style.colorScheme.itemColor;
			WriteText(_items[i].Data.name, _style.ItemFont, _style.ItemFontSize,_items[i].Location.X, _items[i].Location.Y, color);
		}
	}
}
