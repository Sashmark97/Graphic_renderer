/**
 * @file main.cpp
 * @author 8ScareT8
 * @brief Source file for making triangles
 * @version 0.1
 * @date 2018-11-02
 * 
 * @copyright Copyright (c) 2018
 * 
 */

/** @mainpage Graphon
 *
 * @section intro_sec Introduction
 *
 * This is the program for interaction with the screen in linux. Currently it is capable of drawing triangles on the screen.
 *
 * @section install_sec Components
 *
 * @subsection framebuff Framebuffer
 * Main class for interaction with the screen(fb0 device).
 * @see Framebuffer
 * 
 * @subsection shaderprog Shader Program
 * Main class for processing models(triangles)
 * @see ShaderProgram
 * 
 * @subsection geom Geometry
 * Combination of Linear algebra's methods and objects
 * 
 * @see geometry.cpp
 */

#include "Framebuffer.hpp"
#include "geometry.hpp"
#include "ShaderProgram.hpp"
#include "Mouse.hpp"
#include <cmath>
#include <algorithm>
vertex verts[] =
{
    {{-0.5f, -0.5f, 0.5f}, {0, 0, 0, 255}},
    {{-0.5f, 0.5f, 0.5f}, {255, 0, 0, 255}},
    {{0.5f, -0.5f, 0.5f}, {0, 255, 0, 255}},
    {{0.5f, 0.5f, 0.5f}, {0, 0, 0, 255}},
};
int index[] =
{
    0, 1, 2, 1, 2, 3
};
int main()
{
    Framebuffer fb;
    ShaderProgram sp;
    MouseEvent e;
    sp.fb = &fb;
    float phi = 1.5f;
    float theta = -0.0f;
    vec3 up = {0.f, 1.f, 0.f};
    vec3 pos = {0.f, 0.f, -2.f};
    sp.persp = perspective(0.1f, 1000.f, 1.f, (float)fb.get_width() / fb.get_height());
    bool keepLoopGoing = true;
    while(keepLoopGoing)
    {
        while(PollMouseEvent(e))
        {
            phi -= 0.01f * e.xrel();
            theta += 0.01f * e.yrel();
        }
        vec3 dir = {std::sin(phi) * std::cos(theta), std::sin(theta), std::cos(phi) * std::cos(theta)};
        sp.lookat = lookAt(dir, vec3(0.f, 0.f, 0.f), up); 
        fb.clear();
        for(int i = 0; i < sizeof(index) / sizeof(int); i += 3)
        {
            sp.rasterize(sp.vertexShader(verts[index[i]]), sp.vertexShader(verts[index[i + 1]]), sp.vertexShader(verts[index[i + 2]]));
        }
        fb.update();
            
        //fb.update();
    }
}