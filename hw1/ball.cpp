//
//  ball.cpp
//  Lab2
//
//  Created by Melanie Kwon on 9/15/17.
//  Copyright © 2017 Melanie Kwon. All rights reserved.
//

#include <stdio.h>
#include "ball.h"

Ball::Ball() {}
Ball::~Ball() {}

Ball::Ball(int id, double x, double y, int radius, bool filled) {
    m_id = id;
    m_x = x;
    m_y = y;
    m_radius = radius;
    m_filled = filled;
}

int Ball::getId() {
    return m_id;
}

void Ball::setCoord(double x, double y) {
    m_x = x;
    m_y = y;
}

double Ball::getX() {
    return m_x;
}

double Ball::getY() {
    return m_y;
}

void Ball::setRadius(int r) {
    m_radius = r;
}

int Ball::getRadius() {
    return m_radius;
}

void Ball::setFilled(bool filled) {
    m_filled = filled;
}

bool Ball::isFilled() {
    return m_filled;
}
