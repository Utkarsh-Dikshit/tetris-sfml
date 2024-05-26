#include "header/game.h"

int main()
{
    // Create an instance of the Game class
    Game game;

    // Create the game window
    sf::RenderWindow window(sf::VideoMode(game.minimum_screen_width, game.minimum_screen_height), "Tetris");
    window.setFramerateLimit(60);

    // Load and set the game icon
    sf::Image image_icon;
    image_icon.loadFromFile("resources/icon/tetris.png");
    window.setIcon(image_icon.getSize().x, image_icon.getSize().y, image_icon.getPixelsPtr());

    while (window.isOpen())
    {
        // Clear the window
        window.clear(sf::Color::Black);

        // Update drawable entities (blocks, grid, UI elements)
        game.updateDrawableEntity(window);

        // Draw the game
        game.drawGame(window);

        // Handle user input
        game.inputHandler(window);

        // Display the updated window
        window.display();
    }

    return 0;
}
