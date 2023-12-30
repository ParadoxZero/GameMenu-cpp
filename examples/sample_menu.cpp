#include "game_menu/game_menu.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

int main() {
	sf::RenderWindow w( sf::VideoMode( 800, 600 ), "Sample Title", sf::Style::Close);
	
	sf::Font font;
	font.loadFromFile( "sansation.ttf" );
	game_menu::Style style {
		.TitleFont = &font,
		.ItemFont = &font,
		.TitleFontSize = 36,
		.ItemFontSize = 24,
		.MenuTitleScaleFactor = 1,
		.MenuItemScaleFactor = 1.5,
		.colorScheme = {
			.titleColor = 0xFFFFFF,
			.itemColor = 0xFFFFFF,
			.selectedColor = 0xFF22F1
		},
		.PaddingTitle = {
			.top = 100,
			.left = 0,
		},
		.PaddingItems = {
			.top = 40,
		},
		.TitleAlign = game_menu::Align::Center,
		.ItemAlign = game_menu::Align::Center
	};

	bool is_exit_requested = false;

	std::vector<game_menu::MenuItem> items {
		{ "New Game", [](sf::RenderTarget &target) {}},
		{ "Load Game", [](sf::RenderTarget &target) {}},
		{ "Leaderboard", [](sf::RenderTarget &target) {}},
		{ "Settings", [](sf::RenderTarget &target) {}},
		{ "Exit", [&is_exit_requested](sf::RenderTarget &target) {is_exit_requested = true;}}
	};

	game_menu::MenuConfig config {
		.title = "My Game",
		.items = items,
		.style = style
	};
	
	auto menu_ptr = create_menu_context(w, config);
	std::unique_ptr<game_menu::MENU, decltype(&menu_destroy_context)> menu(menu_ptr, &menu_destroy_context);
	while (w.isOpen()) {
		if (is_exit_requested) {
			w.close();
			break;
		}
		sf::Event event;
		while (w.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				is_exit_requested = true;
			}
			menu_handle_event(menu.get(), event);
		}
		w.clear();
		menu_render(menu.get());
		w.display();
	}
	return 0;
}

