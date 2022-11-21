#ifndef MAIN_HPP
#define MAIN_HPP

#include <SFML/Graphics.hpp>
#include "const.hpp"

typedef struct {
  int state;
} Game;

typedef struct {
  sf::RectangleShape chassis;
  sf::RectangleShape screen;
  sf::RectangleShape frontWheels[2];
  sf::RectangleShape backWheels[2];
  sf::CircleShape fumes[3];
  sf::Vector2f pos;
  sf::Vector2f displayPos;
  float speed;
  float turnAngle;
  float angle;
} Car;

typedef struct {
  sf::CircleShape body;
  sf::Vector2f pos;
  sf::Vector2f displayPos;
} Point;

#endif
