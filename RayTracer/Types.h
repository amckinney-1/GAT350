#pragma once
#include <glm.hpp>
#include <gtx/compatibility.hpp>
#include <gtx/norm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <gtx/color_space.hpp>

#include <sdl.h>

using color_t = SDL_Color;

inline color_t Vec3ToColor(const glm::vec3& vec3)
{
    color_t color;

    color.r = static_cast<std::uint8_t>(glm::clamp(vec3[0], 0.0f, 1.0f) * 255);
    color.g = static_cast<std::uint8_t>(glm::clamp(vec3[1], 0.0f, 1.0f) * 255);
    color.b = static_cast<std::uint8_t>(glm::clamp(vec3[2], 0.0f, 1.0f) * 255);
    color.a = 0;

    return color;
}