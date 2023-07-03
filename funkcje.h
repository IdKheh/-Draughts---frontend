#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"

void rulesOfGame(sf::Font &font, sf::RenderWindow &window)
{
	sf::Text title,zasady;
	title.setFont(font);
	title.setString("ZASADY GRY");
	title.setCharacterSize(40);
	title.setFillColor(sf::Color::Red);
	title.setPosition({ 350,100 });


	sf::Text text;
	text.setFont(font);
	text.setString("Warcaby");
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Red);
	text.setPosition({ 300,80 });


	zasady.setFont(font);
	zasady.setString("1) Pionki poruszaja sie tylko do przodu.\n2) Pionki bija do przodu oraz do tylu po skosie.\n3) Istnieja bicia wielokrotne.\n4) Gdy pionek dotrze do przeciwnej krawedzi, to pionek staje sie damka.\n5) Damki moga poruszac sie do przodu oraz do tylu o dowolna ilosc pol.\n6) Gra skonczy sie jesli jeden z graczy zbije wszystkie pionki drugiego lub gracz nie bedzie mial mozliwosci ruchu.");
	zasady.setCharacterSize(10);
	zasady.setFillColor(sf::Color::Black);
	zasady.setPosition({ 350,100 });

	window.draw(title);
	window.draw(text);
	window.draw(zasady);
}
