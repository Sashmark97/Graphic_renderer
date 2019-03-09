extern "C"
{
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
}

#include <stdexcept>
#include "Framebuffer.hpp"
#include "geometry.hpp"
/**
 * @brief Construct a new Framebuffer object
 * 
 Gets information about monitor from FSCREENINFO and VSCREENINFO, puts it to Framebuffer fields. Also creates array of pixel vectors
 * @see pixel
 */
Framebuffer::Framebuffer()
{
	int fd = open("/dev/fb0", O_WRONLY);
	if(fd < 0)
		throw std::runtime_error(std::string("open:")+strerror(errno));	
	struct fb_fix_screeninfo fsinfo;
	ioctl(fd, FBIOGET_FSCREENINFO, &fsinfo);
	struct fb_var_screeninfo vsinfo;
	ioctl(fd, FBIOGET_VSCREENINFO, &vsinfo);
	width = (fsinfo.line_length * 8) / vsinfo.bits_per_pixel;
	height = fsinfo.smem_len /  fsinfo.line_length;
	xres = vsinfo.xres;
	yres = vsinfo.yres;
	w = fsinfo.line_length * 8 / vsinfo.bits_per_pixel;
    	h = fsinfo.smem_len / fsinfo.line_length;
	close(fd);
	data = new pixel[w * h];

}	
	/**
	 * @brief Get actual width of monitor
	 * 
	 * @return int Width of the monitor
	 */
	int Framebuffer::get_width() const noexcept
	{
		return width;
	}
	/**
	 * @brief Get actual height of monitor
	 * 
	 * @return int Height of monitor
	 */
	int Framebuffer::get_height() const noexcept
	{
		return height;
	}
	/**
	 * @brief Easy access to data in form of 2D array
	 * 
	 * @param i Number of line of pixels
	 * @return pixel* Array of pixel
	 */
	pixel *Framebuffer::operator[](int i) noexcept
	{
		return data + width * (yres - i - 1);
	}
	/**
	 * @brief Easy access to data in form of 2D array

	 * Used in case pixel is a constans 
	 * @param i Number of line of pixels
	 * @return pixel* Array of pixel
	 */
	pixel const *Framebuffer::operator[](int i) const noexcept
	{
		return data + width * (yres - i - 1);
	}
	/**
	 * @brief Update screen

	 * Opens fb0 for writing. Writes data to it and closes it. As the result, new data array is displayed
	 * @exception std::runtime_error {Is thrown when fails to open fb0 for writing}
	 */
	void Framebuffer::update()
	{
		int fd = open("/dev/fb0", O_WRONLY);
		if(fd == -1)
			throw std::runtime_error(std::string("open:")+strerror(errno));	
		int res = write(fd, data, width * height * sizeof(pixel));
		//write(fd, data, width * height * sizeof(pixel));
		close(fd);
	}
	/**
	 * @brief Clear it with fork
	 * @author Polkovnik
	 * 
	 Clears up your shit on the screen
	 */
	void Framebuffer::clear()
	{
		for(int i = 0 ; i < w * h; i++)
		{
			data[i] = {0,0,0,255};
		}
	}
	/**
	 * @brief Destroy the Framebuffer object

	 * Clears the data array.
	 */
	Framebuffer::~Framebuffer()
	{
    		delete[] data;
	}