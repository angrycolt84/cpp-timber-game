#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    VideoMode vm({1920, 1080});

    Texture textureBackground;
    textureBackground.loadFromFile("background.png");

    if (!textureBackground.loadFromFile("background.png")) {
        std::cout << "ERROR: could not load background.png" << std::endl;
        return -1;
    } else {
        std::cout << "SUCCESS: background.png loaded" << std::endl;
    }

    Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition({0, 0});

    Texture textureTree;
    textureTree.loadFromFile("src/graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition({600, 0});
    // prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("src/graphics/bee.png");
    Sprite spriteBee(textureBee);
    spriteBee.setPosition({700, 80});
    // bee is moving?
    bool isBeeActive{false};
    float beeSpeed{0.0f};
    // cloud processing
    Texture textureCloud;
    textureCloud.loadFromFile("src/graphics/cloud.png");
    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);

    spriteCloud1.setPosition({0, 0});
    spriteCloud2.setPosition({0, 150});
    spriteCloud3.setPosition({0, 300});

    // clouds moving? 
    bool isCloud1Active{false};
    bool isCloud2Active{false};
    bool isCloud3Active{false};

    float cloud1Speed{0.0f};
    float cloud2Speed{0.0f};
    float cloud3Speed{0.0f};

    cloud1Speed = 0;
    cloud2Speed = 0;
    cloud3Speed = 0;

    Clock clock;

    RenderWindow window(vm, "Timber!!!", State::Fullscreen);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
            if (const auto* key = event->getIf<Event::KeyPressed>())
                if (key->code == Keyboard::Key::Escape)
                    window.close();
        }

        window.clear();
        Time dt = clock.restart();
        // set up the bee
        if (!isBeeActive) 
        {
            // how fast is the bee
            srand((int) time(0));
            beeSpeed = (rand() % 200) + 200;
            // how high is the bee
            srand((int) time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition({2000, height});
            isBeeActive = true;
        } else {
            // move the bee
            spriteBee.setPosition({spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y});

            // has bee reached left side of screen
            if (spriteBee.getPosition().x <= -100) 
            {
                isBeeActive = false;
            }
        }
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display();
    }

    return 0;
}



































































































































