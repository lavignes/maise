#ifndef PLANE_H
#define PLANE_H

class Plane {
  public:
    Plane(float x, float y, float z, float yaw);
    void phys(float dt);

    float get_x();
    float get_y();
    float get_z();

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);

    float get_roll();
    void set_roll(float roll);

    float get_pitch();
    void set_pitch(float pitch);

    float get_speed();
    void set_speed(float speed);

    float get_yaw();
    void set_yaw(float yaw);
    
  private:
    float x, y, z;
    float v;
    float pitch;
    float yaw;
    float roll;
};

#endif /* PLANE_H */
