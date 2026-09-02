#include "renderer.hpp"
#include "material.hpp"
#include "opengl.hpp"
#include "matrix4.hpp"
#include "vector3.hpp"
#include <cmath>
#include <gl/gl.h>
#include <numbers>
#include "camera.hpp"

namespace game
{
    Renderer::Renderer(Material material)
        : m_mesh({}), m_material(std::move(material))
    {
        ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void Renderer::render(const Camera& camera) const
    {
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ::glUseProgram(m_material.get_native_handle());

        static constexpr auto model= Matrix4{Vector3{0.0f,0.0f,0.0f} };
        const auto model_location = ::glGetUniformLocation(m_material.get_native_handle(), "model");
        ::glUniformMatrix4fv(model_location, 1, GL_FALSE, model.data().data());
        
         

        const auto view_location = ::glGetUniformLocation(m_material.get_native_handle(), "view");
        ::glUniformMatrix4fv(view_location, 1, GL_FALSE, camera.get_view().data());

        const auto projection_location = ::glGetUniformLocation(m_material.get_native_handle(), "projection");
        ::glUniformMatrix4fv(projection_location, 1, GL_FALSE, camera.get_projection().data());

        m_mesh.bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 36);
        m_mesh.unbind();
    }


}