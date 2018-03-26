#include <iostream>
#include <cmath>
#define PI 3.14159265
#include <SFML/Graphics.hpp>
using namespace std;

sf::Sprite bImage;
sf::Texture bTexture;
sf::RenderWindow window;
std::vector<sf::RectangleShape> line(20);
std::vector<sf::CircleShape> vertex(20);
sf::CircleShape originMarker, destinationMarker, hoverMarker;
bool originMarkerIsPlaced = false, destinationMarkerIsPlaced = false;
float xInitialOffset, yInitialOffset;
int lineThickness = 9;
int vertexRadius = 10;


void resetHoverMarkerPosition();

void initVertexVector(int radius, sf::Color color);

float getProximityToEdge(sf::RectangleShape &shape, int x, int y) {

    float A, B, K, L, theta, alpha;
    int epsilon;


    A = fabs(y - shape.getPosition().y);
    B = fabs(x - shape.getPosition().x);
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

    return L;
};

void initVertexVector(int radius, sf::Color color) {

    sf::Color vertexBorderColor = sf::Color(255, 255, 255, 200);
    int vertexBorderThickness = 3;

    vertex[0].setPosition(1512-xInitialOffset-radius, 1517-yInitialOffset-radius);
    vertex[1].setPosition(1523-xInitialOffset-radius, 1261-yInitialOffset-radius);
    vertex[2].setPosition(1658-xInitialOffset-radius, 1439-yInitialOffset-radius);
    vertex[3].setPosition(1490-xInitialOffset-radius, 1022-yInitialOffset-radius);
    vertex[4].setPosition(1529-xInitialOffset-radius, 1165-yInitialOffset-radius);

    for(int i=0; i<vertex.size(); i++) {
        vertex[i].setRadius(radius);
        vertex[i].setFillColor(color);
        vertex[i].setOutlineColor(vertexBorderColor);
        vertex[i].setOutlineThickness(vertexBorderThickness);
    }
}

void initLineVector(int lineThickness, sf::Color streetColor) {
    line[0].setSize(sf::Vector2f(260, lineThickness));
    line[0].setPosition(1510-xInitialOffset, 1520-yInitialOffset);
    line[0].setRotation(-88);

    line[1].setSize(sf::Vector2f(190, lineThickness));
    line[1].setPosition(1521-xInitialOffset, 1263-yInitialOffset);
    line[1].setRotation(-142);

    line[2].setSize(sf::Vector2f(140, lineThickness));
    line[2].setPosition(1372-xInitialOffset, 1141-yInitialOffset);
    line[2].setRotation(-85);

    line[3].setSize(sf::Vector2f(100, lineThickness));
    line[3].setPosition(1393-xInitialOffset, 1001-yInitialOffset);
    line[3].setRotation(12);

    line[4].setSize(sf::Vector2f(386, lineThickness));
    line[4].setPosition(1491-xInitialOffset, 1022-yInitialOffset);
    line[4].setRotation(15);

    line[5].setSize(sf::Vector2f(77, lineThickness));
    line[5].setPosition(1862-xInitialOffset, 1123-yInitialOffset);
    line[5].setRotation(4);

    line[6].setSize(sf::Vector2f(140, lineThickness));
    line[6].setPosition(1940-xInitialOffset, 1129-yInitialOffset);
    line[6].setRotation(4);

    line[7].setSize(sf::Vector2f(105, lineThickness));
    line[7].setPosition(2082-xInitialOffset, 1138-yInitialOffset);
    line[7].setRotation(4);

    line[8].setSize(sf::Vector2f(98, lineThickness));
    line[8].setPosition(1520-xInitialOffset, 1259-yInitialOffset);
    line[8].setRotation(-88);

    line[9].setSize(sf::Vector2f(140, lineThickness));
    line[9].setPosition(1527-xInitialOffset, 1165-yInitialOffset);
    line[9].setRotation(-107);

    line[10].setSize(sf::Vector2f(170, lineThickness));
    line[10].setPosition(1513-xInitialOffset, 1516-yInitialOffset);
    line[10].setRotation(-29);

    line[11].setSize(sf::Vector2f(175, lineThickness));
    line[11].setPosition(1658-xInitialOffset, 1433-yInitialOffset);
    line[11].setRotation(-29);

    line[12].setSize(sf::Vector2f(136, lineThickness));
    line[12].setPosition(1811-xInitialOffset, 1354-yInitialOffset);
    line[12].setRotation(-79);

    line[13].setSize(sf::Vector2f(315, lineThickness));
    line[13].setPosition(1530-xInitialOffset, 1163-yInitialOffset);
    line[13].setRotation(9);

    line[14].setSize(sf::Vector2f(90, lineThickness));
    line[14].setPosition(1838-xInitialOffset, 1217-yInitialOffset);
    line[14].setRotation(-79);

    for(int i=0; i<line.size(); i++) {
        line[i].setFillColor(streetColor);
    }

}

void updateKeyboardControl(sf::Vector2i screenDimensions) {
    int i;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bImage.getPosition().x < 0) {
        bImage.move(1, 0);
        originMarker.move(1, 0);
        destinationMarker.move(1, 0);

        for(i=0; i<line.size(); i++) {
            line[i].move(1, 0);
        }

        for(i=0; i<vertex.size(); i++) {
            vertex[i].move(1, 0);
        }

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
             bImage.getPosition().x >= -(bImage.getLocalBounds().width-screenDimensions.x)) {
        bImage.move(-1, 0);
        originMarker.move(-1, 0);
        destinationMarker.move(-1, 0);

        for(i=0; i<line.size(); i++) {
            line[i].move(-1, 0);
        }

        for(i=0; i<vertex.size(); i++) {
            vertex[i].move(-1, 0);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bImage.getPosition().y < 0) {
        bImage.move(0, 1);
        originMarker.move(0, 1);
        destinationMarker.move(0, 1);

        for(i=0; i<line.size(); i++) {
            line[i].move(0, 1);
        }

        for(i=0; i<vertex.size(); i++) {
            vertex[i].move(0, 1);
        }

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
             bImage.getPosition().y >= -(bImage.getLocalBounds().height-screenDimensions.y)) {
        bImage.move(0, -1);
        originMarker.move(0, -1);
        destinationMarker.move(0, -1);

        for(i=0; i<line.size(); i++) {
            line[i].move(0, -1);
        }

        for(i=0; i<vertex.size(); i++) {
            vertex[i].move(0, -1);
        }
    }
}

void resetHoverMarkerPosition() {
    hoverMarker.setPosition(-50, -50);
}

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Vector2i screenDimensions(1600, 900);
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "my first sfml", sf::Style::Default, settings);

    if(!bTexture.loadFromFile("peta.png"))
        std::cout << "Could not load background image" << std::endl;
    bImage.setTexture(bTexture);
    xInitialOffset = (bImage.getGlobalBounds().width)/2 - 400;
    yInitialOffset = (bImage.getGlobalBounds().height)/2 - 1000;
    bImage.setPosition(-xInitialOffset,-yInitialOffset);

    //https://www.youtube.com/watch?v=ghgd-R1gRmc
    sf::Color streetColor = sf::Color(0, 0, 0, 150);
    sf::Color streetColorHover = sf::Color(255, 255, 0, 200);
    sf::Color hoverMarkerColor = sf::Color(0, 154, 0, 150);
    sf::Color originMarkerColor = sf::Color(0, 154, 0, 200);
    sf::Color destinationMarkerColor = sf::Color(236, 0, 0, 200);
    sf::Color vertexColor = sf::Color(0, 0, 0, 255);


    initLineVector(lineThickness, streetColor);
    initVertexVector(vertexRadius, vertexColor);

    hoverMarker.setRadius(10);
    hoverMarker.setFillColor(hoverMarkerColor);
    resetHoverMarkerPosition();

    originMarker.setRadius(15);
    originMarker.setFillColor(originMarkerColor);
    originMarker.setOutlineColor(sf::Color::White);
    originMarker.setOutlineThickness(2);
    originMarker.setPosition(-100.0f, -100.0f);

    destinationMarker.setRadius(15);
    destinationMarker.setFillColor(destinationMarkerColor);
    destinationMarker.setOutlineColor(sf::Color::White);
    destinationMarker.setOutlineThickness(2);
    destinationMarker.setPosition(-100.0f, -100.0f);



    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    float proximityToEdge;

    while(window.isOpen()) {
        sf::Event event;


        while(window.pollEvent(event)) {

            resetHoverMarkerPosition();

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

                            proximityToEdge = getProximityToEdge(line[i], event.mouseMove.x, event.mouseMove.y);

                            if(proximityToEdge < (0.85*lineThickness)) {
                                line[i].setFillColor(streetColorHover);
                                hoverMarker.setPosition(event.mouseMove.x-(hoverMarker.getRadius()),
                                                         event.mouseMove.y-(hoverMarker.getRadius()));

                            }


                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:

                    for(int i=0; i<line.size(); i++) {
                        if (line[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                            proximityToEdge = getProximityToEdge(line[i], event.mouseButton.x, event.mouseButton.y);

                            //std::cout << "line " << i << " ditekan - " << proximityToEdge << std::endl;

                            if(proximityToEdge < (0.85*lineThickness)) {

                                if(event.mouseButton.button == sf::Mouse::Left) {
                                    originMarker.setPosition(event.mouseButton.x-(originMarker.getRadius()),
                                                             event.mouseButton.y-(originMarker.getRadius()));

                                    originMarkerIsPlaced = true;
                                    std::cout << "left mouse button " << std::endl;

                                }else if(event.mouseButton.button == sf::Mouse::Right) {
                                    destinationMarker.setPosition(event.mouseButton.x-(destinationMarker.getRadius()),
                                                             event.mouseButton.y-(destinationMarker.getRadius()));


                                    destinationMarkerIsPlaced = true;
                                    std::cout << "right mouse button " << std::endl;
                                }

                            }
                        }
                    }

                    break;
                default:

                    break;
            }
        }

        updateKeyboardControl(screenDimensions);



        window.setView(view);
        window.draw(bImage);


        for(int i=0; i<line.size(); i++) {
            window.draw(line[i]);
        }

        for(int i=0; i<vertex.size(); i++) {
            window.draw(vertex[i]);
        }

        window.draw(hoverMarker);
        window.draw(originMarker);
        window.draw(destinationMarker);

        window.display();
        window.clear();
    }


    return 0;
}












