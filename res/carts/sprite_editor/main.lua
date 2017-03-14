global_timer = 0

cart_header = {
  name = "Sprite Editor"
}

require("object.lua")
require("panel.lua")
require("palette.lua")
require("sprite_editor.lua")
require("spritesheet.lua")
require("mouse.lua")

palette_cursor = {
  color = 0,
  cursor_color = 0
}

sprite_info = {
  index = 0,
  palette = -1,
  scale = 16
}

function _init()
  palette_reset()
end

function _update()
  mouse:update()
  palette:Update()
  spritesheet:Update()
  editor:Update()
  global_timer = global_timer + 1
end

function _draw()
  --cls()
  cls(1)
  -- Draw panels
  palette:Draw()
  spritesheet:Draw()
  editor:Draw()

  --Draw cpu
  set_color(7)
  draw_string("CPU: "..stat_cpu() .. "%", 8, 224 - 8)
  mouse:draw()
  flip()
end
