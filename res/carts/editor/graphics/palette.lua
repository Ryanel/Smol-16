Palette = Panel:extend()

function Palette:new()
  Palette.super:new()
  self:SetBounds(0,224 - (24),256,24)
  self.title = "Palette"
  self.window_color = 5
  self.window_text = 10
  self.cursor = {}
  self.cursor.index = 0
  self.cursor.color = 7
  self.nodrag_x = true
  self.minimisable = false
end

function Palette:DrawContent()
  local pal_color = 0
  repeat
    set_color(pal_color)

    local x_offset = floor((pal_color * 4) % 256)
    local y_offset = floor(pal_color / 64)
    local x = x_offset
    local y = (y_offset * 4) + self.y
    if(not self.no_chrome) then y = y + 8 end

    gfx_rect(x, y, x + 4, y + 4)
    if (pal_color == self.cursor.index and (global_timer % 30) > 10) then
      if(pal_color == self.cursor.color) then
        set_color(0)
      else
        set_color(self.cursor.color)
      end

      gfx_rect(x, y, x + 4, y + 4)
      set_color(pal_color)
      gfx_rect(x + 1, y + 1, x + 3, y + 3)
    end

    pal_color = pal_color + 1
  until pal_color == 256
end

function Palette:UpdateContent()
  local inBounds = self:InBounds(mouse.x, mouse.y)
  if inBounds then
    if btn(9) then
      local pal_y = self.y
      if(not self.no_chrome) then pal_y = pal_y + 8 end
      local pal_x = floor((mouse.x) / 4)
      local pal_y = floor((mouse.y - pal_y) / 4)
      local fin = floor(pal_y * 64 + pal_x)
      if fin < 0 then fin = 0 end
      self.cursor.index = fin
      sprite_editor_ctx.selected_color = fin
    end
  end
  self.title = "Palette (Color "..self.cursor.index..")"
end
