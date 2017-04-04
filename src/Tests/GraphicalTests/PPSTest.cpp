/*
 * infosv
 * jan 2017
 * Marco Antognini
 */

#include <Tests/GraphicalTests/PPSTest.hpp>
#include <Env/Wolf.hpp>
#include <Env/Sheep.hpp>
//#include <Env/Grass.hpp> // A DECOMENTER DEPUIS LE TEST 11
#include <Utility/Utility.hpp>

IMPLEMENT_MAIN(PPSTest)

void PPSTest::onEvent(sf::Event event, sf::RenderWindow&)
{
if (event.type == sf::Event::KeyPressed) {
	switch (event.key.code) {
		case sf::Keyboard::W:
			getAppEnv().addEntity(new Wolf(getCursorPositionInView()));
			break;
		case sf::Keyboard::S:
			getAppEnv().addEntity(new Sheep(getCursorPositionInView()));
			break;
		case sf::Keyboard::G:
			// A DECOMMENTER DEPUIS LE TEST 11
			//getAppEnv().addEntity(new Grass(getCursorPositionInView()));
			break;
                
		default:
			break;
	}

}

}



