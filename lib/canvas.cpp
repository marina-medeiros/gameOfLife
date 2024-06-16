/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"
#include "lodepng.h"

namespace life {

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

/// Assigns a black color to the whole image.
void Canvas::clear(const Color& color) {
    for (size_t i{ 0 }; i < width(); ++i)
        for (size_t j{ 0 }; j < height(); ++j)
            pixel(i, j, color);
}

/*!
 * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
 * @param x The (real) X coordinate of the pixel we want to know the color of.
 * @param x The (real) Y coordinate of the pixel we want to know the color of.
 * @return The pixel color.
 */
Color Canvas::pixel(coord_t x, coord_t y) const {
    if (not in_bounds(x, y))
        throw std::invalid_argument("Invalid pixel coordinate.");
    auto channels = pixel_channels(x, y);
    return Color{ channels[Color::R], channels[Color::G], channels[Color::B] };
}

/*!
 * Draw a pixel on the real image at the requested coordinate.
 *
 * @note Nothing is done if the pixel coordinate is located outside the canvas.
 * @param x The (real) X coordinate of the pixel we want to know the color of.
 * @param x The (real) Y coordinate of the pixel we want to know the color of.
 * @param c The color.
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
