project(sasm)

set(sasm_src
    main.cxx
    config.cxx
    args.cxx
    file.cxx
    preprocess.cxx
    assembler.cxx
    lexicon.cxx
)

add_executable(sasm ${sasm_src})
target_link_libraries(sasm pthread)
