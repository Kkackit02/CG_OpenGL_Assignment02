#include "Surface.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

using namespace std;

glm::vec3 Surface::shade(const Ray& ray,
    const glm::vec3& hit_point,
    const glm::vec3& normal,
    const Light& light, 
    const std::vector<Surface*>& surfaces) const
{
    // �� ����: ī�޶� ����
    glm::vec3 V = glm::normalize(-ray.direction);

    // ���� ����: ��Ʈ �������� ��������
    glm::vec3 L = glm::normalize(light.position - hit_point);


    // ������ �ٸ� ������Ʈ�� ������ �׸��� ����
    Ray shadowRay(hit_point + 1e-4f * normal, L); // �����ϰ� ������ �༭ ǥ�鿡�� �ٷ� �������� �ʵ���

    for (const auto& obj : surfaces)
    {
        float t_shadow;
        glm::vec3 shadow_hit, shadow_normal;

        // �� ������ � ������Ʈ�� �����Ѵٸ�,
        if (obj->intersect(shadowRay, t_shadow, shadow_hit, shadow_normal))
        {
            // �������� �Ÿ����� ª�� ������ �׸�����
            if (t_shadow > 0.001f && t_shadow < glm::length(light.position - hit_point))
            {
                return material.ka * light.intensity; // ambient�� ��ȯ
            }
        }
    }

    // �ݻ� ���� (Phong reflection)
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

    return glm::clamp(color, 0.0f, 1.0f); // [0,1] ������ Ŭ����
}
