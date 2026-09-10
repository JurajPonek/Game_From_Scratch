#include "renderer.hpp"
#include "buffer_writer.hpp"
#include "material.hpp"
#include "opengl.hpp"
#include "matrix4.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include <gl/gl.h>
#include "camera.hpp"
#include "vendor/opengl/glext.h"

namespace game
{
    Renderer::Renderer() : 
    m_camera_buffer {sizeof(Matrix4) * 2}
    {

    }
    void Renderer::render(const Camera& camera, const Scene& scene) const
    {
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            BufferWriter writer{m_camera_buffer};
            writer.write(camera.get_view());
            writer.write(camera.get_projection());
        }
        ::glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_camera_buffer.get_native_handle());
        for(const auto* entity : scene.m_entities)
        {
             
            const auto* material = entity->get_material();         
            const auto* mesh = entity->get_mesh();
            const auto* texture = entity->get_texture();
            const auto* sampler = entity->get_sampler();
        
            ::glUseProgram(material->get_native_handle());

            const auto model_location = ::glGetUniformLocation(material->get_native_handle(), "model");
            ::glUniformMatrix4fv(model_location, 1, GL_FALSE, entity->get_model_matrix().data());

            ::glBindTextureUnit(0, texture->get_native_handle());
            ::glBindSampler(0, sampler->get_native_handle());
            
            const auto texture_uniform = ::glGetUniformLocation(material->get_native_handle(), "sampler");
            ::glUniform1i(texture_uniform, 0);

            mesh->bind();
            ::glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, reinterpret_cast<void*>(mesh->get_index_offset()));
            mesh->unbind();
        }
    }


}