#ifndef GEOMETRY_H
#define GEOMETRY_H

class Geometry {
  public:
    virtual void draw(float dt) = 0;
    float get_x();
    float get_y();
    float get_z();
    float get_w();
    float get_h();
    bool collide_cicle(float x, float z, float radius);
    virtual ~Geometry() {};
  protected:
    Geometry(float x, float y, float z, float w, float h);
    float x, y, z, w, h;
};

#endif /* GEOMETRY_H */
