#include "sampler.hpp"

namespace game
{
    Sampler::Sampler() 
        :m_handle{0u, [](auto sampler){::glDeleteSamplers(1, &sampler);}}
    {
        ::glCreateSamplers(1, &m_handle);
        
    }
    ::GLuint Sampler::get_native_handle() const { return m_handle; }

} // namespace game
