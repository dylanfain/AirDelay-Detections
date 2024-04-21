#include <iostream>
#include <SFML\Graphics.hpp>

class gui{
    //dimension vars
public:
    //possibly make constructor to get window to bring drawing into a function later
    std::vector<sf::Text> displayResults(std::vector<FlightData>& flightData, sf::Font &font){
        std::vector<sf::Text> Results;
        int index = 1;
        if(flightData.size() == 0){
            string value = "There is no data for these filters";
            sf::Text item = text(400,  225 + index *25, 12,value, font);
            item.setFillColor(sf::Color::White);
            Results.push_back(item);
        }
        else if(flightData.size() < 10){
            for (int i = flightData.size()-1; i > 0; i--) {
                string weatherval = "False";
                if(to_string(flightData[i].weatherDelay) == "1")
                    weatherval = "True";
                std::string current = to_string(index)+".  Delay: "+to_string(flightData[i].arrivalDelay)+" mins, "+flightData[i].airline+" " +flightData[i].date + ", Weather Delay: " +
                                      weatherval;
                sf::Text item = text(400,  225 + index *25, 12,current, font);
                item.setFillColor(sf::Color::White);
                Results.push_back(item);
                index++;
            }
        }
        else{
            for (int i = flightData.size()-1; i > flightData.size()-11; i--) {
                string weatherval = "False";
                if(to_string(flightData[i].weatherDelay) == "1")
                    weatherval = "True";
                std::string current = to_string(index)+".  Delay: "+to_string(flightData[i].arrivalDelay)+" mins, "+flightData[i].airline+" " +flightData[i].date + ", Weather Delay: " +
                                      weatherval;
                sf::Text item = text(400,  225 + index *25, 12,current, font);
                item.setFillColor(sf::Color::White);
                Results.push_back(item);
                index++;
            }
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
    std::vector<sf::RectangleShape> DropdownBackground(std::vector<std::string> options, sf::RectangleShape& Rect){
        std::vector<sf::RectangleShape> stuff;
        for (int i = 0; i < options.size(); ++i) {
            auto dim = Rect.getGlobalBounds();
            sf::RectangleShape current(sf::Vector2f(dim.width-2, dim.height-2));
            //color for boxes
            current.setFillColor(sf::Color{ 110, 110, 110, 255 });
            current.setPosition(dim.left+1, dim.top + i*dim.height+ dim.height+1);
            current.setOutlineColor(sf::Color::Black);
            current.setOutlineThickness(1);
            stuff.push_back(current);
        }
        return stuff;
    }

};
