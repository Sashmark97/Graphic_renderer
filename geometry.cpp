/**
 * @file geometry.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-04
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "geometry.hpp"
#include <cmath>

/**
 * @brief Perform 3x3 matrix multiplication
 * 
 * @param m Second matrix
 * @return mat3 Resulting 3x3 matrix
 */
mat3 mat3::operator*(mat3 const &mat) const noexcept
{
    mat3 out;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            out[i][j] = 0.f;
            for(int k = 0; k < 3; k++)
                out[i][j] += m[i][k] * mat[k][j];
        }
    return out;
}
/**
 * @brief Multiplication of 3x3 matrix and vec3
 * 
 * @param v 
 * @return vec3 
 */
vec3 mat3::operator*(vec3 const &v) const noexcept
{
    vec3 res = {m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z};
    return res;
}
/**
 * @brief Cross multiplication of two 3D vectors [a,b] = c
 * 
   More detailed description
 * @param a First vector
 * @param b Second vector
 * @return vec3 Resulting vector
 */
vec3 cross(vec3 const& a, vec3 const& b)
{
	vec3 res = {a.y * b.z - a.z * b.y,
		        a.z * b.x - a.x * b.z,
		        a.x * b.y - a.y * b.x};
	return res;
}

float *mat3::operator[](int i) noexcept
{
    return m[i];
}

float const *mat3::operator[](int i) const noexcept
{
    return m[i];
}

mat3::mat3(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22):
    m{a00, a01, a02, a10, a11, a12, a20, a21, a22}
{}

mat4 mat4::operator*(mat4 const &mat) const noexcept
{
    mat4 out;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            out[i][j] = 0.f;
            for(int k = 0; k < 4; k++)
                out[i][j] += m[i][k] * mat[k][j];
        }
    return out;
}

vec4 mat4::operator*(vec4 const &v) const noexcept
{
    vec4 res = {m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.p,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.p,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.p,
                m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.p};
    return res;
}

float *mat4::operator[](int i) noexcept
{
    return m[i];
}

float const *mat4::operator[](int i) const noexcept
{
    return m[i];
}

mat4::mat4(float a00, float a01, float a02, float a03, float a10, float a11, float a12, float a13, float a20, float a21, float a22, float a23, float a30, float a31, float a32, float a33):
    m{a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23, a30, a31, a32, a33}
{}
/**
 * @brief Creates matrix of translation to camera's coordinate system
 * 
 * @param dir Direction of camera()
 * @param up Position of the sky
 * @return mat3 3x3 Matrix of translation
 */
mat4 lookAt(vec3 const& pos, vec3 const& at, vec3 const& up)
{
    vec3 e1, e2, e3;
    e3 = normalize(pos - at);
    e1 = normalize(cross(normalize(up), e3));
    e2 = normalize(cross(e3, e1));
    return mat4(e1.x, e1.y, e1.z, -dot(e1, pos), 
                e2.x, e2.y, e2.z, -dot(e2, pos),
                e3.x, e3.y, e3.z, -dot(e3, pos),
                0.0f, 0.0f, 0.0f, 1.0f);

}
/**
 * @brief Returns normalized vector
 * 
 * @param a Initial vector
 * @return vec3 Normalized vector
 */
vec3 normalize(vec3 const& a)
{
	float norm = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	vec3 res = {a.x / norm , a.y / norm, a.z / norm};
	return res;
}
 
vec3::vec3() noexcept
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}    

vec3::vec3(float a, float b, float c) noexcept
{
    x = a;
    y = b;
    z = c;
}    

vec3::vec3(vec4 const &v) noexcept
{
    x = v.x / v.p; 
    y = v.y / v.p;
    z = v.z / v.p;
}

vec3 vec3::operator+(vec3 const &v) const noexcept
{
    return vec3(x + v.x, y + v.y, z + v.z);
}
vec3 vec3::operator-(vec3 const &v) const noexcept
{   
    return vec3(x - v.x, y - v.y, z - v.z);
}

vec4::vec4() noexcept
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    p = 1.0f;
}

vec4::vec4(float a, float b, float c, float d) noexcept
{
    x = a;
    y = b;
    z = c;
    p = d;
} 

vec4::vec4(vec3 const &v) noexcept
{
    x = v.x;
    y = v.y; 
    z = v.z; 
    p = 1.f;
}

mat4 perspective(float n, float f, float fov, float ratio) noexcept
{
    float c1 = (f + n) / (f - n);    // HYPERBOLIC APPROX: dzeta = c1 + c2/z
    float c2 = (2.f * f * n) / (f - n)  ;
    //float c1 = 2 / (n - f);        // LINEAR APPROX: dzeta = c1 * z + c2
    //float c2 = (f + n) / (n - f);
    return mat4(-1.f/std::tan(fov), 0.0f, 0.0f, 0.0f,
                0.0f, -ratio/std::tan(fov), 0.0f, 0.0f,
                0.0f, 0.0f,  c1 ,  c2 ,
                0.0f, 0.0f, 1.0f, 0.0f);
}

float dot(vec3 a, vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
