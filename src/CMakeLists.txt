set(smol_src
    main.cxx
    args.cxx
    config.cxx
)

add_subdirectory(sys)

add_executable(Smol16 ${smol_src})

set(lib_names
    sys
)

target_link_libraries(Smol16 ${lib_names} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDLMIXER_LIBRARY})
