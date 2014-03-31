cmake_minimum_required(VERSION 2.8)

project(TerrainMesh)

set(quad_edge_srcs
"src/edge.cpp"
"src/face.cpp"
"src/vertex.cpp"
"src/cell.cpp"
"src/predicates.cpp"
"src/quadedgewrapper.cxx"
)

set(quad_edge_headers
"include/quadedgewrapper.h"
"include/edge.h"
"include/face.h"
"include/cell.h"
"include/predicates.h"
"include/vec3.h"
"include/vertex.h"
)

add_library(quad_edge ${quad_edge_srcs} ${quad_edge_headers})

# add source files here.  This sets the ${srcs} variable to be a list of files
set(srcs
"src/predicates.cpp"
#"src/locate.cpp"
"src/triangulation.cxx"
"src/GSLocate.cpp"
)

# add headers here.  This sets the ${headers} variable to be a list of files
set(headers
#"include/MeshDataStructure.h"
"include/predicates.h"
#"include/quad_edge.h"
#"include/vector3.h"
"include/vec3.h"
"include/locate.h"
"include/triangulation.h"
"include/GSLocate.h"
)

include_directories(${CMAKE_SOURCE_DIR}/include)

# this set of lines creates an executable, if you need to create another
add_library(TerrainMesh ${srcs} ${headers})
#target_link_libraries(TerrainMesh
# quad_edge
#)

set(test_srcs
"src/array.cpp"
"src/test.cpp"
"src/obj.cpp"
"src/list.cpp"
)

set(test_headers
"include/array.h"
"include/obj.h"
"include/list.h"
)

add_executable(test ${test_srcs} ${test_headers})
target_link_libraries(test quad_edge TerrainMesh)
