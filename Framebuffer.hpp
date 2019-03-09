/**
 * @file Framebuffer.hpp
 * @author 8ScarleT8
 * @brief Describes Framebuffer class
 * @version 0.1
 * @date 2018-11-02
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#pragma once
#include "geometry.hpp"
/**
 * @brief Class for interaction with the screen through fb0.
 
 * Determines actual and virtual size of the monitor, prepares pixel array
   that will be written to fb0 in order to be displayed on the screen.
 */
class Framebuffer
{
	pixel *data; /*!< @brief Reference to the beginning of pixel, that will be written on the screen */
	int width; /*!< @brief Reference to the beginning of pixel, that will be written on the screen */
    int height;
    int xres;
    int yres;
    int w;
    int h;
public:
    Framebuffer();
    ~Framebuffer();
    Framebuffer(Framebuffer const &) = delete;
    Framebuffer(Framebuffer &&) = delete;

    int get_width() const noexcept;
    int get_height() const noexcept;
    pixel *operator[](int i) noexcept;
    pixel const *operator[](int i) const noexcept;
    void update();
    void clear();
};