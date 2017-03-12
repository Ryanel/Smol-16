palette_cursor = {
  color = 0,
  cursor_color = 0
}

sprite_info = {
  index = 0,
  palette = -1,
  scale = 16
}

cursor = {
  x = 0,
  y = 0,
  color = 1,
  in_editing_area = false,
  in_palette_area = false
}

global_timer = 0

dofile("carts/sprite_editor/gfx.lua")

function _init()
  screen_clear()
  palette_reset() -- Resets Palette
  poke16(0x1E000 + (255 * 2), 0xABCDEF)
  local y = 0
  -- Write default sprites

end

function enforce_limits()
  if (palette_cursor.color < 0) then palette_cursor.color = 0 end
  if (palette_cursor.color > 255) then palette_cursor.color = 255 end
end

function update_input()
  cursor.x = _get_mouse_x()
  cursor.y = _get_mouse_y()
end

function _update()
  update_input()
  if cursor.y > 200 and cursor.y < 216 then -- Palette pane
    cursor.in_palette_area = true
    cursor.in_editing_area = false
    if btn(9) then
      local pal_x = floor((cursor.x) / 4)
      local pal_y = floor((cursor.y - 200) / 4)
      palette_cursor.color = floor(pal_y * 64 + pal_x)
    end
  end

  if cursor.x >= 96 and cursor.y >= 32 then
    cursor.in_palette_area = false
    cursor.in_editing_area = true
  else
    cursor.in_editing_area = false
  end

  global_timer = global_timer + 1
  enforce_limits()
end

function _draw()
  screen_clear()
  draw_palette_pane()
  draw_sprite_pane()
  draw_mouse()
  flip()
end
