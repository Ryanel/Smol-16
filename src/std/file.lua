function file_load_spritesheet(filepath)
  local file = io.open (filepath , "rb")
  if file == nil then return end
  local i = 0
  repeat
    local dat = file:read(1)
    if dat == nil then break end
    ppu.poke8(i + 0x10000, string.byte(dat))
    i = i + 1
  until i == 64 * 256
  file:close()
end

function sys_load_palette(file_path)
  local file = io.open (filepath , "rb")
  if file == nil then return end
  local i = 0
  repeat
    local dat = file:read(2)
    ppu.poke16(0xE000 + i * 2,string.byte(dat))
    i = i + 1
  until i == 256
  file:close()
end
