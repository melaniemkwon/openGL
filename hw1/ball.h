//
//  ball.h
//  HW1
//
//  Created by Melanie Kwon on 9/15/17.
//  Copyright © 2017 Melanie Kwon. All rights reserved.
//

#ifndef ball_h
#define ball_h

class Ball {
    
public:
    Ball();
    ~Ball();
    Ball(int uid, double x, double y, int r, bool f);
    int getId();
    void setCoord(double x, double y);
    double getX();
    double getY();
    void setRadius(int r);
    int getRadius();
    void incRadius(int x);
    void decRadius(int x);
    
    void setMass(double m);
    double getMass();
    void setVelocity(double vx, double vy, double vm);
    void setVelocityVector(double x, double y);
    void incVelocityMagnitude(int x);
    void decVelocityMagnitude(int x);
    
    double getVelocityVectorX();
    double getVelocityVectorY();
    double getVelocityMagnitude();
    
    void move();
    
    void setFilled(bool filled);
    void toggleFilled();
    bool isFilled();
    
    void setRGB(float r, float g, float b);
    float getColorRed();
    float getColorGreen();
    float getColorBlue();
private:
    int m_id;
    double m_x;
    double m_y;
    int m_radius;
    
    double m_mass;
    double m_velocity_vectorX;
    double m_velocity_vectorY;
    double m_velocity_magnitude;
    
    bool m_filled;
    
    float m_red;
    float m_green;
    float m_blue;
};

#endif
