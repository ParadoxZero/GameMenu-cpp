/*
*	Copyright (C) 2016 Sidhin S Thomas
*
*	This software is licensed under the MIT License
*/

#include <GameMenu/GameMenu.h>

namespace gmenu {


	/*==================================================*
	*				public functions					*
	*===================================================*/

	void Menu::setTitle(std::string title) {
		menu_title = title;
	}

	void Menu::setMenuItems(MenuItem *items, int8_t length) {
		menu_items.entries = items;
		menu_items.size = length;
	}


	/* 
	This function constains the main event loop for the menu
	The actions performed : drawMenu() -> pollEvent() -> prefromAction()
	*/
	void Menu::createMenu() {
		setMenu();
		bool cont = true;
		while (window->isOpen() && cont)
		{
			window->clear();
			drawMenu();
			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window->close();
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up) {
						currently_selected_item = (currently_selected_item - 1);
						if (currently_selected_item < 0)
							currently_selected_item = menu_items.size - 1;
					}
					else if (event.key.code == sf::Keyboard::Down) {
						currently_selected_item = (currently_selected_item + 1) % (menu_items.size);
					}
					else if (event.key.code == sf::Keyboard::Return) {
						cont = menu_items.entries[currently_selected_item].action->start();
					}
				}
			} // while( pollEvent )

			window->display();
		} // while window open
	} //create menu



	/*==================================================*
	*				Private Functions					*
	*===================================================*/


	/* Utility function */
	void Menu::writeText(std::string str, sf::Font font, unsigned int size, float x, float y, const sf::Color &color) {
		sf::Text text;
		text.setString(str);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.width / 2.0f,0);
		text.setPosition(sf::Vector2f(x,y));
		window->draw(text);
	} //writeText(...)

	void Menu::setMenu() {

		/* Setting title of menu */
		{
			/* Small scope just to be able to freely use the variable names */
			float x = (float) window->getSize().x / 2, y = 0;
			title_location.x = x;
			title_location.y = y;
		}

		unsigned int menu_screen_height =(int) window->getSize().y * (1 -  MenuTitleScaleFactor);
		unsigned int block_height = (int) menu_screen_height / menu_items.size * MenuItemScaleFactor;
		float x = (float)window->getSize().x / 2;
		float y = (float)window->getSize().y - 0.75 * menu_screen_height + block_height * 1 / 8;
		item_location = new coordinates[menu_items.size];
		/* Calculating Menu item locations */
		for (int8_t i = 0; i < menu_items.size; ++i) {
			item_location[i].x = x;
			item_location[i].y = y;
			y += block_height;
		}
		
	} //setMenu()

	void Menu::drawMenu() {
		writeText(menu_title, style.TitleFont, style.TitleFontSize, title_location.x, title_location.y, style.TitleColor);
		sf::Color color = style.ItemColor;
		for (int i = 0; i < menu_items.size; ++i)
		{
			if (i == currently_selected_item) {
				color = style.Selected;
			}
			writeText(menu_items.entries[i].title, style.ItemFont, style.ItemFontSize, item_location[i].x, item_location[i].y, color);
			color = style.ItemColor;
		}

	} //drawMenu()


} // namespace sui