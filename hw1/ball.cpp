//
//  ball.cpp
//  HW1
//
//  Created by Melanie Kwon on 9/15/17.
//  Copyright © 2017 Melanie Kwon. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "ball.h"

Ball::Ball() {}
Ball::~Ball() {}

Ball::Ball(int id, double x, double y, int r, double m, double v, bool f) {
    m_id = id;
    m_x = x;
    m_y = y;
    m_radius = r;
    m_mass = m;
    m_velocity = v;
    m_filled = f;
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

void Ball::setMass(double m) {
    m_mass = m;
}

double Ball::getMass() {
    return m_mass;
}

void Ball::setVelocity(double v) {
    m_velocity = v;
}

double Ball::getVelocity() {
    return m_velocity;
}

void Ball::setFilled(bool filled) {
    m_filled = filled;
}

void Ball::toggleFilled() {
    m_filled = !m_filled;
}

bool Ball::isFilled() {
    return m_filled;
}

void Ball::setNextCoord(double x, double y) {
    m_nextx = x;
    m_nexty = y;
}

double Ball::getNextX() {
    return m_nextx;
}

double Ball::getNextY() {
    return m_nexty;
}

void Ball::setRGB(float r, float g, float b) {
    m_red = r;
    m_green = g;
    m_blue = b;
}

float Ball::getColorRed() {
    return m_red;
}

float Ball::getColorGreen() {
    return m_green;
}

float Ball::getColorBlue() {
    return m_blue;
}
