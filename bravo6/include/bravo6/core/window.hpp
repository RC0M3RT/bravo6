#pragma once

#include <string>

#include "bravo6/logging/logging.hpp"

// FW Decls
struct GLFWwindow;
namespace bravo6{
    class context;   
}


namespace bravo6 {

/**
 * @brief Container for window properties
 * 
 */
struct window_props{
    int widht;
    int height;
    std::string title;
    bool enable_vsync{true};
};

/**
 * @brief 
 * 
 */
class window {
public:
    /**
     * @brief Construct a new window object with default values
     * width: 800, height: 600, title: Test Window, vsync enabled
     * 
     */
    window();

    /**
     * @brief Construct a new window object
     * 
     * @param window_properties 
     */
    window(const window_props& window_properties);

    /**
     * @brief Destroy the window object
     * 
     */
    ~window();

    /**
     * @brief Initializes the GLFWwindow and set opengl properties
     * 
     * @return true On Success
     * @return false On failure
     */
    bool init();

    /**
     * @brief Returns the width of window 
     * 
     * @return int 
     */
    int width() const;

    /**
     * @brief Returns the height of window 
     * 
     * @return int 
     */
    int height() const;

    /**
     * @brief Returns the aspect of window(width/height)
     * 
     * @return float 
     */
    float aspect() const;

private:
    static void glfw_error_callback(int error, const char* description);

private:
    int width_;
    int height_;
    std::string title_;
    float aspect_;
    bool enable_vsync_{true};
    GLFWwindow* gl_window_{nullptr};

    friend class bravo6::context;
};

} // namespace bravo6