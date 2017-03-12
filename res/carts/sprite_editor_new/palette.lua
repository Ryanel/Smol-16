palette = Panel()
palette.title = "Palette"
palette.set_bounds(0, 0, 256, 25)
-- Set palette properties
palette.cursor = {}
palette.cursor.index = 0
palette.cursor.color = 0

palette.draw_content = function ()
  local pal_color = 0
  repeat
    set_color(pal_color)

    local x_offset = floor((pal_color * 4) % 256)
    local y_offset = floor(pal_color / 64)
    local x = x_offset
    local y = (y_offset * 4) + this.y
    if(not this.hide_pane) then y = y + 8 end

    draw_rect(x, y, x + 4, y + 4)
    if (pal_color == this.cursor.index and (global_timer % 30) > 10) then
      if(pal_color == this.cursor.color) then
        set_color(7)
      else
        set_color(this.cursor.color)
      end

      draw_rect(x, y, x + 4, y + 4)
      set_color(pal_color)
      draw_rect(x + 1, y + 1, x + 3, y + 3)
    end

    pal_color = pal_color + 1
  until pal_color == 256
end

palette.update = function()
  palette.in_bounds()
  if(palette.is_in) then
    if btn(9) then
      local pal_y = palette.y
      if(not palette.hide_pane) then pal_y = pal_y + 8 end

      local pal_x = floor((mouse.x) / 4)
      local pal_y = floor((mouse.y - pal_y) / 4)
      palette.cursor.index = floor(pal_y * 64 + pal_x)
    end
  end
  if btn(0) then
    palette.y = palette.y - 1
  end
  if btn(2) then
    palette.y = palette.y + 1
  end
end
