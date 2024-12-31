#
# Initial set-up
#

cmake_minimum_required(VERSION 3.15)

# Packages
# include(cmake/generic/vcpkg.cmake)

# Project
project(template)
include(cmake/generic/project.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Languages
include(cmake/generic/cxx.cmake)
include(cmake/generic/python.cmake)

# Support
include(cmake/generic/outputs.cmake)
include(cmake/generic/artefacts.cmake)
include(cmake/generic/sources.cmake)
include(cmake/generic/assets.cmake)
include(cmake/generic/publish.cmake)

# Processing
# ...

# Subprojects
add_subdirectory(src/repo_version)

# Publication
finalise_publish()
