#include <iostream>
#include "color.h"
using namespace std;


Color::Color(int r, int g, int b){
    set_colors(r, g, b);
}

void Color::set_colors(int r, int g, int b){
    r = clip(r);
    g = clip(g);
    b = clip(b);
    m_r = r;
    m_g = g;
    m_b = b;
}

int Color::get_r() const {
    return m_r;
}

int Color::get_g() const {
    return m_g;
}

int Color::get_b() const {
    return m_b;
}

Color& Color::operator=(const Color &rhs){
    if(this == &rhs){
        return *this;
    }
    m_r = rhs.m_r;
    m_g = rhs.m_g;
    m_b = rhs.m_b;

    return *this;
}

Color operator+(const Color &c1, const Color &c2){
    int r = clip(c1.get_r() + c2.get_r());
    int g = clip(c1.get_g() + c2.get_g());
    int b = clip(c1.get_b() + c2.get_b());

    return Color(r, g, b); 
}

Color operator*(const Color &col, double k){
    int r = clip(col.get_r() * k);
    int g = clip(col.get_g() * k);
    int b = clip(col.get_b() * k);
    
    return Color(r, g, b);
}

Color operator*(double k, const Color &col){
    return (col * k);
}

int clip(int x){
    if(x > 255){
        x = 255;
    }
    if(x < 0){
        x = 0;
    }

    return x;
}
