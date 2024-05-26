#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

// Color constants
extern const sf::Color dark_grey;
extern const sf::Color outer_green;
extern const sf::Color outer_red;
extern const sf::Color outer_orange;
extern const sf::Color outer_yellow;
extern const sf::Color outer_purple;
extern const sf::Color outer_cyan;
extern const sf::Color outer_blue;

extern const sf::Color inner_orange;
extern const sf::Color inner_green;
extern const sf::Color inner_red;
extern const sf::Color inner_yellow;
extern const sf::Color inner_purple;
extern const sf::Color inner_cyan;
extern const sf::Color inner_blue;

extern const sf::Color lightBlue;

// Get outer cell colors
std::vector<sf::Color> getOuterCellColors();

// Get inner cell colors
std::vector<sf::Color> getInnerCellColors();
