#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "Button.h"
#include "classes/board.h"
#include "classes/pawn.h"
#include "classes/player.h"
#include "classes/objects.h"
sf::RenderWindow window(sf::VideoMode(1200, 800), "Warcaby", sf::Style::Titlebar | sf::Style::Close);

Button przycisk[32] = {
      Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
        Button("", { 79,79 }, 20, sf::Color(255, 255, 0, 150)),
};

// 0=false -> ruch białych, 1=true -> ruch czarnych
bool turnOf = false;
int how_many_blackCrowns = 0;
int how_many_whiteCrowns = 0;

//zapis do pliku statystyk (data, nicki graczy i kto wygrał)
std::ofstream statsFile;
std::ifstream statsFileInput;

char* getTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

void capture(std::string color, int x_zbitego, int y_zbitego)
{
    if (color == "black")
        for (int j = 0; j < 12; j++)
            if (whitePawns[j].getPosX() == x_zbitego && whitePawns[j].getPosY() == y_zbitego && whitePawns[j].getStatus() == true)
            {
                whitePawns[j].changeStatus();
                board.update(whitePawns[j].getPosY(), whitePawns[j].getPosX(), 0);
            }
    for (int j = 0; j < 12; j++)
        if (whiteCrowns[j].getPosX() == x_zbitego && whiteCrowns[j].getPosY() == y_zbitego)
        {
            board.update(whiteCrowns[j].getPosY(), whiteCrowns[j].getPosX(), 0);
        }

    if (color == "white")
        for (int j = 0; j < 12; j++)
            if (blackPawns[j].getPosX() == x_zbitego && blackPawns[j].getPosY() == y_zbitego && blackPawns[j].getStatus() == true)
            {
                blackPawns[j].changeStatus();
                board.update(blackPawns[j].getPosY(), blackPawns[j].getPosX(), 0);
            }
    for (int j = 0; j < 12; j++)
        if (blackCrowns[j].getPosX() == x_zbitego && blackCrowns[j].getPosY() == y_zbitego)
        {
            board.update(blackCrowns[j].getPosY(), blackCrowns[j].getPosX(), 0);
        }
}
void captureCrown(std::string color, int x_zbitego, int y_zbitego)
{
    if (color == "black")
        for (int j = 0; j < 12; j++)
            if (whiteCrowns[j].getPosX() == x_zbitego && whiteCrowns[j].getPosY() == y_zbitego && whiteCrowns[j].getStatus() == true)
            {
                whiteCrowns[j].changeStatus();
                board.update(whiteCrowns[j].getPosY(), whiteCrowns[j].getPosX(), 0);
            }

    if (color == "white")
        for (int j = 0; j < 12; j++)
            if (blackCrowns[j].getPosX() == x_zbitego && blackCrowns[j].getPosY() == y_zbitego && blackCrowns[j].getStatus() == true)
            {
                blackCrowns[j].changeStatus();
                board.update(blackCrowns[j].getPosY(), blackCrowns[j].getPosX(), 0);
            }
}



void MovesCaptureCrown(int bicie, int i, int y_des, int x_des, std::string color) // rozpisane binarnie 
{
    int enemyPawn, enemyCrown, moves = 0;
    if (color == "black") {
        enemyPawn = 1;
        enemyCrown = 3;
        int xCrown = blackCrowns[i].getPosX();
        int yCrown = blackCrowns[i].getPosY();
        int x = blackCrowns[i].getPosX();
        int y = blackCrowns[i].getPosY();
        switch (bicie) {
        case 1:
            while (x_des <= x && x_des < xCrown && y_des <= y && y_des < yCrown)
            {
                if (board.getBoard(y - 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x + 1) == 0)
                {
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x - 1, y - 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y -= 1;
                }
            }
            break;

        case 2:
            while (x_des <= x && x_des<xCrown && y_des > y && y >= yCrown)
            {
                if (board.getBoard(y + 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x + 1) == 0)
                {

                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x - 1, y + 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y += 1;
                }
            }
            break;
        case 3:
            while (y_des <= y && y_des<yCrown && x_des >= x && x_des>xCrown)
            {
                if (board.getBoard(y - 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x - 1) == 0)
                {
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x + 1, y - 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y -= 1;
                }
            }
            break;
        case 4:
            while (x_des >= x && x_des > xCrown && y_des >= y && y_des > yCrown)
            {
                if (board.getBoard(y + 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x - 1) == 0)
                {
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                    captureCrown("black", x, y);
                    blackCrowns[i].changePosition(x + 1, y + 1);
                    board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y += 1;
                }
            }
            break;

        default:
            break;
        }
    }
    else {
        enemyPawn = 2;
        enemyCrown = 4;
        int xCrown = whiteCrowns[i].getPosX();
        int yCrown = whiteCrowns[i].getPosY();
        int x = whiteCrowns[i].getPosX();
        int y = whiteCrowns[i].getPosY();
        switch (bicie) {
        case 1:
            while (x_des <= x && x_des < xCrown && y_des <= y && y_des < yCrown)
            {
                if (board.getBoard(y - 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x + 1) == 0)
                {
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x - 1, y - 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y -= 1;
                }
            }
            break;

        case 2:
            while (x_des <= x && x_des<xCrown && y_des > y && y >= yCrown)
            {
                if (board.getBoard(y + 1, x - 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x + 1) == 0)
                {

                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x - 1, y + 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x -= 1;
                    y += 1;
                }
            }
            break;
        case 3:
            while (y_des <= y && y_des<yCrown && x_des >= x && x_des>xCrown)
            {
                if (board.getBoard(y - 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y + 1, x - 1) == 0)
                {
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x + 1, y - 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y -= 1;
                }
            }
            break;
        case 4:
            while (x_des >= x && x_des > xCrown && y_des >= y && y_des > yCrown)
            {
                if (board.getBoard(y + 1, x + 1) == 0 && (board.getBoard(y, x) == enemyCrown || board.getBoard(y, x) == enemyPawn) && board.getBoard(y - 1, x - 1) == 0)
                {
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                    captureCrown("white", x, y);
                    whiteCrowns[i].changePosition(x + 1, y + 1);
                    board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                    board.show();
                    return;
                }
                else {
                    x += 1;
                    y += 1;
                }
            }
            break;

        default:
            break;
        }
    }

}

void changeWhiteToQueen(int i) {
    if (whitePawns[i].getPosY() == 0)
    {
        whitePawns[i].changeStatus();
        whiteCrowns[how_many_whiteCrowns] = Crown(whitePawns[i].getPosY(), whitePawns[i].getPosX(), "white");
        whiteCrowns[how_many_whiteCrowns].born(whitePawns[i].getPosY(), whitePawns[i].getPosX());
        board.update(whiteCrowns[how_many_whiteCrowns].getPosY(), whiteCrowns[how_many_whiteCrowns].getPosX(), 3);
        how_many_whiteCrowns++;
        board.show();
    }
}

void changeBlackToQueen(int i) {
    if (blackPawns[i].getPosY() == 7)
    {
        blackPawns[i].changeStatus();
        blackCrowns[how_many_blackCrowns] = Crown(blackPawns[i].getPosY(), blackPawns[i].getPosX(), "black");
        blackCrowns[how_many_blackCrowns].born(blackPawns[i].getPosY(), blackPawns[i].getPosX());
        board.update(blackCrowns[how_many_blackCrowns].getPosY(), blackCrowns[how_many_blackCrowns].getPosX(), 4);
        how_many_blackCrowns++;
        board.show();
    }
}
void show(sf::Sprite boardGraphic, sf::Sprite whitePawnGraphic, sf::Sprite blackPawnGraphic,
    sf::Sprite whiteCrownGraphic, sf::Sprite blackCrownGraphic, int wyswietlanie) {
    window.clear(sf::Color::White);
    window.draw(boardGraphic);
    int k = 0;
    float x = 0, y = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getBoard(j, i) == 1) {
                whitePawnGraphic.setPosition(90 + i * 79, 90 + j * 79);
                window.draw(whitePawnGraphic);
                x = 90 + i * 79;
                y = 90 + j * 79;
                przycisk[k].x = i;
                przycisk[k].y = j;
                przycisk[k].setPosition({ x, y });
                przycisk[k].setNiePress();
                przycisk[k].drawToBoard(window);
                k++;
            }
            if (board.getBoard(j, i) == 2) {
                blackPawnGraphic.setPosition(90 + i * 79, 90 + j * 79);
                window.draw(blackPawnGraphic);
                x = 90 + i * 79;
                y = 90 + j * 79;
                przycisk[k].x = i;
                przycisk[k].y = j;
                przycisk[k].setPosition({ x, y });
                przycisk[k].setNiePress();
                przycisk[k].drawToBoard(window);
                k++;
            }
            if (board.getBoard(j, i) == 3) {
                whiteCrownGraphic.setPosition(90 + i * 79, 90 + j * 79);
                window.draw(whiteCrownGraphic);
                x = 90 + i * 79;
                y = 90 + j * 79;
                przycisk[k].x = i;
                przycisk[k].y = j;
                przycisk[k].setPosition({ x, y });
                przycisk[k].setNiePress();
                przycisk[k].drawToBoard(window);
                k++;
            }
            if (board.getBoard(j, i) == 4) {
                blackCrownGraphic.setPosition(90 + i * 79, 90 + j * 79);
                window.draw(blackCrownGraphic);

                x = 90 + i * 79;
                y = 90 + j * 79;
                przycisk[k].x = i;
                przycisk[k].y = j;
                przycisk[k].setPosition({ x, y });
                przycisk[k].setNiePress();
                przycisk[k].drawToBoard(window);
                k++;
            }
            if (board.getBoard(j, i) == 0) {
                x = 90 + i * 79;
                y = 90 + j * 79;
                przycisk[k].x = i;
                przycisk[k].y = j;
                przycisk[k].setPosition({ x, y });
                przycisk[k].setNiePress();
                przycisk[k].drawToBoard(window);
                k++;
            }
        }
    }
    if (wyswietlanie == 1)
        window.display();
}

void turn() {
    int index1 = 0;
    int index2 = 0;
    int x1, x2, y1, y2;
    int bicie;
    int moveNumber = 0;
    int captureCounter = 0;
    int ruch = 0;
    sf::Event wydarzenie;
    sf::Text komunikat;
    
    while (window.isOpen())
    {
        while (window.pollEvent(wydarzenie))
        {
            if(wydarzenie.type == sf::Event::Closed)
                window.close();

            if (wydarzenie.type == sf::Event::MouseButtonPressed && ruch == 0) {
                for (int i = 0; i < 32; i++)
                {
                    if (przycisk[i].isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // tutaj jest sobie wyswietlanie i hmm...
                        for (int j = 0; j < 32; j++) { // trzeba je ewidentnie poprawic
                            if (i != j && przycisk[j].pressed == true) {
                                przycisk[i].setPress();
                                index2 = i;
                                x2 = przycisk[i].x;
                                y2 = przycisk[i].y;
                                
                                std::cout << "x1:" << x1 << " " << y1 << "\n";
                                std::cout << "x2:" << x2 << " " << y2 << "\n";
                                ruch = 1;
                            }
                        }
                        if (ruch == 0)
                        {
                            index1 = i;
                            przycisk[i].setPress();
                            x1 = przycisk[i].x;
                            y1 = przycisk[i].y;
                            
                        }
                    }
                    window.display();
                }
            }
            else break;
        }
        if (ruch) break;
    }
    przycisk[index1].setNiePress();
    przycisk[index2].setNiePress();

    x1 = przycisk[index1].x;
    y1 = przycisk[index1].y;
    x2 = przycisk[index2].x;
    y2 = przycisk[index2].y;
    std::cout << "x1:" << x1 << " " << y1 << "\n";
    std::cout << "x2:" << x2 << " " << y2 << "\n";
    for (int i = 0; i < 12; i++) {
        if (blackPawns[i].getPosX() == x1 && blackPawns[i].getPosY() == y1 && turnOf && blackPawns[i].getStatus() == true) {
            blackPawns[i].choose();

            if (board.checkMoves(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) == 0 &&
                (board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) == 0)) {
                std::cout << "Pionek nie moze wykonac zadnego ruchu, wybierz inny\n";
                turn();
                return;
            }
            bicie = board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color);
            while (bicie > 0)
            {
                if (x1 > x2 && y1 > y2 && (bicie == 2 || bicie == 5 || bicie == 8 || bicie == 9 || bicie == 10 || bicie == 12)) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                else if (x1 < x2 && y1 > y2 && (bicie == 4 || bicie == 5 || bicie == 7 || bicie == 9 || bicie == 11 || bicie == 12)) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() - 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() - 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                else if (x1 > x2 && y1 < y2 && (bicie == 1 || bicie == 6 || bicie == 8 || bicie == 9 || bicie == 10 || bicie == 11)) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() - 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() - 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                else if (x1 < x2 && y1 < y2 && (bicie == 3 || bicie == 6 || bicie == 7 || bicie == 10 || bicie == 11 || bicie == 12)) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    capture("black", blackPawns[i].getPosX() + 1, blackPawns[i].getPosY() + 1);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 2, blackPawns[i].getPosX() + 2);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 2);
                    board.show();
                }
                bicie = board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color);
                if (bicie == 0) {
                    turnOf = !turnOf;
                    return;
                }
                turn();
            }
            if (board.checkMoves(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color))//ruchy
            {
                std::cout << i << " " << blackPawns[i].getPosX() << " " << blackPawns[i].getPosY() << " \n";
                if (blackPawns[i].getPosX() > x2 && blackPawns[i].getPosY() < y2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 1, blackPawns[i].getPosX() - 1);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(),2);
                    board.show();
                    turnOf = !turnOf;
                    return;
                }

                if (blackPawns[i].getPosX() < x2 && blackPawns[i].getPosY() < y2) {
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(), 0);
                    blackPawns[i].changePosition(blackPawns[i].getPosY() + 1, blackPawns[i].getPosX() + 1);
                    board.update(blackPawns[i].getPosY(), blackPawns[i].getPosX(),2);
                    board.show();
                    turnOf = !turnOf;
                    return;
                }
            }
        }
       
        if (whitePawns[i].getPosX() == x1 && whitePawns[i].getPosY() == y1 && !turnOf && whitePawns[i].getStatus() == true) {
            whitePawns[i].choose();
            std::cout << i << " " << whitePawns[i].getPosX() << " " << whitePawns[i].getPosY() << " \n";

            std::cout << "x1:" << x1 << " " << y1 << "\n";
            std::cout << "x2:" << x2 << " " << y2 << "\n";
            if (board.checkMoves(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) == 0 &&
                (board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) == 0)) {
                std::cout << "Pionek nie moze wykonac zadnego ruchu, wybierz inny\n";
                turn();
                return;
            }
            bicie = board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color);
            while (bicie > 0)
            {
                if (x1 > x2 && y1 > y2 && (bicie == 2 || bicie == 5 || bicie == 8 || bicie == 9 || bicie == 10 || bicie == 12)) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                else if (x1 < x2 && y1 > y2 && (bicie == 4 || bicie == 5 || bicie == 7 || bicie == 9 || bicie == 11 || bicie == 12)) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() - 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                else if (x1 > x2 && y1 < y2 && (bicie == 1 || bicie == 6 || bicie == 8 || bicie == 9 || bicie == 10 || bicie == 11)) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() - 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() - 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                else if (x1 < x2 && y1 < y2 && (bicie == 3 || bicie == 6 || bicie == 7 || bicie == 10 || bicie == 11 || bicie == 12)) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    capture("white", whitePawns[i].getPosX() + 1, whitePawns[i].getPosY() + 1);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() + 2, whitePawns[i].getPosX() + 2);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                }
                bicie = board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color);
                if (bicie == 0) {
                    turnOf = !turnOf;
                    return;
                }
                turn();
            }
            if (board.checkMoves(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color))//ruchy
            {
                std::cout << i << " " << whitePawns[i].getPosX() << " " << whitePawns[i].getPosY() << " \n";
                if (whitePawns[i].getPosX() > x2 && whitePawns[i].getPosY() > y2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 1, whitePawns[i].getPosX() - 1);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                    turnOf = !turnOf;
                    return;
                }

                if (whitePawns[i].getPosX() < x2 && whitePawns[i].getPosY() > y2) {
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 0);
                    whitePawns[i].changePosition(whitePawns[i].getPosY() - 1, whitePawns[i].getPosX() + 1);
                    board.update(whitePawns[i].getPosY(), whitePawns[i].getPosX(), 1);
                    board.show();
                    turnOf = !turnOf;
                    return;
                }
            }
        }   
    }
    for (int i = 0; i < 12; i++) { // ruchy damek
        if (blackCrowns[i].getPosX() == x1 && blackCrowns[i].getPosY() == y1 && turnOf)
        {
            int bicie = board.searchCaptures(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), blackCrowns[i].color);
            blackCrowns[i].choose();

            int captureOptions; //dawna zmienna costam, tak serio byla tak nazwana heh

            while (bicie)
            {
                    if (x2 < blackCrowns[i].getPosX() && y2 < blackCrowns[i].getPosY()) {
                        captureOptions = 1;
                    }
                    else if (x2 < blackCrowns[i].getPosX() && y2 > blackCrowns[i].getPosY()) {
                        captureOptions = 2;
                    }
                    else if (x2 > blackCrowns[i].getPosX() && y2 < blackCrowns[i].getPosY()) {
                        captureOptions = 3;
                    }
                    else if (x2 > blackCrowns[i].getPosX() && y2 > blackCrowns[i].getPosY()) {
                        captureOptions = 4;
                    }
                    MovesCaptureCrown(captureOptions, i, y2, x2, blackCrowns[i].color); 
                    board.show();
                    turnOf = !turnOf;
                    return;
            }
                
            bicie = board.checkCapture(blackCrowns[i].getPosX(), blackCrowns[i].getPosY(), blackCrowns[i].color);
            
            while ((board.checkMovesCrown(blackCrowns[i].getPosX(), blackCrowns[i].getPosY(), x2, y2) == false) && // nie mozna sie tak ruszyc lub
                (board.searchCaptures(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), blackCrowns[i].color) == 0)) { //nie ma ruchu
                turn(); return;
            }
            if (board.checkMovesCrown(blackCrowns[i].getPosX(), blackCrowns[i].getPosY(), x2, y2)) {
                board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 0);
                blackCrowns[i].changePosition(y2, x2);
                board.update(blackCrowns[i].getPosY(), blackCrowns[i].getPosX(), 4);
                board.show();
                turnOf = !turnOf;
                return;
            }
        }
        
        if (whiteCrowns[i].getPosX() == x1 && whiteCrowns[i].getPosY() == y1 && !turnOf)
        {
            int bicie = board.searchCaptures(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), whiteCrowns[i].color);
            whiteCrowns[i].choose();

            int captureOptions; //dawna zmienna costam

            while (bicie)
            {
                if (x2 < whiteCrowns[i].getPosX() && y2 < whiteCrowns[i].getPosY()) {
                    captureOptions = 1;
                }
                else if (x2 < whiteCrowns[i].getPosX() && y2 > whiteCrowns[i].getPosY()) {
                    captureOptions = 2;
                }
                else if (x2 > whiteCrowns[i].getPosX() && y2 < whiteCrowns[i].getPosY()) {
                    captureOptions = 3;
                }
                else if (x2 > whiteCrowns[i].getPosX() && y2 > whiteCrowns[i].getPosY()) {
                    captureOptions = 4;
                }
                MovesCaptureCrown(captureOptions, i, y2, x2, whiteCrowns[i].color); /// zrob by zamiast bicie byl tutaj ruch z pozycji powyzej zrob jeszcze tez mozliwosc wybrania sobie kierunku bicia
                board.show();
                turnOf = !turnOf;
                return;
            }

            while ((board.checkMovesCrown(whiteCrowns[i].getPosX(), whiteCrowns[i].getPosY(), x2, y2) == false) &&
                (board.searchCaptures(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), whiteCrowns[i].color) == 0)) {
                turn(); return;
            }
            if (board.checkMovesCrown(whiteCrowns[i].getPosX(), whiteCrowns[i].getPosY(), x2, y2)) {
                board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 0);
                whiteCrowns[i].changePosition(y2, x2);
                board.update(whiteCrowns[i].getPosY(), whiteCrowns[i].getPosX(), 4);
                board.show();
                turnOf = !turnOf;
                return;
            }
        }
    }
    std::cout << "Blad, na tym polu nie ma pionka tego gracza\n";
    turnOf = !turnOf;

}

bool hasPawns(std::string color) {
    if (color == "black") {
        for (int i = 0; i < 12; i++) {
            if ((blackPawns[i].getStatus() == true &&
                (board.checkMoves(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) != 0 ||
                    board.checkCapture(blackPawns[i].getPosX(), blackPawns[i].getPosY(), blackPawns[i].color) != 0)) ||
                blackCrowns[i].getStatus() == true) {
                return true;
            }
        }
        return false;
    }
    if (color == "white") {
        for (int i = 0; i < 12; i++) {
            if ((whitePawns[i].getStatus() == true &&
                (board.checkMoves(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) != 0 ||
                    board.checkCapture(whitePawns[i].getPosX(), whitePawns[i].getPosY(), whitePawns[i].color) != 0)) ||
                whiteCrowns[i].getStatus() == true) {
                return true;
            }
        }
        return false;
    }
}

int main()
{
    window.setKeyRepeatEnabled(true);
    sf::Texture texture;
    texture.loadFromFile("graphics/board.jpg");
    sf::Sprite board(texture);
    sf::Texture texture1;
    texture1.loadFromFile("graphics/whitePawn.png");
    sf::Sprite whitePawnGraphic(texture1);
    sf::Texture texture2;
    texture2.loadFromFile("graphics/blackPawn.png");
    sf::Sprite blackPawnGraphic(texture2);
    sf::Texture texture3;
    texture3.loadFromFile("graphics/blackCrown.png");
    sf::Sprite blackCrownGraphic(texture3);
    sf::Texture texture4;
    texture4.loadFromFile("graphics/whiteCrown.png");
    sf::Sprite whiteCrownGraphic(texture4);

    //deklaracja menu
    Button menu1("Zasady gry", { 240,60 }, 20, sf::Color::White);
    menu1.setPosition({ 485,400 });
    menu1.setPositionText({ 565,418 });
    Button menu2("Graj!", { 240,60 }, 20, sf::Color::White);
    menu2.setPosition({ 485,500 });
    menu2.setPositionText({ 590,518 });
    Button menu3("Wyniki", { 240,60 }, 20, sf::Color::White);
    menu3.setPosition({ 485,600 });
    menu3.setPositionText({ 585,618 });

    sf::Font arial;
    arial.loadFromFile("C:/Users/Wiktoria/Desktop/Nowy folder/Project1/Arialn.ttf");
    menu1.setFont(arial);
    menu2.setFont(arial);
    menu3.setFont(arial);

    sf::Text titleOfGame, zasady, title;
    titleOfGame.setFont(arial);
    titleOfGame.setString("Warcaby");
    titleOfGame.setCharacterSize(60);
    titleOfGame.setFillColor(sf::Color::Red);
    titleOfGame.setPosition({ 500,95 });

    bool isGame = false;
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            
            case sf::Event::MouseMoved:
                if (menu1.isMouseOver(window)) {
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
                if (menu1.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //wyswietlam zasady
                    menu1.setBackColor(sf::Color::Red);

                    title.setFont(arial);
                    title.setString("ZASADY GRY");
                    title.setCharacterSize(25);
                    title.setFillColor(sf::Color::Red);
                    title.setPosition({ 530,160 });

                    zasady.setFont(arial);
                    zasady.setString("1) Pionki poruszaja sie tylko do przodu.\n2) Pionki bija do przodu oraz do tylu po skosie.\n3) Istnieja bicia wielokrotne.\n4) Gdy pionek dotrze do przeciwnej krawedzi, to pionek staje sie damka.\n5) Damki moga poruszac sie do przodu oraz do tylu o dowolna ilosc pol.\n6) Gra skonczy sie jesli jeden z graczy zbije wszystkie pionki drugiego lub\ngracz nie bedzie mial mozliwosci ruchu.");
                    zasady.setCharacterSize(20);
                    zasady.setFillColor(sf::Color::Black);
                    zasady.setPosition({ 340,190 });

                }
                else if (menu2.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    player1.setName("gracz pierwszy");
                    player2.setName("gracz drugi");
                    
                    show(board, whitePawnGraphic, blackPawnGraphic, blackCrownGraphic, whiteCrownGraphic,1);
                    while (hasPawns("black") && hasPawns("white")) {
                        turn();
                        std::cout << "costam\n";
                        show(board, whitePawnGraphic, blackPawnGraphic, blackCrownGraphic, whiteCrownGraphic,1);
                    }
                    statsFile.open("stats/results.txt", std::ios::app);
                    statsFileInput.open("stats/results.txt");
                    std::string winner;
                    winner = turnOf ? player1.getName() : player2.getName();
                    std::cout << "WYGRANA GRACZA: " << winner;
                    statsFile << getTime() << player1.getName() << " vs " << player2.getName() << "\tZwyciezca: " << winner << "\n\n";
                    statsFile.close();
                    statsFileInput.close();
                }
                else if (menu3.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    menu3.setBackColor(sf::Color::Red);

                    title.setFont(arial);
                    title.setString("WYNIKI:");
                    title.setCharacterSize(25);
                    title.setFillColor(sf::Color::Red);
                    title.setPosition({ 550,170 });

                    zasady.setFont(arial);
                    zasady.setCharacterSize(20);
                    zasady.setFillColor(sf::Color::Black);
                    zasady.setPosition({ 340,200 });

                    statsFile.open("stats/results.txt", std::ios::app); //dobrze by bylo gdyby sie wyswietlaly tylko 6 ostatnich
                    statsFileInput.open("stats/results.txt"); //bo wyglada to wlasnie tak jak wyglada
                    std::string wyniki = "", wyraz;
                    int counter = 0;
                    int number = 1;
                    while (statsFileInput >> wyraz) {
                        if (counter == 0) {
                            wyniki += std::to_string(number) + ". ";
                        }
                        wyniki += wyraz;
                        wyniki += " ";
                        if (counter < 9) {
                            counter++;
                        }
                        else {
                            wyniki += "\n";
                            number++;
                            counter = 0;
                        }
                    }
                    zasady.setString(wyniki);
                    statsFile.close();
                    statsFileInput.close();
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
        window.display();
    }
    return 0;
}
