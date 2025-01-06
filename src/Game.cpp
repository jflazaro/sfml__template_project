#include "Game.hpp"
#include <iostream>

Game::Game()
: mWindow(sf::VideoMode(1920, 1080), "SFML Application", sf::Style::Close)
, mTexture()
, mPlayer()
, mTimePerFrame()
, mPlayerSpeed(180.f)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
{
    mWindow.setFramerateLimit(144);

    mTimePerFrame = sf::seconds(1.f / 60.f);

    if (!mTexture.loadFromFile("Media/Textures/Eagle.png"))
	{
        std::cout << "ERROR loading texture" << std::endl;
		// Handle loading error
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        
        while (timeSinceLastUpdate > mTimePerFrame)
        {
            timeSinceLastUpdate -= mTimePerFrame;

            processEvents();
            update(mTimePerFrame);
        }
        render();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::processEvents()
{
    for (auto event = sf::Event(); mWindow.pollEvent(event);)
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= mPlayerSpeed;
	if (mIsMovingDown)
		movement.y += mPlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= mPlayerSpeed;
	if (mIsMovingRight)
		movement.x += mPlayerSpeed;
		
	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}
