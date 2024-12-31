init_directory(douceurs_repo_version)

# Define the Version project
init_project(douceurs_repo_version "meta")

# Sources static
setup_project_source(douceurs_repo_version "version"
  include:
    git_version.h GENERATED
)
setup_project_source(douceurs_repo_version "script"
  script:
    ../../touch
    generate_git_version.py
    git_version.txt GENERATED
)

# Target
configure_project_header_only(douceurs_repo_version)

# Custom
add_custom_command(
  COMMENT			"Generate git version file"
  OUTPUT    		${abs_gen_include}/git_version.h
                    ${abs_gen_script}/git_version.txt
  COMMAND   		${Python3_EXECUTABLE}
					${abs_can_script}/generate_git_version.py
					${abs_gen_include}/git_version.h
					${abs_gen_script}/git_version.txt
                    "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
  DEPENDS			${cmake_root_dir}/touch
                    ${abs_can_script}/generate_git_version.py
  WORKING_DIRECTORY ${cmake_root_dir}
  VERBATIM
)
configure_publish_file("${abs_gen_script}/git_version.txt" "version.txt")
