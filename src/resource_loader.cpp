#include "resource_loader.hpp"
#include "src/error.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ios>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>


namespace
{
    std::string load(const std::filesystem::path& path, auto open_mode)
    {
        std::ifstream file{path, open_mode};
        game::ensure(!!file, "Failed to open file");
        std::stringstream ss{};
        ss << file.rdbuf();
        return ss.str();
    }
} // namespace
namespace game
{
    ResourceLoader::ResourceLoader(const std::filesystem::path& root) : m_root(root) {}
    std::string ResourceLoader::load_string(std::string_view name) const { return load(m_root / name, std::ios::in); }
    std::vector<std::byte> ResourceLoader::load_binary(std::string_view name) const
    {
        const auto data = load(m_root / name, std::ios::in | std::ios::binary);
        return data | std::views::transform([](auto b) { return static_cast<std::byte>(b); }) |
               std::ranges::to<std::vector>();
    }
} // namespace game