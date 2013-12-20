#ifndef BITMAP_H
#define BITMAP_H

#include <string>

class Bitmap {

  public:
    Bitmap(const std::string& path);
    ~Bitmap();

    unsigned get_id();
    unsigned get_width();
    unsigned get_height();

    float intensity_at(int i);

    unsigned short operator[](int i);

  private:
    unsigned short* pixels;
    unsigned id;
    unsigned width;
    unsigned height;
};

#endif /* BITMAP_H */