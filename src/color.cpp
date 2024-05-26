// Description: Implementation of color constants and related functions.

#include "header/color.h"

// Color constants
const sf::Color dark_grey = {26, 31, 40, 150};

const sf::Color outer_green = {0, 204, 0, 255};
const sf::Color outer_red = {204, 0, 0, 255};
const sf::Color outer_orange = {204, 102, 0, 255};
const sf::Color outer_yellow = {235, 235, 0, 255};
const sf::Color outer_purple = {204, 0, 204, 255};
const sf::Color outer_cyan = {0, 204, 204, 255};
const sf::Color outer_blue = {0, 0, 204, 255};

const sf::Color inner_green = {41, 225, 41, 255};
const sf::Color inner_red = {240, 48, 48, 255};
const sf::Color inner_orange = {230, 128, 27, 255};
const sf::Color inner_yellow = {255, 255, 30, 255};
const sf::Color inner_purple = {255, 51, 255, 255};
const sf::Color inner_cyan = {51, 255, 255, 255};
const sf::Color inner_blue = {51, 51, 255, 255};

const sf::Color lightBlue = {0, 191, 255, 150};

// Get outer cell colors
std::vector<sf::Color> getOuterCellColors() {
    return {dark_grey, outer_green, outer_red, outer_orange, outer_yellow, outer_purple, outer_cyan, outer_blue};
}

// Get inner cell colors
std::vector<sf::Color> getInnerCellColors() {
    return {dark_grey, inner_green, inner_red, inner_orange, inner_yellow, inner_purple, inner_cyan, inner_blue};
}
