#include "GameMenu\GameMenu.h"
#include <SFML\Graphics.hpp>

namespace test {
	class testAction : public gmenu::Action {
	public:
		bool start() {
			return true;
		}
	};
}

void main() {
	sf::RenderWindow w( sf::VideoMode( 800, 800 ), "Test", sf::Style::Close );
	gmenu::MenuItem item[3];
	std::string text[3] = { "Hello", "World","!!!" };
	sf::Font font;
	font.loadFromFile( "sansation.ttf" );
	for ( int i = 0; i < 3; ++i ) {
		item[i].title = text[i];
		item[i].action = new test::testAction();
	}
	gmenu::Style style;
	style.TitleFont = font;
	style.ItemFont = font;
	style.ItemColor = sf::Color::Blue;
	style.Selected = sf::Color::Yellow;
	style.ItemFontSize = 30;
	gmenu::Menu menu( &w, "Sample Menu", item, 3, style );
	menu.createMenu();
}
