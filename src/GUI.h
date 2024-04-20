#include <iostream>
#include <SFML\Graphics.hpp>

class gui{
    //dimension vars
public:
    //possibly make constructor to get window to bring drawing into a function later
    std::vector<sf::Text> displayResults(std::vector<FlightData>& flightData, sf::Font &font){
        std::vector<sf::Text> Results;
        for (int i = 0; i < 10; ++i) {
            std::string current = to_string(i+1)+".  "+flightData[i].airline+" " +flightData[i].date;
            sf::Text item = text(300,  250 + i *25, 15,current, font);
            item.setFillColor(sf::Color::White);
            Results.push_back(item);
        }
        return Results;
    }

    std::vector<sf::Text> dropdown(std::vector<std::string> options, sf::RectangleShape& Rect,  sf::Font &font){

        // Dropdown menu items
        std::vector<sf::Text> dropdownItems;
        for (size_t i = 0; i < options.size(); ++i) {
            auto dim = Rect.getGlobalBounds();
            sf::Text item = text(dim.left+dim.width/2.0f, dim.top+dim.height/2.0f+dim.height + i * dim.height, 12, options[i], font);
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
        //Rect.setOutlineColor(sf::Color::Black);
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
