#include "renderer.hpp"
#include "material.hpp"
#include "opengl.hpp"


namespace game
{
    Renderer::Renderer(Material material)
        : m_mesh({}), m_material(std::move(material))
    {
        ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void Renderer::render() const
    {
        ::glClear(GL_COLOR_BUFFER_BIT);
        ::glUseProgram(m_material.get_native_handle());
        m_mesh.bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 3);
        m_mesh.unbind();
    }


}