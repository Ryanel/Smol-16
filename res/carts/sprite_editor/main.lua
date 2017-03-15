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
  local sprite_index = 0
  repeat
    local y = 0
    -- Write default sprites
    spr_set(sprite_index, 2, y, 9)
    spr_set(sprite_index, 3, y, 9)
    spr_set(sprite_index, 4, y, 9)
    spr_set(sprite_index, 5, y, 9)
    y = y + 1

    spr_set(sprite_index, 1, y, 9)
    spr_set(sprite_index, 2, y, 10)
    spr_set(sprite_index, 3, y, 10)
    spr_set(sprite_index, 4, y, 10)
    spr_set(sprite_index, 5, y, 10)
    spr_set(sprite_index, 6, y, 9)
    y = y + 1
    spr_set(sprite_index, 0, y, 9)
    spr_set(sprite_index, 1, y, 10)
    spr_set(sprite_index, 2, y, 10)
    spr_set(sprite_index, 3, y, 10)
    spr_set(sprite_index, 4, y, 10)
    spr_set(sprite_index, 5, y, 10)
    spr_set(sprite_index, 6, y, 10)
    spr_set(sprite_index, 7, y, 9)
    y = y + 1
    spr_set(sprite_index, 0, y, 9)
    spr_set(sprite_index, 1, y, 10)
    spr_set(sprite_index, 2, y, 10)
    spr_set(sprite_index, 3, y, 10)
    spr_set(sprite_index, 4, y, 10)
    spr_set(sprite_index, 5, y, 10)
    spr_set(sprite_index, 6, y, 10)
    spr_set(sprite_index, 7, y, 9)
    y = y + 1
    spr_set(sprite_index, 0, y, 9)
    spr_set(sprite_index, 1, y, 10)
    spr_set(sprite_index, 2, y, 10)
    spr_set(sprite_index, 3, y, 10)
    spr_set(sprite_index, 4, y, 10)
    spr_set(sprite_index, 5, y, 10)
    spr_set(sprite_index, 6, y, 10)
    spr_set(sprite_index, 7, y, 9)
    y = y + 1
    spr_set(sprite_index, 0, y, 9)
    spr_set(sprite_index, 1, y, 10)
    spr_set(sprite_index, 2, y, 10)
    spr_set(sprite_index, 3, y, 10)
    spr_set(sprite_index, 4, y, 10)
    spr_set(sprite_index, 5, y, 10)
    spr_set(sprite_index, 6, y, 10)
    spr_set(sprite_index, 7, y, 9)
    y = y + 1
    spr_set(sprite_index, 1, y, 9)
    spr_set(sprite_index, 2, y, 10)
    spr_set(sprite_index, 3, y, 10)
    spr_set(sprite_index, 4, y, 10)
    spr_set(sprite_index, 5, y, 10)
    spr_set(sprite_index, 6, y, 9)
    y = y + 1
    spr_set(sprite_index, 2, y, 9)
    spr_set(sprite_index, 3, y, 9)
    spr_set(sprite_index, 4, y, 9)
    spr_set(sprite_index, 5, y, 9)
    sprite_index = sprite_index + 1
  until sprite_index == 255

  poke8(0x1E200 + 10, 9)
  poke8(0x1E200 + 9, 8)
  poke8(0x1E300 + 10, 12)
  poke8(0x1E300 + 9, 13)
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
  draw_string("CPU: "..stat_cpu() .. "%", 8, 224 - 7)
  mouse:draw()
  flip()
end
