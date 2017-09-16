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
    Ball(int uid, double x, double y, int r, double m, double v, bool f);
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
    void setVelocity(double v);
    double getVelocity();
    
    void setFilled(bool filled);
    void toggleFilled();
    bool isFilled();
    
    void setNextCoord(double x, double y);
    double getNextX();
    double getNextY();
    
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
    double m_velocity;
    
    bool m_filled;
    
    double m_nextx;
    double m_nexty;
    
    float m_red;
    float m_green;
    float m_blue;
};

#endif /* ball_h */
