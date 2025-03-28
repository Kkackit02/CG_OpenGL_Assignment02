#ifndef PLANE_H
#define PLANE_H

#include "Surface.h"

class Plane : public Surface {
public:
    glm::vec3 point;  // ��� ���� �� ��
    glm::vec3 normal; // ����� ���� ����


    Plane(const Material& _material, glm::vec3 _point, glm::vec3 _normal)
    : Surface(_material), point(_point) , normal(_normal)
    { }

    virtual bool intersect(const Ray& ray, float& t_hit, glm::vec3& hit_point, glm::vec3& normal_out) const override;
};

#endif 