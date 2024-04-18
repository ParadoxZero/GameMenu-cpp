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
	sf::Text BuildText(const std::string& text, const Style& textStyle, const sf::Vector2u& windowSize, const float& scalingFactor, const float& yHeight);

	IMenu::~IMenu() {}

	MenuImpl::MenuImpl(const MenuConfig& config, const sf::Vector2u& windowSize)
		: _selectedColor(config.SelectedItemColor)
		, _unselectedColor(config.ItemStyle.Color)
		, _config(config)
	{
		_title = BuildText(config.TitleText, config.TitleStyle, windowSize, config.ScalingFactor, 0.0);

		auto y = (config.TitleStyle.Padding.Top * config.ScalingFactor) + _title.getGlobalBounds().height + (config.TitleStyle.Padding.Bottom * config.ScalingFactor);
		for (auto& item : config.Items)
		{
			auto text = BuildText(item.Name, config.ItemStyle, windowSize, config.ScalingFactor, y);
			_items.push_back(std::make_pair(text, item.Action));

			y += (config.ItemStyle.Padding.Top * config.ScalingFactor) + text.getGlobalBounds().height + (config.ItemStyle.Padding.Bottom * config.ScalingFactor);
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
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2f mouseClickPosition(event.mouseButton.x, event.mouseButton.y);
			for (size_t i = 0; i < _items.size(); ++i)
			{
				if (_items[i].first.getGlobalBounds().contains(mouseClickPosition))
				{
					_currentlySelectedItem = i;
					_items[_currentlySelectedItem].second(window);
				}
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2f mousePosition(event.mouseMove.x, event.mouseMove.y);
			for (size_t i = 0; i < _items.size(); ++i)
			{
				if (_items[i].first.getGlobalBounds().contains(mousePosition))
				{
					_currentlySelectedItem = i;
				}
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

	sf::Text BuildText(const std::string& text, const Style& textStyle, const sf::Vector2u& windowSize, const float& scalingFactor, const float& yHeight)
	{
		sf::Text sfText(text, textStyle.Font, (std::uint32_t)(textStyle.FontSize * scalingFactor));
		sfText.setColor(textStyle.Color);

		auto x = textStyle.Padding.Left * scalingFactor;
		if (textStyle.Alignment == Align::Center)
		{
			// The x position of the text is the mid point of the window, minus half the width of the text box including padding. Then the padding for the left 
			// must be added back for the proper left indentation.
			const auto totalTextLength = (textStyle.Padding.Left * scalingFactor) + sfText.getGlobalBounds().width + (textStyle.Padding.Right * scalingFactor);
			x = (windowSize.x / 2.0) - (totalTextLength / 2.0) + (textStyle.Padding.Left * scalingFactor);
		}
		else if (textStyle.Alignment == Align::Right)
		{
			// The x position of the text is the right border of the window minus the full width of the text with the padding.
			x = windowSize.x - (textStyle.Padding.Right * scalingFactor) - sfText.getGlobalBounds().width - (textStyle.Padding.Left * scalingFactor);
		}

		const auto y = yHeight + (textStyle.Padding.Top * scalingFactor);
		sfText.setPosition(x, y);

		return sfText;
	}

	std::shared_ptr<IMenu> BuildMenu(const sf::Vector2u& windowSize, const MenuConfig& menuConfig)
	{
		return std::make_shared<MenuImpl>(menuConfig, windowSize);
	}
}
