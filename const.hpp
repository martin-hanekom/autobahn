#ifndef CONST_HPP
#define CONST_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

// Window size
#define WIN_W 1600
#define WIN_H 900
#define FS 60

// Game states
#define ST_INIT 0
#define ST_PLAY 1
#define ST_PAUSE 2

// Physical dimensions
#define GRAVITY 9.81
#define TAR_S_FRICTION 5
#define TAR_K_FRICTION 3

// Car dimensions
#define CHASSIS_W 30
#define CHASSIS_H 50
#define CHASSIS_COLOR sf::Color::Green
#define SCREEN_W 25
#define SCREEN_H 15
#define SCREEN_COLOR sf::Color::Black
#define WHEEL_W 8
#define WHEEL_H 12
#define WHEEL_COLOR sf::Color::Red
#define CHASSIS_WHEEL_D ceil(sqrt((CHASSIS_W / 2) * (CHASSIS_W / 2) + (CHASSIS_H / 4) * (CHASSIS_H / 4)))
#define WHEEL_R CHASSIS_H / 2
#define CAR_ACC 30
#define CAR_FRICTION 0.997
#define CAR_SLOW_FRICTION 0.1
#define CAR_BRAKE 0.97
#define CAR_BRAKE_MIN 2
#define CAR_TURN 1
#define CAR_MAX_TURN M_PI / 6

#define CAR_MASS 1000
#define ENGINE_F 150000
#define BRAKING_F 120000
#define MAX_MOMENTUM 200000

// Point dimensions
#define POINT_R 10
#define POINT_COLOR sf::Color::Blue

#endif
