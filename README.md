# SFML Calendar

A simple, interactive calendar application built with C++ and SFML (Simple and Fast Multimedia Library). Features a clean interface with theme switching and month navigation capabilities.

## Features

- **Interactive Month Navigation**: Use left/right arrow keys to browse through months and years
- **Theme Switching**: Toggle between light and dark themes with the 'T' key
- **Today Highlighting**: Current date is highlighted with a colored circle
- **Clean Interface**: Minimalist design with proper weekday labels and date layout
- **Responsive Design**: Smooth 60 FPS rendering with proper event handling

## Screenshots

The calendar supports two themes:
- **Light Theme**: Light background with dark text and blue highlights
- **Dark Theme**: Dark background with light text and orange highlights

## Prerequisites

Before building this project, ensure you have:

- C++11 or later compiler (GCC, Clang, or MSVC)
- SFML 2.5+ development libraries
- OpenSans.ttf font file (place in project directory)

### Installing SFML

**Ubuntu/Debian:**
```bash
sudo apt-get install libsfml-dev
```

**macOS (with Homebrew):**
```bash
brew install sfml
```

**Windows:**
Download SFML from [sfml-dev.org](https://www.sfml-dev.org/download.php) and follow the setup guide for your IDE.

## Building

### Using g++
```bash
g++ -o calendar kalendar.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

### Using CMake (create CMakeLists.txt)
```cmake
cmake_minimum_required(VERSION 3.10)
project(Calendar)

set(CMAKE_CXX_STANDARD 11)

find_package(sfml REQUIRED graphics window system)

add_executable(calendar kalendar.cpp)
target_link_libraries(calendar sfml-graphics sfml-window sfml-system)
```

Then build:
```bash
mkdir build && cd build
cmake ..
make
```

## Font Setup

Download the OpenSans font:
1. Visit [Google Fonts - Open Sans](https://fonts.google.com/specimen/Open+Sans)
2. Download the font family
3. Extract `OpenSans-Regular.ttf` and rename it to `OpenSans.ttf`
4. Place it in the same directory as your executable

## Usage

### Controls

| Key | Action |
|-----|--------|
| `←` (Left Arrow) | Navigate to previous month |
| `→` (Right Arrow) | Navigate to next month |
| `T` | Toggle between light and dark themes |
| `ESC` or Close Button | Exit application |

### Running the Application

After building, simply run:
```bash
./calendar
```

The calendar will open displaying the current month with today's date highlighted.

## Code Structure

- **Theme System**: Configurable color schemes stored in a `Theme` struct
- **Date Calculation**: Uses C++ `<chrono>` and `<ctime>` for accurate date handling
- **Leap Year Support**: Properly calculates days in February for leap years
- **Grid Layout**: 7×7 grid system for proper calendar display

## Technical Details

- **Window Size**: 800×600 pixels
- **Frame Rate**: Limited to 60 FPS for smooth performance
- **Cell Dimensions**: 100×70 pixels per calendar cell
- **Font Sizes**: 30px for header, 24px for dates, 20px for weekday labels

## Customization

### Adding New Themes
Add new color schemes to the `themes` vector in `main()`:
```cpp
themes.push_back({
    sf::Color(R, G, B),     // background
    sf::Color(R, G, B),     // text
    sf::Color(R, G, B)      // highlight
});
```

### Changing Window Size
Modify the `sf::VideoMode` parameters:
```cpp
sf::RenderWindow window(sf::VideoMode(width, height), "SFML Calendar");
```

### Custom Fonts
Replace `OpenSans.ttf` with your preferred font file and update the load path:
```cpp
font.loadFromFile("YourFont.ttf")
```

## Troubleshooting

**Font loading error**: Ensure `OpenSans.ttf` is in the same directory as the executable or provide the full path.

**SFML linking errors**: Make sure SFML is properly installed and linked. On some systems, you may need to specify additional flags like `-lGL`.

**Display issues**: Verify your system supports OpenGL and has proper graphics drivers installed.

- SFML team for the excellent multimedia library
- Google Fonts for providing the Open Sans font family
