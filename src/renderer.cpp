#include "renderer.hpp"
#include "material.hpp"
#include "opengl.hpp"
#include "matrix4.hpp"
#include "scene.hpp"
#include "vector3.hpp"
#include <gl/gl.h>
#include "camera.hpp"

namespace game
{
    void Renderer::render(const Camera& camera, const Scene& scene) const
    {
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(const auto* entity : scene.m_entities)
        {
             
            const auto* material = entity->get_material();\
            const auto* mesh = entity->get_mesh();
        
            ::glUseProgram(material->get_native_handle());

            const auto model_location = ::glGetUniformLocation(material->get_native_handle(), "model");
            ::glUniformMatrix4fv(model_location, 1, GL_FALSE, entity->get_model_matrix().data());
            
                    

            const auto view_location = ::glGetUniformLocation(material->get_native_handle(), "view");
            ::glUniformMatrix4fv(view_location, 1, GL_FALSE, camera.get_view().data());

            const auto projection_location = ::glGetUniformLocation(material->get_native_handle(), "projection");
            ::glUniformMatrix4fv(projection_location, 1, GL_FALSE, camera.get_projection().data());

            mesh->bind();
            ::glDrawArrays(GL_TRIANGLES, 0, 36);
            mesh->unbind();
        }
    }


}