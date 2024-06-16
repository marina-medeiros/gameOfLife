/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"
#include "lodepng.h"

namespace life {
    
/**
 * @brief Encodes an image to a PNG file and saves it to a specified filename.
 *
 * This function uses the lodepng library to encode an image represented by an array of pixels 
 * and saves it as a PNG file. If there is an encoding error, it displays an error message.
 *
 * @param filename The name of the file where the PNG image will be saved.
 * @param image A pointer to the array of pixels representing the image.
 * @param width The width of the image in pixels.
 * @param height The height of the image in pixels.
 */
void encode_png(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  // Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  // if there's an error, display it
  if (error != 0U) {
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  }
}

/*!
 * Deep copy of the canvas.
 * @param clone The object we are copying from.
 */
Canvas::Canvas(const Canvas& clone) {
    m_width = clone.m_width;
    m_height = clone.m_height;
    m_pixels = clone.m_pixels;
}

/*!
 * @param source The object we are copying information from.
 * @return A reference to the `this` object.
 */
Canvas& Canvas::operator=(const Canvas& source) { return *this; }

/**
 * @brief Clears the canvas by setting all pixels to a specified color.
 *
 * This function iterates over all the pixels in the canvas and sets each one to the given color.
 *
 * @param color The color to set all the pixels in the canvas to.
 */
void Canvas::clear(const Color& color) {
    for (size_t i{ 0 }; i < width(); ++i)
        for (size_t j{ 0 }; j < height(); ++j)
            pixel(i, j, color);
}

/**
 * @brief Retrieves the color of a pixel at the specified coordinates.
 *
 * @throw std::invalid_argument If the pixel coordinate is located outside the canvas.
 * @param x The X coordinate of the pixel we want to know the color of.
 * @param y The Y coordinate of the pixel we want to know the color of.
 * @return The color of the specified pixel.
 */
Color Canvas::pixel(coord_t x, coord_t y) const {
    if (not in_bounds(x, y))
        throw std::invalid_argument("Invalid pixel coordinate.");
    auto channels = pixel_channels(x, y);
    return Color{ channels[Color::R], channels[Color::G], channels[Color::B] };
}

/**
 * @brief Draws a pixel on the real image at the specified coordinates.
 *
 * @note Nothing is done if the pixel coordinate is located outside the canvas.
 * @param x The X coordinate of the pixel to be drawn.
 * @param y The Y coordinate of the pixel to be drawn.
 * @param c The color of the pixel.
 */
void Canvas::pixel(coord_t x, coord_t y, const Color& c) {
    if (not in_bounds(x, y))
        return;
    auto [virtual_x, virtual_y] = real_to_virtual(x, y);
    for (int i = 0; i < m_block_size; i++)
        for (int j = 0; j < m_block_size; j++) {
            auto current_x = virtual_x + j;
            auto current_y = virtual_y + i;
            if (not in_virtual_bounds(current_x, current_y))
                continue;
            m_pixels[(current_y * m_width + current_x) * Canvas::image_depth + Color::R]
              = c.channels[Color::R];
            m_pixels[(current_y * m_width + current_x) * Canvas::image_depth + Color::G]
              = c.channels[Color::G];
            m_pixels[(current_y * m_width + current_x) * Canvas::image_depth + Color::B]
              = c.channels[Color::B];
            m_pixels[(current_y * m_width + current_x) * Canvas::image_depth + 3]
              = 255;  //!< Setting alpha to full opacity
        }
}
/**
 * @brief Converts a matrix to a PNG image and saves it to a specified file path.
 *
 * This function clears the canvas, iterates over the matrix, and draws pixels on the canvas 
 * according to the matrix values. It then encodes the canvas to a PNG image file.
 *
 * @param matrix The matrix representing the current state of the canvas.
 * @param aliveColor The color used to represent alive cells.
 * @param bkgColor The background color used to represent dead or empty cells.
 * @param imagePath The path where the PNG image will be saved.
 * @param configPrefix The prefix used in the filename of the PNG image.
 * @param genCount The generation count, used in the filename of the PNG image.
 */
void Canvas::matrix_to_png(std::vector<std::vector<int>>& matrix, std::string aliveColor, std::string bkgColor, std::string imagePath, std::string configPrefix, int genCount){
    clear();
    for (int y = 0; y < (int)height(); ++y) {
        for (int x = 0; x < (int)width(); ++x) {
            if (matrix[y+1][x+1] == 0 || matrix[y+1][x+1] == 2) {
                pixel(x, y, color_pallet[bkgColor]);
            } else if (matrix[y+1][x+1] == 1) {
                pixel(x, y, color_pallet[aliveColor]);
            }
        }
    }
    // data.path + / + 
    std::string filename = imagePath + "/" + configPrefix + std::to_string(genCount) + ".png";
    const char *cstr = filename.c_str();
    encode_png(cstr, pixels(), virtual_width(), virtual_height());
}

}  // namespace life
//================================[ canvas.cpp ]================================//
