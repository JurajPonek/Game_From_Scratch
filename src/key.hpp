#pragma once
#include <format>
#include <string_view>
namespace game
{
    enum class Key
    {
        ESC = 0x1b,
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4a,
        K = 0x4b,
        L = 0x4c,
        M = 0x4d,
        N = 0x4e,
        O = 0x4f,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5a
    };

    enum class KeyState
    {
        UP,
        DOWN
    };

};
template<>
struct std::formatter<game::Key>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return std::cbegin(ctx);
    }
    auto format(const game::Key& key, std::format_context& ctx) const
    {
        std::string_view s = "?";

        switch (key)
        {
            using enum game::Key;
            case ESC: s = "ESC"; break;
            case A:   s = "A";   break;
            case B:   s = "B";   break;
            case C:   s = "C";   break;
            case D:   s = "D";   break;
            case E:   s = "E";   break;
            case F:   s = "F";   break;
            case G:   s = "G";   break;
            case H:   s = "H";   break;
            case I:   s = "I";   break;
            case J:   s = "J";   break;
            case K:   s = "K";   break;
            case L:   s = "L";   break;
            case M:   s = "M";   break;
            case N:   s = "N";   break;
            case O:   s = "O";   break;
            case P:   s = "P";   break;
            case Q:   s = "Q";   break;
            case R:   s = "R";   break;
            case S:   s = "S";   break;
            case T:   s = "T";   break;
            case U:   s = "U";   break;
            case V:   s = "V";   break;
            case W:   s = "W";   break;
            case X:   s = "X";   break;
            case Y:   s = "Y";   break;
            case Z:   s = "Z";   break;
            default:  s = "Unknown"; break;
        }
        return std::format_to(ctx.out(), "{}\n", s);
    }
}; 
template<>
struct std::formatter<game::KeyState>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return std::cbegin(ctx);
    }
    auto format(const game::KeyState& key_state, std::format_context& ctx) const
    {
        switch (key_state) {
            using enum game::KeyState;
            case UP:
                return std::format_to(ctx.out(), "UP\n");
            case DOWN:
                return std::format_to(ctx.out(), "DOWN\n");
            default: 
                return std::format_to(ctx.out(), "UNKNOWN\n");
        }
    } 
};