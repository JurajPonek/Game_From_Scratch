#pragma once
#include <concepts>
#include <functional>
#include <memory>
namespace game
{
    template<typename T, T Invalid={}>
    class AutoRelease
    {
        public:
            AutoRelease() : AutoRelease(Invalid, nullptr)
            {

            }
            AutoRelease(T object, std::function<void(T)> deleter)
            : m_object(object), m_deleter(deleter)
            {

            }
            ~AutoRelease()
            {
                if (m_object != Invalid && m_deleter)
                {
                    m_deleter(m_object);
                }
                
            }
            AutoRelease(const AutoRelease&) = delete;
            AutoRelease& operator=(const AutoRelease&) = delete;
            AutoRelease(AutoRelease&& other) : m_object(Invalid), m_deleter(nullptr)
            {
                swap(other);
            }
            AutoRelease& operator=(AutoRelease&& other)
            {
                AutoRelease newObj {std::move(other)};
                swap(newObj);
                return *this;

          }
            void swap(AutoRelease& other)
            {
                std::ranges::swap(m_object, other.m_object);
                std::ranges::swap(m_deleter, other.m_deleter);
            }

            T get() const
            {
                return m_object;
            }

            operator T() const
            {
                return m_object;
            }

            T* operator&() noexcept
            {
                return std::addressof(m_object);
            }


        private:
            T m_object;
            std::function<void(T)> m_deleter;
    };



}