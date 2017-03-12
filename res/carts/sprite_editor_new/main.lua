global_timer = 0

dofile("carts/sprite_editor_new/oo.lua")
dofile("carts/sprite_editor_new/panel.lua")
dofile("carts/sprite_editor_new/palette.lua")
dofile("carts/sprite_editor_new/mouse.lua")

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
  mouse.update()
  palette.update()

  global_timer = global_timer + 1
end

function _draw()
  screen_clear()
  palette.draw()
  mouse.draw()
  flip()
end
