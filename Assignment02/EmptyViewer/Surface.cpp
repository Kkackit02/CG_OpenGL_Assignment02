#include "Surface.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

glm::vec3 Surface::shade(const Ray& ray,
    const glm::vec3& hit_point,
    const glm::vec3& normal,
    const Light& light) const
{
    // 뷰 벡터: 카메라 방향
    glm::vec3 V = glm::normalize(-ray.direction);

    // 광원 벡터: 히트 지점에서 광원까지
    glm::vec3 L = glm::normalize(light.position - hit_point);

    // 반사 벡터 (Phong reflection)
    glm::vec3 R = glm::reflect(-L, normal);

    // Ambient
    glm::vec3 ambient = material.ka * light.intensity;

    // Diffuse
    float diff = std::max(glm::dot(normal, L), 0.0f);
    glm::vec3 diffuse = material.kd * diff * light.intensity;

    // Specular
    float spec = std::pow(std::max(glm::dot(R, V), 0.0f), material.specularPower);
    glm::vec3 specular = material.ks * spec * light.intensity;

    glm::vec3 color = ambient + diffuse + specular;

    return glm::clamp(color, 0.0f, 1.0f); // [0,1] 범위로 클램핑
}
