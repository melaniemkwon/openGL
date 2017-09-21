//
//  ball.cpp
//  HW1
//
//  Created by Melanie Kwon on 9/15/17.
//  Copyright © 2017 Melanie Kwon. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "ball.h"

#define PI 3.14159265358979324

#define MAX_RADIUS 10
#define MIN_RADIUS 1

#define MAX_VELOCITY 10
#define MIN_VELOCITY 1

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

void Ball::setVelocityDirection(double vd) {
    m_velocity_direction = vd;
}
/*
void Ball::setVelocity(double vx, double vy, double vm) {
    m_velocity_vectorX = vx;
    m_velocity_vectorY = vy;
    m_velocity_magnitude = vm;
}
*/
void Ball::setVelocityVector(double x, double y) {
    m_velocity_vectorX = x;
    m_velocity_vectorY = y;
}

void Ball::updateVelocityVector() {
    double t = 1; // time
    
    //double newX = balls[i].getX() + cos(directionInRadians) * balls[i].getVelocityMagnitude() * t;
    //double newY = balls[i].getY() + sin(directionInRadians) * balls[i].getVelocityMagnitude() * t;
    //double directionInRadians = balls[i].getVelocityDirection() * PI / 180;
    
    double directionInRadians = m_velocity_direction * PI / 180;
    // calculate new velocity vector
    m_velocity_vectorX = m_x + cos( directionInRadians ) * m_velocity_magnitude * t;
    m_velocity_vectorY = m_y + sin( directionInRadians ) * m_velocity_magnitude * t;
    std::cout << "new vector: " << m_velocity_vectorX << "," << m_velocity_vectorY << std::endl;
}

void Ball::updateVelocityDirectionFromVector() {
    
}

void Ball::incVelocityMagnitude(int x) {
    if (m_velocity_magnitude + x <= MAX_VELOCITY) { m_velocity_magnitude += x; }
}

void Ball::decVelocityMagnitude(int x) {
    if (m_velocity_magnitude - x >= MIN_VELOCITY) { m_velocity_magnitude -= x; }
}

double Ball::getVelocityDirection() {
    return m_velocity_direction;
}

double Ball::getVelocityVectorX() {
    return m_velocity_vectorX;
}

double Ball::getVelocityVectorY() {
    return m_velocity_vectorY;
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
