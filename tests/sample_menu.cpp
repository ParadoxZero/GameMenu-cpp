#include "GameMenu\GameMenu.h"
#include <SFML\Graphics.hpp>

namespace test {
	class testAction : public gmenu::Action {
	public:
		bool start() {
			return false;
		}
	};
}

void main() {
	sf::RenderWindow w( sf::VideoMode( 800, 400 ), "Test", sf::Style::Close);
	gmenu::MenuItem item[2];
	std::string text[2] = { "Hello", "World" };
	sf::Font font;
	font.loadFromFile( "sansation.ttf" );
	for ( int i = 0; i < 2; ++i ) {
		item[i].title = text[i];
		item[i].action = new test::testAction();
	}
	gmenu::Style style;
	style.TitleFont = font;
	style.ItemFont = font;
	gmenu::Menu menu( &w, "Sample Menu", item, 2,style );
	menu.createMenu();
}

