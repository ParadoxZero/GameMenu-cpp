/*
	Copyright (c) 2024 Sidhin S Thomas. All rights reserved
*/

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "game_menu/Menu.h"

int main() 
{
	// Creating the SFML RenderWindow object for displaying the example.
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sample Menu Example", sf::Style::Close);
	
	// Loading the font from the example font file.
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// Variable to be captured by action functions below for the example.
	auto isExitRequested = false;

	// This configuration defines the layout and operation of a menu.
	Menu::MenuConfig menuConfig;

	// The items list should have all selectable menu items in the list. Along with each string include a 
	// function pointer to the action you want performed when the menu item is selected. In the example 
	// below we have added 3 menu items with generic names. The third item "Exit" has an example exit method.
	menuConfig.Items =
	{
		// Text and function pointers.
		{ "Menu Item 1", [](sf::RenderTarget& target) {} },
		{ "Menu Item 2", [](sf::RenderTarget& target) {} },
		{ "Exit", [&](sf::RenderTarget& target) { isExitRequested = true; } },
	};

	// The ItemStyle member defines the style to apply to all items in the menu.
	
	// Alignment Defines how the text of menu items is aligned. Center is the default.
	menuConfig.ItemStyle.Alignment = Menu::Align::Center;
	// Color to use for menu items that are not selected.
	menuConfig.ItemStyle.Color = sf::Color::Blue;

	// Font to use for menu item text.
	menuConfig.ItemStyle.Font = font;

	// Size of the menu item font in points.
	menuConfig.ItemStyle.FontSize = 24;

	// Padding for menu item text in pixels.
	menuConfig.ItemStyle.Padding.Bottom = 10.0f;
	menuConfig.ItemStyle.Padding.Left = 10.0f;
	menuConfig.ItemStyle.Padding.Right = 10.0f;
	menuConfig.ItemStyle.Padding.Top = 10.0f;

	// The color to use when a menu item is selected.
	menuConfig.SelectedItemColor = sf::Color::Cyan;

	// The TitleStyle member defines the style to apply to the title.

	// Gives the alignment of the title.
	menuConfig.TitleStyle.Alignment = Menu::Align::Center;

	// Color to use for the title text.
	menuConfig.TitleStyle.Color = sf::Color::Green;

	// Font to use for title text.
	menuConfig.TitleStyle.Font = font;

	// Size of the title font in points.
	menuConfig.TitleStyle.FontSize = 36;

	// Padding for title text in pixels.
	menuConfig.TitleStyle.Padding.Bottom = 20.0f;
	menuConfig.TitleStyle.Padding.Left = 20.0f;
	menuConfig.TitleStyle.Padding.Right = 20.0f;
	menuConfig.TitleStyle.Padding.Top = 20.0f;

	// Test to use as the title of the menu.
	menuConfig.TitleText = "My Menu Title";
	
	// Use the BuildMenu factory function in the IMenu header. This gives a fully built menu object.
	auto menu = Menu::BuildMenu(window.getSize(), menuConfig);

	// This while loop ill control the menu operation.
	while (window.isOpen()) 
	{
		// The isExitRequested was passed into the "Exit" menu action by reference.
		if (isExitRequested) 
		{
			// When the isExitRequested goes true the user pressed enter on the "Exit" action.
			window.close();
			break;
		}

		// Poll the events from the window.
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			// Handle the closed event here, but pass all other events to the menu since it's displayed.
			if (windowEvent.type == sf::Event::Closed)
			{
				// Just handle this as if the "Exit" entry had been seleced.
				isExitRequested = true;
			}
			else
			{
				// Pass the event to the menu
				menu->HandleEvent(windowEvent, window);
			}
		}

		// Clear the window.
		window.clear();

		// Draw the menu on the window.
		menu->Draw(window);

		// Tell the window to display.
		window.display();
	}

	// Exit from the example.
	return 0;
}
