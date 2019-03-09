/**
 * @file ShaderProgram.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-04
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#pragma once
#include "geometry.hpp"
#include "Framebuffer.hpp"
/**
 * @brief Main class for processing models(triangles)
 * 
 */
class ShaderProgram
{
public:
    Framebuffer *fb;
    mat4 lookat;
    mat4 persp;
    fragment vertexShader(vertex const& v);
    pixel fragmentShader(vertex );
    void rasterize(fragment v1, fragment v2, fragment v3);
    //void draw(vertex const *, size_t const *, size_t) noexcept;
};