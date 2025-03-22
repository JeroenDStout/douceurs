init_directory(douceurs)

# Define the Version project
init_project(douceurs "douceurs")

# Sources static
setup_project_source(douceurs "memory"
  include:
    template_buffer_alloc.h
)
setup_project_source(douceurs "io"
  include:
    slurp.h
)
setup_project_source(douceurs "strings"
  include:
    render_string.h
    string_view_manip.h
)
setup_project_source(douceurs "reflection"
  include:
    refl_func.h
)
setup_project_source(douceurs "value"
  include:
    ref_value.h
    def_value.h
)
setup_project_source(douceurs "sugar"
  include:
    once.h
)

# Target
configure_project_header_only(douceurs)
