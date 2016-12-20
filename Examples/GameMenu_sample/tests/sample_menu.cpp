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
	sf::RenderWindow w( sf::VideoMode( 500, 500 ), "Test", sf::Style::Close);
	std::vector<gmenu::MenuItem> itemList;
	std::string text[3] = { "Hello", "World","!!!" };
	gmenu::MenuItem item;
	sf::Font font;
	font.loadFromFile( "sansation.ttf" );
	gmenu::Style style( font, font );
	style.layout = gmenu::Layout::TitleCentre;
	for ( int i = 0; i < 3; ++i ) {
		item.title = text[i];
		item.action = new test::testAction();
		itemList.push_back( item );
	}
	gmenu::Menu menu( w, "Sample Menu", itemList, style );
	menu.createMenu();
}

