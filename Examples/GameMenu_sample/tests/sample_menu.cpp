#include "GameMenu\GameMenu.h"
#include <SFML\Graphics.hpp>
#include <memory>

namespace test {
	class testAction : public gmenu::Action {
	public:
		bool start() {
			return true;
		}
	};
}

void main() {
	sf::RenderWindow w( sf::VideoMode( 800, 600 ), "Sample Title", sf::Style::Close);
	std::vector<gmenu::MenuItem> itemList;
	std::string text[4] = { "Option1", "Option2","Option3", "Option4" };
	gmenu::MenuItem item;
	sf::Font font;
	font.loadFromFile( "sansation.ttf" );
	gmenu::Style style( font, font );
	style.layout = gmenu::Layout::TitleLeft|gmenu::Layout::ItemLeft;
	style.TitleColor = sf::Color::White;
	style.ItemColor = sf::Color::Cyan;
	style.Selected = sf::Color::Yellow;
	style.PaddingTitle.top = 250;
	style.PaddingItems.top = 30;
	style.PaddingItems.left = -100;
	for ( int i = 0; i < 4; ++i ) {
		item.title = text[i];
		item.action = std::make_shared < test::testAction>();
		itemList.push_back( item );
	}
	gmenu::Menu menu( w, "Sample Menu", itemList, style );
	menu.createMenu();
}

