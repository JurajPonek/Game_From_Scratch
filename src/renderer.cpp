#include "renderer.hpp"
#include "buffer_writer.hpp"
#include "color.hpp"
#include "material.hpp"
#include "opengl.hpp"
#include "matrix4.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include <gl/gl.h>
#include <ranges>
#include "camera.hpp"
#include "vendor/opengl/glext.h"

namespace
{
    struct LightBuffer
    {
        alignas(16) game::Color ambient;
        alignas(16) game::Vector3 direction;
        alignas(16) game::Color direction_color;
        alignas(16) game::Vector3 point;
        alignas(16) game::Color point_color;
    };

}


namespace game
{
    Renderer::Renderer() : 
    m_camera_buffer {sizeof(Matrix4) * 2 + sizeof(Vector3)}, m_light_buffer(sizeof(LightBuffer))
    {

    }
    void Renderer::render(const Camera& camera, const Scene& scene) const
    {
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            BufferWriter writer{m_camera_buffer};
            writer.write(camera.get_view());
            writer.write(camera.get_projection());
            writer.write(camera.get_position());
        }

        {
            LightBuffer light_buffer{scene.ambient, scene.directional.direction, scene.directional.color, scene.point.position, scene.point.color};
            BufferWriter writer{m_light_buffer};
            writer.write(light_buffer);
            
        }
        ::glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_camera_buffer.get_native_handle());
        ::glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_light_buffer.get_native_handle());
        for(const auto* entity : scene.m_entities)
        {
             
            const auto* material = entity->get_material();         
            const auto* mesh = entity->get_mesh();
            const auto textures = entity->get_textures();
            const auto* sampler = entity->get_sampler();
        
            ::glUseProgram(material->get_native_handle());

            const auto model_location = ::glGetUniformLocation(material->get_native_handle(), "model");
            ::glUniformMatrix4fv(model_location, 1, GL_FALSE, entity->get_model_matrix().data());
            for (const auto& [index, tex] : entity->get_textures() | std::views::enumerate)
            {
                ::glBindTextureUnit(index, tex->get_native_handle());
                ::glBindSampler(index, sampler->get_native_handle());
                const auto uniform_name = std::format("tex{}", index);
                const auto texture_uniform = ::glGetUniformLocation(material->get_native_handle(), uniform_name.c_str());
                ::glUniform1i(texture_uniform, index);
            }
            
            
        

            mesh->bind();
            ::glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, reinterpret_cast<void*>(mesh->get_index_offset()));
            mesh->unbind();
        }
    }


}