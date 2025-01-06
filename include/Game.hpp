#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


class Game : private sf::NonCopyable
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::RenderWindow mWindow;
    sf::Texture      mTexture;
    sf::Sprite       mPlayer;
    sf::Time         mTimePerFrame;
    
    float mPlayerSpeed;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

#endif // BOOK_GAME_HPP