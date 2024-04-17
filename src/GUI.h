//
// Created by samir on 4/16/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>

class gui{
    //dimension vars
public:
    //possibly make constructor to get window to bring drawing into a function later
    void display(){}//creates results text display
    std::vector<sf::Text> dropdown(std::vector<std::string> options, sf::RectangleShape& Rect,  sf::Font &font){

        // Dropdown menu items
        std::vector<sf::Text> dropdownItems;
        for (size_t i = 0; i < options.size(); ++i) {
            auto dim = Rect.getGlobalBounds();
            sf::Text item = text(dim.left+dim.width/2.0f, dim.top+dim.height/2.0f+dim.height + i * dim.height, 16, options[i], font);
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
        Rect.setFillColor(sf::Color{ 55, 55, 55, 255 });
        Rect.setPosition(x, y);
        return Rect;
    }
    //creates text object
    sf::Text text(float x, float y, int size, std::string input, sf::Font &font){
        sf::Text Text;
        Text.setFont(font);
        Text.setString(input);
        Text.setCharacterSize(size);
        Text.setFillColor(sf::Color::Black);
        //Text.setPosition(x, y);
        setText(Text, x, y);
        return Text;
    }

};