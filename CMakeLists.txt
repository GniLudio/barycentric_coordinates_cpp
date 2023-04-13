# The minimum CMAKE version required
cmake_minimum_required (VERSION 3.10.0)

# Define the project
project ("Computergraphik" C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 11)

# Automically include generated files
set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_subdirectory(lib/imgui-1.89.4/)
add_subdirectory(lib/glad/)

# Define header files
set (HEADERS
	# Math
	"src/math/Vec4f.h"
	"src/math/Mat4f.h"
	# Primtives
	"src/primitives/Vertex.h"
	"src/primitives/TexCoord.h"
	"src/primitives/Barycentric.h"
	"src/primitives/Triangle.h"
	# Rendering
	"src/rendering/Shader.h"
	"src/rendering/Mesh.h"
	"src/rendering/LineDrawer.h"
	"src/rendering/CircleDrawer.h"
	# Window
	"src/window/Window.h"
	# Utilities
	"src/utilities/Colors.h"
	# Barycentric Coordinates
	"src/barycentric_coordinates/BarycentricCoordinates.h"
)

# Define source files
set (SOURCES
	"src/main.cpp"
	# Math
	"src/math/Vec4f.cpp"
	"src/math/Mat4f.cpp"
	# Rendering
	"src/rendering/Shader.cpp"
	"src/rendering/Mesh.cpp"
	"src/rendering/LineDrawer.cpp"
	"src/rendering/CircleDrawer.cpp"
	# Window
	"src/window/Window.cpp" 
)

# Define shader & other resources
set (RESOURCES
	"shader/line.vert"
	"shader/line.frag"
	"shader/circle.vert"
	"shader/circle.frag"
)

# Allow to include files directly from this paths
include_directories(
	"src"
	"lib/tiny_obj_loader"
)

# Define the executable
add_executable(Computergraphik ${SOURCES} ${HEADERS} ${RESOURCES})

# IMGUI specific compile definition:
target_compile_definitions(Computergraphik PUBLIC -DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Define the libraries to link against:
target_link_libraries(Computergraphik PUBLIC imgui glad)