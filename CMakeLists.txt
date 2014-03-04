cmake_minimum_required(VERSION 2.8)

project(TerrainMesh)

# add source files here.  This sets the ${srcs} variable to be a list of files
set(srcs
"src/predicates.cpp"
)

# add headers here.  This sets the ${headers} variable to be a list of files
set(headers
"include/MeshDataStructure.h"
"include/predicates.h"
)

# this set of lines creates an executable, if you need to create another
add_executable(TerrainMesh ${srcs} ${headers})
#target_link_libraries(
# put any libraries we require here
#)
