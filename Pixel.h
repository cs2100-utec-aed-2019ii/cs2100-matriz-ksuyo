#ifndef CS2100_MATRIZ_KSUYO_PIXEL_H
#define CS2100_MATRIZ_KSUYO_PIXEL_H


struct Pixel {
    unsigned short r, g, b;
    Pixel (const unsigned short& r, const unsigned short& g, const unsigned short& b): r{r}, g{g}, b{b} {};

    float avg () {
        return (float)(r+g+b)/3.0f;
    }

    void set () {
        if (this->avg() < 120){
            r = g = b = 0;
        } else {
            r = g = b = 255;
        }
    }

};


#endif