/*
	Copyright (c) 2024 Sidhin S Thomas. All rights reserved
*/

#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>

namespace Menu
{
	/// <summary>
	/// Interface for a Menu object.
	/// </summary>
	class IMenu
	{
	public:
		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~IMenu();

		/// <summary>
		/// Draws the built menu on the provided render target.
		/// </summary>
		/// <param name="window">Target to draw on.</param>
		virtual void Draw(sf::RenderTarget& window) = 0;

		/// <summary>
		/// Handles a window event applied to the menu.
		/// </summary>
		/// <param name="event">Received event.</param>
		/// <param name="window">Render target to be passed along for actions tied to menu items.</param>
		virtual void HandleEvent(const sf::Event& event, sf::RenderTarget& window) = 0;
	};

	/// <summary>
	/// Defines alignment options to be applied to containers.
	/// </summary>
	enum class Align
	{
		/// <summary>
		/// Aligns containers to the left of the window.
		/// </summary>
		Left = 0,
		/// <summary>
		/// Aligns containers to the center of the window.
		/// </summary>
		Center = 1,
		/// <summary>
		/// Aligns containers to the right of the window.
		/// </summary>
		Right = 2 
	};

	/// <summary>
	/// Definition of a text menu item.
	/// </summary>
	struct MenuItem
	{
		/// <summary>
		/// Text to appear on the menu item.
		/// </summary>
		std::string Name;

		/// <summary>
		/// Action function to be called when the menu item is selected.
		/// </summary>
		std::function<void(sf::RenderTarget&)> Action;
	};

	/// <summary>
	/// Container to store padding values.
	/// </summary>
	struct Padding
	{
		/// <summary>
		/// Padding to apply to the bottom of the container.
		/// Units in pixels.
		/// </summary>
		float Bottom = 0.0f;

		/// <summary>
		/// Padding to apply to the left of the container.
		/// Units in pixels.
		/// </summary>
		float Left = 0.0f;

		/// <summary>
		/// Padding to apply to the right of the container.
		/// Units in pixels.
		/// </summary>
		float Right = 0.0f;

		/// <summary>
		/// Padding to apply to the top of the container.
		/// Units in pixels.
		/// </summary>
		float Top = 0.0f;
	};

	/// <summary>
	/// Style definition of a menu item.
	/// </summary>
	struct Style
	{
		/// <summary>
		/// Alignment of the menu item text.
		/// </summary>
		Align Alignment = Align::Center;

		/// <summary>
		/// Standard color of menu item text.
		/// </summary>
		sf::Color Color;

		/// <summary>
		/// Font to use for the menu item text.
		/// </summary>
		sf::Font Font;

		/// <summary>
		/// Font size to use for menu item text.
		/// </summary>
		std::uint32_t FontSize = 8;

		/// <summary>
		/// Padding to use for menu item text.
		/// </summary>
		Padding Padding;
	};

	/// <summary>
	/// Configuration container of the menu.
	/// </summary>
	struct MenuConfig
	{
		/// <summary>
		/// List of the menu items to be in the menu.
		/// </summary>
		std::vector<MenuItem> Items;

		/// <summary>
		/// Style to apply to all Items.
		/// </summary>
		Style ItemStyle;

		/// <summary>
		/// Color to apply to items when they are actively selected.
		/// </summary>
		sf::Color SelectedItemColor;

		/// <summary>
		/// Style to apply to title.
		/// </summary>
		Style TitleStyle;

		/// <summary>
		/// Text to use on the title.
		/// </summary>
		std::string TitleText;
	};

	/// <summary>
	/// Factory function to build a Menu interface reference.
	/// </summary>
	/// <param name="windowSize">Overall size of the window.</param>
	/// <param name="menuConfig">Configuration of the menu.</param>
	/// <returns>Menu instance.</returns>
	std::shared_ptr<IMenu> BuildMenu(const sf::Vector2u& windowSize, const MenuConfig& menuConfig);
}
