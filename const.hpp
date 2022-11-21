#ifndef CONST_HPP
#define CONST_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

// Window size
#define WIN_W 1200
#define WIN_H 800
#define FS 60

// Game states
#define ST_INIT 0
#define ST_PLAY 1
#define ST_PAUSE 2

// Car dimensions
#define CHASSIS_W 50
#define CHASSIS_H 80
#define CHASSIS_COLOR sf::Color::Green
#define SCREEN_W 40
#define SCREEN_H 20
#define SCREEN_COLOR sf::Color::Black
#define WHEEL_W 10
#define WHEEL_H 14
#define WHEEL_COLOR sf::Color::Red
#define CHASSIS_WHEEL_D ceil(sqrt((CHASSIS_W / 2) * (CHASSIS_W / 2) + (CHASSIS_H / 4) * (CHASSIS_H / 4)))
#define WHEEL_R CHASSIS_H / 2
#define CAR_ACC 30
#define CAR_TURN 1
#define CAR_MAX_TURN M_PI / 3

// Point dimensions
#define POINT_R 10
#define POINT_COLOR sf::Color::Blue

#endif
