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
        // manage the clouds
        // cloud 1
        if (!isCloud1Active) 
        {
            // how fast is the cloud
            srand((int) time(0) * 10);
            cloud1Speed = (rand() % 200);
            srand((int) time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition({-300, height});
            isCloud1Active = true;
        } else 
        {
            spriteCloud1.setPosition({spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y});
            // cloud out of bounds
            if (spriteCloud1.getPosition().x >= 1920) 
            {
                isCloud1Active = false;
            }
        }
        // cloud 2
        if (!isCloud2Active)
        {
            // how fast
            srand((int) time(0) * 20);
            cloud2Speed = (rand() % 200);
            srand((int) time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition({-300, height});
            isCloud2Active = true;
        } else 
        {
            spriteCloud2.setPosition({spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y});
            // cloud out of bounds?
            if (spriteCloud2.getPosition().x >= 1920)
            {
                isCloud2Active = false;
            }
        }
        // cloud 3
        if (!isCloud3Active)
        {
            // how fast
            srand((int) time(0) * 30);
            cloud3Speed = (rand() % 200);
            // how high
            srand((int) time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition({-300, height});
            isCloud3Active = true;
        } else 
        {
            spriteCloud3.setPosition({spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y});
            // cloud out of bounds
            if (spriteCloud3.getPosition().x >= 1920) 
            {
                isCloud3Active = false;
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



































































































































