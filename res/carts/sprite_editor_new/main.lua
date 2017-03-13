global_timer = 0

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
  -- Clear screen
  set_color(1)
  draw_rect(0,0,256, 224)

  -- Draw panels
  palette:Draw()
  spritesheet:Draw()
  editor:Draw()

  mouse:draw()
  flip()
end