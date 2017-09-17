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

#define MAX_RADIUS 10
#define MIN_RADIUS 2

Ball::Ball() {}
Ball::~Ball() {}

Ball::Ball(int id, double x, double y, int r, bool f) {
    m_id = id;
    m_x = x;
    m_y = y;
    m_radius = r;
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
    if (r >= MIN_RADIUS && r <= MAX_RADIUS) { m_radius = r; }
}

void Ball::incRadius(int x) {
    int cond = m_radius + x;
    if (cond <= MAX_RADIUS) {
        m_radius += x;
        
        // When radius increases, its mass must be increased
        double m_massNew = m_mass + x;
        
        // Velocity v must be decreased using the equation: v’ = Mv/M’
        // where v’ is the decreased v and M’ is the increased M
        m_velocity_magnitude = m_mass * m_velocity_magnitude / m_massNew;
        
        m_mass = m_massNew;
    }
}

void Ball::decRadius(int x) {
    int cond = m_radius - x;
    if (cond >= MIN_RADIUS) {
        m_radius -= x;
        
        // When radius decreases, its mass must be decreased
        double m_massNew = m_mass - x;
        
        // Velocity v must be increased using the equation: v’ = Mv/M’
        // where v’ is the increased v and M’ is the decreased M
        m_velocity_magnitude = m_mass * m_velocity_magnitude / m_massNew;
        
        m_mass = m_massNew;
    }
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

void Ball::setVelocity(double vd, double vm) {
    m_velocity_direction = vd;
    m_velocity_magnitude = vm;
}

double Ball::getVelocityDirection() {
    return m_velocity_direction;
}

double Ball::getVelocityMagnitude() {
    return m_velocity_magnitude;
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
