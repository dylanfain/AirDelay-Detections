//
// Created by samir on 4/16/2024.
//
#include <C:\SFML\include\SFML\Graphics.hpp>
#include <iostream>

class gui{
    //dimension vars
public:

    void button(int x, int y, int height, int width, std::string name){}
    void display(){}
    std::vector<sf::Text> dropdown(std::vector<std::string> options, sf::RectangleShape& dropdownRect, sf::Text& dropdownText, sf::Font &font){

        // Dropdown menu items
        std::vector<sf::Text> dropdownItems;
        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text item;
            item.setFont(font);
            item.setString(options[i]);
            item.setCharacterSize(16);
            item.setFillColor(sf::Color::Black);
            //make relative to dropdownrect position
            item.setPosition(55, 85 + i * 30);
            dropdownItems.push_back(item);
        }
        return dropdownItems;
    }
    void setText(sf::Text &text, float x, float y){
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(x, y));
    }
    sf::RectangleShape Rect(float x, float y, float height, float width){
        sf::RectangleShape Rect(sf::Vector2f(width, height));
        Rect.setFillColor(sf::Color::White);
        Rect.setOutlineColor(sf::Color::Black);
        Rect.setOutlineThickness(2.f);
        Rect.setPosition(x, y);
        return Rect;
    }

    sf::Text text(float x, float y, float size, std::string input, sf::Font &font){
        sf::Text Text;
        Text.setFont(font);
        Text.setString(input);
        Text.setCharacterSize(size);
        Text.setFillColor(sf::Color::Black);
        Text.setPosition(x, y);
        return Text;
    }



};