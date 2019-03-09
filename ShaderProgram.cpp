#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"
#include "geometry.hpp"
#include <cmath>
#include <algorithm>

fragment ShaderProgram::vertexShader(vertex const& v)
{
    return{persp * lookat * vec4(v.pos), v};
}

/**
 * @brief Mixes color of the three pixels
 * 
 * @param c1 
 * @param c2 
 * @param c3 
 * @param p X coordinate of current vector
 * @param q Y coordinate of current vector
 * @return pixel Resulting color of the pixel
 */
pixel ShaderProgram::fragmentShader(vertex v)
{
	return v.c;
}
vertex mix(vertex const& v1,vertex const& v2,vertex const& v3, float a, float b, float c)
{
    vec3 pos = {(a * v1.pos.x + b * v2.pos.x + c * v3.pos.x) / (a + b + c),
                (a * v1.pos.y + b * v2.pos.y + c * v3.pos.y) / (a + b + c),
                (a * v1.pos.z + b * v2.pos.z + c * v3.pos.z) / (a + b + c)};
    pixel color = {(a * v1.c.b + b * v2.c.b + c * v3.c.b) / (a + b + c),
                   (a * v1.c.g + b * v2.c.g + c * v3.c.g) / (a + b + c),
                   (a * v1.c.r + b * v2.c.r + c * v3.c.r) / (a + b + c),
                   255};
    return {pos, color};
}
/**
 * @brief Builds a triangle with gradient of color
 * 
 * @param v1 First vertex of the triangle
 * @param v2 Second vertex of the triangle
 * @param v3 Third vertex of the triangle
 */
void ShaderProgram::rasterize(fragment f1, fragment f2, fragment f3)
{
    int w2 = fb->get_width() / 2;
    int h2 = fb->get_height() / 2;
    vec3 v1(f1.glob);
    vec3 v2(f2.glob);
    vec3 v3(f3.glob);
    int v1_x = v1.x * w2 + w2;
    int v2_x = v2.x * w2 + w2;
    int v3_x = v3.x * w2 + w2;
    int v1_y = v1.y * h2 + h2;
    int v2_y = v2.y * h2 + h2;
    int v3_y = v3.y * h2 + h2;
    int x_min = std::max(0, std::min(v1_x, std::min(v2_x, v3_x)));
    int y_min = std::max(0, std::min(v1_y, std::min(v2_y, v3_y)));
    int x_max = std::min(fb->get_width() - 1, std::max(v1_x, std::max(v2_x, v3_x)));
    int y_max = std::min(fb->get_height() - 1, std::max(v1_y, std::max(v2_y, v3_y)));
    int det = (v2_x - v1_x) * (v3_y - v1_y) - (v3_x - v1_x) * (v2_y - v1_y);
    if(det == 0)
        return;
    for(int y = y_min; y < y_max; y++)
        for(int x = x_min; x < x_max; x++)
        {
            int det1 = (x - v1_x) * (v3_y - v1_y) - (v3_x - v1_x) * (y - v1_y);
            int det2 = (v2_x - v1_x) * (y - v1_y) - (x - v1_x) * (v2_y - v1_y);
            float p = (float)det1 / det;
            float q = (float)det2 / det;
            if(p < 0 || q < 0 || p + q > 1)
                continue;
            float a = (1.f - p - q) / f1.glob.p;
            float b = p / f2.glob.p;
            float c = q / f3.glob.p;
            float depth = (1 - p - q) * v1.z + p * v2.z + q * v3.z;
            if(depth < -1.f || depth > 1.f)
                continue;
            (*fb)[y][x] = fragmentShader(mix(f1.v, f2.v, f3.v, a, b, c));
        }
}
/**
 * @brief Builds a rectangle
 * 
 * Actually uses triangle function to build 2 triangles.
 * @@param v1 First vertex of the rectangle
 * @param v2 Second vertex of the rectangle
 * @param v3 Third vertex of the rectangle 
 * @param v4 Fourth vertex of the rectangle
 */
/*void rectangle(vertex v1,vertex v2,vertex v3,vertex v4)
{
    triangle(v1,v2,v3);
    triangle(v2,v3,v4);
}*/