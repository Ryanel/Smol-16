sys_mem_layout = {
  vram = 0x0,
  pct = 0xE000
}

function memcpy(dest, src, len)
  local i = 0
  repeat
    mem.poke8(dest + i, mem.peek8(src + i))
    i = i + 1
  until i == len
end
