#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "main.hpp"
#include "const.hpp"

// Global variables
Game game;
Car car;
sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "autobahn");

void updateDisplayPos(sf::Vector2f &pos, sf::Vector2f &displayPos) {
  displayPos.x = WIN_W / 2 + pos.y;
  displayPos.y = WIN_H / 2 - pos.x;
}

// input: fuel, direction
// output: force
void update(float dt) {
  float staticFriction = (car.momentum == 0) ? TAR_S_FRICTION * GRAVITY * CAR_MASS * dt : 0;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && car.momentum > 0) {
    car.momentum -= BRAKING_F * dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && car.momentum < MAX_MOMENTUM) {
    car.momentum += ENGINE_F * dt / fabs(car.gear) - staticFriction;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && car.turnAngle < CAR_MAX_TURN) {
    car.turnAngle += CAR_TURN * dt;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && car.turnAngle > -CAR_MAX_TURN) {
    car.turnAngle -= CAR_TURN * dt;
  }

  float kineticFriction = TAR_K_FRICTION * GRAVITY * CAR_MASS * dt;
  if (car.momentum > kineticFriction) car.momentum -= kineticFriction;
  else if (car.momentum < -kineticFriction) car.momentum += kineticFriction;
  else car.momentum = 0;

  float distance = car.gear * car.momentum * dt / CAR_MASS;
  if (car.turnAngle != 0) {
    float turnRadius = WHEEL_R / sin(car.turnAngle * 0.9);
    float turnTheta = distance / turnRadius;
    car.angle += turnTheta / 2;
    float driveDist = copysignf(sqrtf(2 * turnRadius * turnRadius * (1 - cos(turnTheta))), distance);
    car.pos += sf::Vector2f(driveDist * cos(car.angle), driveDist * sin(car.angle));
  } else {
    car.pos += sf::Vector2f(distance * cos(car.angle), distance * sin(car.angle));
  }

  float angleDegrees = car.angle * 180 / M_PI;
  float turnAngleDegrees = car.turnAngle * 180 / M_PI;
  updateDisplayPos(car.pos, car.displayPos);
  car.chassis.setPosition(car.displayPos);
  car.chassis.setRotation(angleDegrees);
  car.screen.setPosition(car.displayPos);
  car.screen.setRotation(angleDegrees);
  for (int i = 0; i < 2; i++) {
    float wheelAngle = car.angle - M_PI / 4 + i * M_PI / 2;
    sf::Vector2f wheelPos = car.pos + sf::Vector2f(CHASSIS_WHEEL_D * cos(wheelAngle), CHASSIS_WHEEL_D * sin(wheelAngle));
    sf::Vector2f wheelDisplayPos;
    updateDisplayPos(wheelPos, wheelDisplayPos);
    car.frontWheels[i].setPosition(wheelDisplayPos);
    car.frontWheels[i].setRotation(angleDegrees + turnAngleDegrees);
  }
  for (int i = 0; i < 2; i++) {
    car.backWheels[i].setPosition(car.displayPos);
    car.backWheels[i].setRotation(angleDegrees);
  }
}

void draw() {
  window.clear();

  for (int i = 0; i < 2; i++) {
    window.draw(car.frontWheels[i]);
  }
  for (int i = 0; i < 2; i++) {
    window.draw(car.backWheels[i]);
  }
  window.draw(car.chassis);
  window.draw(car.screen);

  window.display();
}

void restart() {
  game.state = ST_INIT;

  car.pos = sf::Vector2f(0, 0);
  car.gear = 1;
  car.momentum = 0;
  car.angle = 0;
  car.turnAngle = 0;
  car.chassis.setSize(sf::Vector2f(CHASSIS_W, CHASSIS_H));
  car.chassis.setOrigin(sf::Vector2f(CHASSIS_W / 2, CHASSIS_H / 2));
  car.chassis.setFillColor(CHASSIS_COLOR);
  car.screen.setSize(sf::Vector2f(SCREEN_W, SCREEN_H));
  car.screen.setOrigin(sf::Vector2f(SCREEN_W / 2, SCREEN_H / 2 + CHASSIS_H / 4));
  car.screen.setFillColor(SCREEN_COLOR);
  for (int i = 0; i < 2; i++) {
    car.frontWheels[i].setSize(sf::Vector2f(WHEEL_W, WHEEL_H));
    car.frontWheels[i].setOrigin(sf::Vector2f(WHEEL_W / 2, WHEEL_H / 2));
    car.frontWheels[i].setFillColor(WHEEL_COLOR);
  }
  for (int i = 0; i < 2; i++) {
    car.backWheels[i].setSize(sf::Vector2f(WHEEL_W, WHEEL_H));
    float wheelAngle = - M_PI / 4 + i * M_PI / 2;
    car.backWheels[i].setOrigin(sf::Vector2f(WHEEL_W / 2 + CHASSIS_WHEEL_D * sin(wheelAngle), WHEEL_H /  2 - CHASSIS_WHEEL_D * cos(wheelAngle)));
    car.backWheels[i].setFillColor(WHEEL_COLOR);
  }
}

int main() {
  srand(time(0));
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(FS);
  sf::Clock clock;
  restart();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::Escape:
              window.close();
              break;
            case sf::Keyboard::R:
              if (car.momentum < TAR_K_FRICTION * GRAVITY * CAR_MASS / 10) car.gear = -1;
              break;
            case sf::Keyboard::Num1:
              if (car.gear > 0 || car.momentum < TAR_K_FRICTION * GRAVITY * CAR_MASS / 10) car.gear = 1;
              break;
            case sf::Keyboard::Num2:
              if (car.gear > 0) car.gear = 2;
              break;
          }
          break;
      }
    }
    float dt = clock.restart().asSeconds();
    update(dt);
    draw();
  }
  
  return 0;
}
