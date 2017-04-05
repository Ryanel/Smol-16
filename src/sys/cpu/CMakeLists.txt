set(smol_src_sys_cpu
    cpu.cxx
    interpreter.cxx
    opcodes/sys.cxx
    opcodes/math.cxx
    opcodes/load.cxx
    opcodes/jump.cxx
)

add_library(cpu ${smol_src_sys_cpu})
