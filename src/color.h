#ifndef COLOR_H
#define COLOR_H

// color class of each shape
class Color{

public:
    Color(int r, int g, int b);
    void set_colors(int r, int g, int b);
    int get_r() const;
    int get_g() const;
    int get_b() const;
    Color& operator=(const Color &rhs);  
private:
    int m_r;
    int m_g;
    int m_b;
};


// overloaded operators
Color operator+(const Color &c1, const Color &c2); 
Color operator*(const Color &col, double k);
Color operator*(double k, const Color &col);

// clipping function.
int clip(int x);

#endif