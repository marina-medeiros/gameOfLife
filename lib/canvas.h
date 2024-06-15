#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
using std::vector;
#include <cstdint>

#include "common.h"

namespace life {

//! Provides methods for drawing on an image.
/*!
 * This is a drawing area on which we shall draw a Life representation.
 *
 * Here some information on the canvas properties:
 *
 * 1. The drawing area has the origin set to the top left corner, with
 * positive `X` axis going to the right and positive `Y` axis going to
 * the bottom of the canvas.
 * 2. A pixel on the canvas has a square shape based on the pixel size
 * set when the canvas is instantiated.
 * 3. Because of 2, we have the `virtual` dimension (set by the client),
 * and the `real` dimension, which is w * pixel_size by h * pixel_size.
 *
 * This class returns to the client an image (object) representation
 * of the canvas, which might be stored by the client as a PPM or
 * PNG image file.
 */
class Canvas {
  public:
    //== Alias
    using component_t = uint8_t;    //!< Type of a color channel.
    using coord_t = unsigned long;  //!< The pixel coordinate type.
    //== Constants
    static constexpr uint8_t image_depth = 4;  //!< Default value is RGBA (4 channels).

    //=== Special members
    /// Constructor
    /*! Creates an empty canvas with the requested dimensions.
     * @param w The canvas width in virtual pixels.
     * @param h The canvas height in virtual pixels.
     * @param bs The canvas block size in real pixels.
     */
    Canvas(size_t w = 0, size_t h = 0, short bs = 4)
        : m_width(w * bs), m_height(h * bs), m_block_size(bs) {
        m_pixels.resize(m_height * m_width * image_depth);
    }
    /// Destructor.
    virtual ~Canvas() = default;

    //=== Special members
    /// Copy constructor.
    Canvas(const Canvas&);
    /// Assignment operator.
    Canvas& operator=(const Canvas&);

    //=== Members
    /// Clear the canvas with black color.
    void clear(const Color& = BLACK);
    /// Set the color of a pixel on the canvas.
    void pixel(coord_t, coord_t, const Color&);
    /// Get the pixel color from the canvas.
    [[nodiscard]] Color pixel(coord_t, coord_t) const;

    //=== Attribute accessors members.
    /// Get the canvas width in virtual pixels.
    [[nodiscard]] size_t width() const { return m_width / m_block_size; }
    /// Get the canvas height in virtual pixels.
    [[nodiscard]] size_t height() const { return m_height / m_block_size; }
    /// Get the canvas width in pixels
    [[nodiscard]] size_t real_width() const { return m_width; }
    /// Get the canvas width in pixels
    [[nodiscard]] size_t real_height() const { return m_height; }
    /// Get the canvas pixels, as an array of `unsigned char`.
    [[nodiscard]] const component_t* pixels() const { return m_pixels.data(); }
    /// Given a (virtual) coordinate, it tells if it's in bounds of m_pixels
    [[nodiscard]] bool in_bounds(coord_t x, coord_t y) const {
        return x < width() and y < height();
    }
    [[nodiscard]] constexpr bool in_real_bounds(coord_t r_x, coord_t r_y) const {
        return r_x < m_width and r_y < m_height;
    }
    /// Virtual to real coordinate
    [[nodiscard]] constexpr std::pair<size_t, size_t> virtual_to_real(coord_t x, coord_t y) const {
        return { x * m_block_size, y * m_block_size };
    }
    /// Given a coordinate it returns every channel of the pixel
    std::array<component_t, image_depth> pixel_channels(coord_t x, coord_t y) const {
        auto [real_x, real_y] = virtual_to_real(x, y);
        return { m_pixels[(real_y * m_width + real_x) * image_depth],
                 m_pixels[(real_y * m_width + real_x) * image_depth + 1],
                 m_pixels[(real_y * m_width + real_x) * image_depth + 2],
                 m_pixels[(real_y * m_width + real_x) * image_depth + 3] };
    }

    void matrix_to_png(std::vector<std::vector<int>>& matrix, std::string aliveColor, std::string bkgColor, std::string imagePath, std::string configPrefix);

  private:
    size_t m_width;                //!< The image width in pixel units.
    size_t m_height;               //!< The image height in pixel units.
    short m_block_size;            //!< Cell size in pixels
    vector<component_t> m_pixels;  //!< The pixels, stored as 3 RGB components.
};
}  // namespace life

#endif  // CANVAS_H
