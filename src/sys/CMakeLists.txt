set(smol_src_sys
    sys.cxx
)

add_subdirectory(cpu)
add_subdirectory(mem)

add_library(sys ${smol_src_sys})
target_link_libraries(sys cpu mem)
