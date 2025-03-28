#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "Ray.h"

class Camera {
public:
    
     glm::vec3 position; // ī�޶� ��ġ
      glm::vec3 u, v, w;  // ī�޶� ��ǥ�� (������, ����, �ٶ󺸴� ����)
      float l, r, b, t, d; // ���� ������Ʈ�� ����
      int nx, ny; // �̹��� �ػ�

      Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, float _l, float _r, float _b, float _t, float _d, int _nx, int _ny);
      Ray getRay(int i, int j) const;
};

#endif 