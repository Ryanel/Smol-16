function draw_pane(title, x, y, w, h)
  set_color(9)
  draw_rect(x,y, x + w, y + 8)
  set_color(7)
  draw_string(title, x + 8 ,y + 1)
end

function draw_palette_pane()
  draw_pane("Palette (" .. palette_cursor.color .. ")", 0, 192, 256, 64)
  local pal_color = 0
  repeat
    set_color(pal_color)

    local x_offset = floor((pal_color * 4) % 256)
    local y_offset = floor(pal_color / 64)
    local x = x_offset
    local y = (y_offset * 4) + 200

    draw_rect(x, y, x + 4, y + 4)
    if (pal_color == palette_cursor.color and (global_timer % 30) > 10) then
      if(pal_color == palette_cursor.cursor_color) then
        set_color(7)
      else
        set_color(palette_cursor.cursor_color)
      end

      draw_rect(x, y, x + 4, y + 4)
      set_color(pal_color)
      draw_rect(x + 1, y + 1, x + 3, y + 3)
    end

    pal_color = pal_color + 1
  until pal_color == 256
end

function draw_sprite_pane()
  local sx0 = 0
  local sy0 = 0
  -- Draw index
  local sx1 = 8
  local sy1 = 8

  local dx0 = 96
  local dy0 = 32
  local scale = sprite_info.scale

  repeat
    repeat
      local pix = peek8(0x20000 + (sprite_info.index * 64) + (sy0 * sy1) + sx0)

      if (sprite_info.palette ~= -1) then
        pix = peek8(0x1E200 + (pal * 256) + pix)
      end
      set_color(pix)

      local scaled_x = sx0 * scale
      local scaled_y = sy0 * scale

      draw_rect(dx0 + scaled_x, dy0 + scaled_y,dx0 + scaled_x + scale, dy0 + scaled_y + scale)
      sx0 = sx0 + 1
    until sx0 == sx1
    sx0 = 0
    sy0 = sy0 + 1
  until sy0 == sy1
end

function draw_mouse()
  if(global_timer % 15 == 0) then
    cursor.color = ((cursor.color + 1) % 16)
    cursor.color = math.max(cursor.color, 3)
  end

  set_color(cursor.color)
  draw_rect(cursor.x,cursor.y, cursor.x + 2, cursor.y + 2)
  set_color(cursor.color - 1)
  draw_rect(cursor.x + 1,cursor.y + 1, cursor.x + 3, cursor.y + 3)
  set_color(cursor.color - 2)
  draw_rect(cursor.x + 2,cursor.y + 2, cursor.x + 4, cursor.y + 4)
end
