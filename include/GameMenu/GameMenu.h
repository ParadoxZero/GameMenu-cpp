/*
*	Copyright (C) 2016 Sidhin S Thomas
*
*	This software is licensed under the MIT License
*/

#ifndef SS_USER_INTERFACE
#define SS_USER_INTERFACE


/*--- Headers ---*/
#include <SFML/Graphics.hpp>
namespace gmenu {

	
	/* Simple abstract class interface to implement Actions */
	class Action {
	public:
		/* The function that will be called by the menu
		Depending on the return value of start() the menu will close
		- If start() return true : menu will not close
		- If start() return false: menu will close

		usefull when you need to implement a feature after which it should not return to the menu.
		eg. Back/Exit/Game Mode etc.
		*/
		virtual bool start() = 0;
	};

	struct MenuItem {
		Action *action;
		std::string title;
	};

	enum Layout {
		TitleCentre,
		TitleRight,
		TitleLeft,

		ItemCentre,
		ItemRight,
		ItemLeft,

	};

	struct Style {
		sf::Font TitleFont;
		sf::Font ItemFont;
		sf::Color TitleColor;
		sf::Color ItemColor;
		sf::Color Selected;
		unsigned int TitleFontSize;
		unsigned int ItemFontSize;
		Layout layout;
		Style() {
			TitleColor = sf::Color::Green;
			ItemColor = sf::Color::Red;
			Selected = sf::Color::Blue;
			ItemFontSize = 20;
			TitleFontSize = 50;
		}
	};


	


	class Menu {
		/* Generic Menu - can be instantiated to generate a custom menu as needed over a sf::RenderWindow */

	public:
		
		/* Only accesible constructor */
		Menu(sf::RenderWindow *window, std::string title, MenuItem* items, int8_t length, Style style) 
			: Menu(window, title) {
			setMenuItems(items, length);
			this->style = style;
		}

	

	    /* This method is will start the menu and handover the screen control to it.
		The Event loop will be controlled by this function after the call, and 
		only after Back/exit on the menu will the control be returned.

		The control is returned when an "gmenu::Action" object is called
		whose start return "false" */
		void createMenu();

		/* In case menu items needs to be changed */
		void setMenuItems(MenuItem *, int8_t);
		
		/* In case the title needs to be changed */
		void setTitle(std::string title);
		

	private:
		
		Menu( sf::RenderWindow *wnd ) {
			window = wnd;
		}

		
		Menu( sf::RenderWindow *window, std::string title ) : Menu( window ) {
			setTitle( title);
		}

		void writeText( std::string string, sf::Font font, unsigned int size, float x, float y,
			const sf::Color &color);

		void setMenu();

		void drawMenu();


		/*==================================================*
		*				Internal structuers        			*
		*===================================================*/

		struct {
			MenuItem *entries;
			int8_t size;
		} menu_items;

		struct coordinates {
			coordinates() {
				x = y = 0.f;
			}
			float x;
			float y;
		} *item_location, title_location;


		/*==================================================*
		*					Data Members					*
		*===================================================*/

		int currently_selected_item = 0;

		Style style;
		
		sf::RenderWindow *window;
		std::string menu_title;

		// TODO: create an interface to set these
		float MenuTitleScaleFactor = 0.125;
		float MenuItemScaleFactor = 0.25;

	}; // Menu

} // namespace sui
#endif