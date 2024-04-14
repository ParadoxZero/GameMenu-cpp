/*
	Copyright (c) 2024 Sidhin S Thomas. All rights reserved
*/

#include <iostream>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

#include "game_menu/Menu.h"
#include "MenuImpl.h"

namespace Menu 
{
	sf::Text BuildText(const std::string& text, const sf::Font& font, const float& fontSize, const sf::Vector2u& windowSize,
		const sf::Vector2f& basePosition, const float& paddingLeft);
	float GetOffsetCoefficient(const Align& alignment);

	IMenu::~IMenu() {}

	MenuImpl::MenuImpl(const MenuConfig& config, const sf::Vector2u& windowSize)
		: _selectedColor(config.SelectedItemColor)
		, _unselectedColor(config.ItemStyle.Color)
	{
		const auto titleOffsetCoefficient = GetOffsetCoefficient(config.TitleStyle.Alignment);
		const auto titleLocationX = ((float)windowSize.x * titleOffsetCoefficient) + config.TitleStyle.Padding.Left;
		_title = BuildText(config.TitleText, config.TitleStyle.Font, config.TitleStyle.FontSize, windowSize, 
			sf::Vector2f(titleLocationX, config.TitleStyle.Padding.Top), config.TitleStyle.Padding.Left);
		_title.setColor(config.TitleStyle.Color);

		// Calculating Menu item locations. X is constant, Y will be updated for each row.
		const auto offsetCoefficient = GetOffsetCoefficient(config.ItemStyle.Alignment);
		const auto x = ((float)windowSize.x * offsetCoefficient) + config.ItemStyle.Padding.Left;
		auto y = config.TitleStyle.Padding.Top + _title.getGlobalBounds().height + config.TitleStyle.Padding.Bottom + config.ItemStyle.Padding.Top;
		for (auto& item : config.Items)
		{
			auto text = BuildText(item.Name, config.ItemStyle.Font, config.ItemStyle.FontSize, windowSize, sf::Vector2f(x, y), config.ItemStyle.Padding.Left);
			_items.push_back(std::make_pair(text, item.Action));
			y += config.ItemStyle.Padding.Top + text.getGlobalBounds().height + config.ItemStyle.Padding.Bottom;
		}
	}

	MenuImpl::~MenuImpl() {}

	void MenuImpl::HandleEvent(const sf::Event& event, sf::RenderTarget& window)
	{
		if (event.type == sf::Event::KeyPressed) 
		{
			const auto itemCount = _items.size();
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				_currentlySelectedItem = (_currentlySelectedItem + itemCount - 1) % itemCount;
				break;
			case sf::Keyboard::Down:
				_currentlySelectedItem = (_currentlySelectedItem + 1) % itemCount;
				break;
			case sf::Keyboard::Return:
				_items[_currentlySelectedItem].second(window);
				break;
			}
		}
	}

	void MenuImpl::Draw(sf::RenderTarget& window)
	{
		window.draw(_title);
		for (size_t i = 0; i < _items.size(); ++i)
		{
			auto color = i == _currentlySelectedItem ? _selectedColor : _unselectedColor;
			_items[i].first.setColor(color);
			window.draw(_items[i].first);
		}
	}

	sf::Text BuildText(const std::string& text, const sf::Font& font, const float& fontSize, const sf::Vector2u& windowSize,
		const sf::Vector2f& basePosition, const float& paddingLeft)
	{
		sf::Text sfText(text, font, fontSize);
		const auto halfTextBoxWidth = sfText.getLocalBounds().width / 2.0f;
		sfText.setOrigin(halfTextBoxWidth, 0);

		auto textX = basePosition.x;
		if (textX - halfTextBoxWidth < 0)
		{
			textX = halfTextBoxWidth + paddingLeft;
		}
		else if (textX + halfTextBoxWidth > windowSize.x)
		{
			textX = windowSize.x - halfTextBoxWidth + paddingLeft;
		}

		sfText.setPosition(sf::Vector2f(textX, basePosition.y));

		return sfText;
	}

	float GetOffsetCoefficient(const Align& alignment)
	{
		switch (alignment)
		{
		case Align::Left:
			return 0.25f;
		case Align::Right:
			return 0.75f;
		case Align::Center:
		default: // Center is the default alignment if unknown.
			return 0.5f;
		}
	}

	std::shared_ptr<IMenu> BuildMenu(const sf::Vector2u& windowSize, const MenuConfig& menuConfig)
	{
		return std::make_shared<MenuImpl>(menuConfig, windowSize);
	}
}
