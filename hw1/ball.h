//
//  ball.h
//  Lab2
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
    Ball(int uid, double x, double y, int radius, bool filled);
    int getId();
    void setCoord(double x, double y);
    double getX();
    double getY();
    void setRadius(int r);
    int getRadius();
    void setFilled(bool filled);
    bool isFilled();
private:
    int m_id;
    double m_x;
    double m_y;
    int m_radius;
    bool m_filled;
};

#endif /* ball_h */
