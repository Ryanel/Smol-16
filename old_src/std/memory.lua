sys_mem_layout = {
  vram = 0x10000,
  pct = 0x1E000
}

function memcpy(dest, src, len)
  local i = 0
  repeat
    poke8(dest + i, peek8(src + i))
    i = i + 1
  until i == len
end
