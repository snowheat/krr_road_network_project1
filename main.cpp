#include <iostream>
#include <math.h>
#define PI 3.14159265
#include <SFML/Graphics.hpp>
using namespace std;

sf::Sprite bImage;
sf::Texture bTexture;
sf::RenderWindow window;
std::vector<sf::RectangleShape> line(10);
int lineThickness = 7;

float getProximityToEdge(sf::Event event, sf::RectangleShape &shape) {

    float A, B, K, L, theta, alpha;
    int epsilon;


    A = fabs(event.mouseMove.y - shape.getPosition().y);
    B = fabs(event.mouseMove.x - shape.getPosition().x);
    K = sqrtf(pow(A, 2.0f) + pow(B, 2.0f));

    if((shape.getRotation()>=0 && shape.getRotation()<90)
       || (shape.getRotation()>=180 && shape.getRotation()<270)) {
        epsilon = abs((int)shape.getRotation()) % 90;
    }else if(shape.getRotation()>=90 && shape.getRotation()<180) {
        epsilon = 180 - abs((int)shape.getRotation());
    }else if(shape.getRotation()>=270 && shape.getRotation()<360) {
        epsilon = 360 - abs((int)shape.getRotation());
    }

    theta = atan((A/B)) * 180 / PI;
    alpha = fabs(epsilon - theta);

    L = K * sin(alpha*PI/180);

    return L;
};

void initLineVectors(int lineThickness, sf::Vector2i screenDimensions, sf::Color streetColor) {
    line[0].setSize(sf::Vector2f(260, lineThickness));
    line[0].setPosition(1510-(float)screenDimensions.x/2, 1520-(float)screenDimensions.y/2);
    line[0].setRotation(-88);
    line[0].setFillColor(streetColor);

    line[1].setSize(sf::Vector2f(190, lineThickness));
    line[1].setPosition(1521-(float)screenDimensions.x/2, 1263-(float)screenDimensions.y/2);
    line[1].setRotation(-142);
    line[1].setFillColor(streetColor);

    line[2].setSize(sf::Vector2f(140, lineThickness));
    line[2].setPosition(1372-(float)screenDimensions.x/2, 1141-(float)screenDimensions.y/2);
    line[2].setRotation(-85);
    line[2].setFillColor(streetColor);

    line[3].setSize(sf::Vector2f(100, lineThickness));
    line[3].setPosition(1393-(float)screenDimensions.x/2, 1001-(float)screenDimensions.y/2);
    line[3].setRotation(12);
    line[3].setFillColor(streetColor);

    line[4].setSize(sf::Vector2f(386, lineThickness));
    line[4].setPosition(1491-(float)screenDimensions.x/2, 1022-(float)screenDimensions.y/2);
    line[4].setRotation(15);
    line[4].setFillColor(streetColor);

    line[5].setSize(sf::Vector2f(77, lineThickness));
    line[5].setPosition(1862-(float)screenDimensions.x/2, 1123-(float)screenDimensions.y/2);
    line[5].setRotation(4);
    line[5].setFillColor(streetColor);

    line[6].setSize(sf::Vector2f(140, lineThickness));
    line[6].setPosition(1940-(float)screenDimensions.x/2, 1129-(float)screenDimensions.y/2);
    line[6].setRotation(4);
    line[6].setFillColor(streetColor);

    line[7].setSize(sf::Vector2f(105, lineThickness));
    line[7].setPosition(2082-(float)screenDimensions.x/2, 1138-(float)screenDimensions.y/2);
    line[7].setRotation(4);
    line[7].setFillColor(streetColor);
}

void updateKeyboardControl(sf::Vector2i screenDimensions) {
    int i;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bImage.getPosition().x < 0) {
        bImage.move(1, 0);
        for(i=0; i<line.size(); i++) {
            line[i].move(1,0 );
        }

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
             bImage.getPosition().x >= -(bImage.getLocalBounds().width-screenDimensions.x)) {
        bImage.move(-1, 0);
        for(i=0; i<line.size(); i++) {
            line[i].move(-1,0 );
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bImage.getPosition().y < 0) {
        bImage.move(0, 1);
        for(i=0; i<line.size(); i++) {
            line[i].move(0, 1);
        }
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
             bImage.getPosition().y >= -(bImage.getLocalBounds().height-screenDimensions.y)) {
        bImage.move(0, -1);
        for(i=0; i<line.size(); i++) {
            line[i].move(0, -1);
        }
    }
}



int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Vector2i screenDimensions(1600, 600);
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "my first sfml");

    if(!bTexture.loadFromFile("peta.png"))
        std::cout << "Could not load background image" << std::endl;
    bImage.setTexture(bTexture);
    bImage.setPosition(-(float)screenDimensions.x/2,-(float)screenDimensions.y/2);

    //https://www.youtube.com/watch?v=ghgd-R1gRmc
    sf::Color streetColor = sf::Color(0, 0, 0, 150);
    sf::Color streetColorHover = sf::Color(255, 84, 0, 150);

    initLineVectors(lineThickness, screenDimensions, streetColor);

    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    float proximityToEdge;

    while(window.isOpen()) {
        sf::Event event;


        while(window.pollEvent(event)) {

            for(int i=0; i<line.size(); i++) {
                line[i].setFillColor(streetColor);
            }

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                case sf::Event::MouseMoved:
                    for(int i=0; i<line.size(); i++) {
                        if (line[i].getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {

                            proximityToEdge = getProximityToEdge(event, line[i]);

                            if(proximityToEdge < (0.85*lineThickness))
                                line[i].setFillColor(streetColorHover);
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    for(int i=0; i<line.size(); i++) {
                        if (line[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                            proximityToEdge = getProximityToEdge(event, line[i]);

                            /*
                            std::cout << "ada click nih di line " << i << " A B epsilon theta alpha. A: "
                                      << A << " B: "
                                      << B << " K: "
                                      << K << " epsilon: "
                                      << epsilon << " theta: "
                                      << theta << " alpha: "
                                      << alpha << " L: "
                                      << L << " - "
                                      << line[i].getPosition().y << " "
                                      << line[i].getPosition().y << " "
                                      << endl;

                            */



                        }
                    }

                    break;
            }
        }



        updateKeyboardControl(screenDimensions);

        window.setView(view);
        window.draw(bImage);

        for(int i=0; i<line.size(); i++) {
            window.draw(line[i]);
        }

        window.display();
        window.clear();
    }


    return 0;
}








