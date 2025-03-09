init_directory(douceurs)

# Define the Version project
init_project(douceurs "douceurs")

# Sources static
setup_project_source(douceurs "strings"
  include:
    render_string.h
)
setup_project_source(douceurs "reflection"
  include:
    refl_func.h
)

# Target
configure_project_header_only(douceurs)
