function file_load_spritesheet(filepath)
  local file = io.open (filepath , "rb")
  if file == nil then return end
  local i = 0
  repeat
    local dat = file:read(1)
    poke8(0x20000 + i,string.byte(dat))
    i = i + 1
  until i == 64 * 256
  file:close()
end
