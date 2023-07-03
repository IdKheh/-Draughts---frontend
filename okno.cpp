#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "classes/board.h"
#include "classes/pawn.h"
#include "classes/player.h"
#include "classes/objects.h"
#include "funkcje.h"
#include "Button.h"

int main()
{
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "Warcaby", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	
	sf::Event event;

	Button menu1("Zasady gry", { 240,60 },20,sf::Color::White);
	menu1.setPosition({350,400});
	menu1.setPositionText({ 430,418 });
	Button menu2("Graj!", { 240,60 }, 20, sf::Color::White);
	menu2.setPosition({ 350,500 });
	menu2.setPositionText({ 455,518 });
	Button menu3("Wyniki", { 240,60 }, 20, sf::Color::White);
	menu3.setPosition({ 350,600 });
	menu3.setPositionText({ 450,618 });

	sf::Font arial;
	arial.loadFromFile("C:/Users/Wiktoria/Desktop/Nowy folder/Project1/Arialn.ttf");
	menu1.setFont(arial);
	menu2.setFont(arial);
	menu3.setFont(arial);

	sf::Text titleOfGame,zasady,title, wyniki;
	titleOfGame.setFont(arial);
	titleOfGame.setString("Warcaby");
	titleOfGame.setCharacterSize(60);
	titleOfGame.setFillColor(sf::Color::Red);
	titleOfGame.setPosition({ 360,95 });

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseMoved:
				if (menu1.isMouseOver(window)){
					menu1.setBackColor(sf::Color(232, 232, 232));
				}
				else if (menu2.isMouseOver(window)) {
					menu2.setBackColor(sf::Color(232, 232, 232));
				}
				else if (menu3.isMouseOver(window)) {
					menu3.setBackColor(sf::Color(232, 232, 232));
				}
				else {
					menu1.setBackColor(sf::Color(195, 194, 194));
					menu2.setBackColor(sf::Color(195, 194, 194));
					menu3.setBackColor(sf::Color(195, 194, 194));
				}
			case  sf::Event::MouseButtonPressed:
				if (menu1.isMouseOver(window)&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //wyswietlam zasady
					menu1.setBackColor(sf::Color::Red);
					
					title.setFont(arial);
					title.setString("ZASADY GRY");
					title.setCharacterSize(25);
					title.setFillColor(sf::Color::Red);
					title.setPosition({ 390,160 });

					zasady.setFont(arial);
					zasady.setString("1) Pionki poruszaja sie tylko do przodu.\n2) Pionki bija do przodu oraz do tylu po skosie.\n3) Istnieja bicia wielokrotne.\n4) Gdy pionek dotrze do przeciwnej krawedzi, to pionek staje sie damka.\n5) Damki moga poruszac sie do przodu oraz do tylu o dowolna ilosc pol.\n6) Gra skonczy sie jesli jeden z graczy zbije wszystkie pionki drugiego lub\ngracz nie bedzie mial mozliwosci ruchu.");
					zasady.setCharacterSize(20);
					zasady.setFillColor(sf::Color::Black);
					zasady.setPosition({ 190,190 });

				}
				else if (menu2.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu2.setBackColor(sf::Color::Red);
				}
				else if (menu3.isMouseOver(window)&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu3.setBackColor(sf::Color::Red);

					title.setFont(arial);
					title.setString("Wyniki");
					title.setCharacterSize(25);
					title.setFillColor(sf::Color::Red);
					title.setPosition({ 390,160 });

					wyniki.setFont(arial);
					wyniki.setString("ciekawe kto wygra");
					wyniki.setCharacterSize(20);
					wyniki.setFillColor(sf::Color::Black);
					wyniki.setPosition({ 190,190 });
				}	

			}
		}
		window.clear(sf::Color::White);
		menu1.drawTo(window);
		menu2.drawTo(window);
		menu3.drawTo(window);
		window.draw(titleOfGame);
		window.draw(title);
		window.draw(zasady);
		window.draw(wyniki);
		window.display();
	}

	return 0;
}