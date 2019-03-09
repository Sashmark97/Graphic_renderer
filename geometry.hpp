/**
 * @file geometry.hpp
 * @brief Describes main geometry objects 
 * Contains Descriptions of Pixel(color vecor), 3D vector and their combination called Vertex
 */
#pragma once
/**
 * @brief Holds RGB color and transparency
 * 
 */
struct pixel
{
	unsigned char b; /*!< @brief Blue color */ 
    unsigned char g; /*!< @brief Green color */ 
    unsigned char r; /*!< @brief Red color */ 
    unsigned char a; /*!< @brief Alpha channel == Transparency */ 
};

struct vec4;
/**
 * @brief 3D vector
 * 
 */

struct vec3
{
    float x; /*!< @brief X coordinate of the vecor*/ 
    float y; /*!< @brief Y coordinate of the vecor*/
    float z; /*!< @brief Z coordinate of the vecor*/
    vec3() noexcept;
    vec3(vec4 const&) noexcept;
    vec3(float , float , float) noexcept;
    vec3 operator-(vec3 const &v) const noexcept;
    vec3 operator+(vec3 const &v) const noexcept;
};

struct vec4
{
    float x; /*!< @brief X coordinate of the vecor*/ 
    float y; /*!< @brief Y coordinate of the vecor*/
    float z; /*!< @brief Z coordinate of the vecor*/
    float p;
    vec4() noexcept;
    vec4(vec3 const &) noexcept;
    vec4(float, float, float, float)  noexcept;
};
/**
 * @brief 3D vector with color
 * 
 */
struct vertex
{
    vec3 pos; /*!< @brief 3D vector ||x, y, z|| */ 
    pixel c;  /*!< @brief Color of the vector */
};
/**
 * @brief 3x3 Matrix for storing float variables
 * 
 */
class mat3
{
    float m[3][3];
    public:
    mat3(float, float, float, float, float, float, float, float, float);
    mat3() = default;   
    mat3 operator*(mat3 const &) const noexcept;
    vec3 operator*(vec3 const &v) const noexcept;
    float const *operator[](int i) const noexcept;
    float *operator[](int i) noexcept;
};
class mat4
{
    float m[4][4];
    public:
    mat4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
    mat4() = default;
    mat4 operator*(mat4 const &) const noexcept;
    vec4 operator*(vec4 const &v) const noexcept;
    float const *operator[](int i) const noexcept;
    float *operator[](int i) noexcept;
};

struct fragment
{
    vec4 glob;
    vertex v;
};
    mat4 lookAt(vec3 const& pos, vec3 const& at, vec3 const& up);
    vec3 cross(vec3 const& a, vec3 const& b);
    vec3 normalize(vec3 const& a);
    mat4 perspective(float n, float f, float fov, float ratio) noexcept;
    float dot(vec3, vec3);
    