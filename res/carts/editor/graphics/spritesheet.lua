SpriteSheetEditor = Panel:extend()

function SpriteSheetEditor:new()
  SpriteSheetEditor.super:new()
  self:SetBounds(0, 32, 8 * 8, 128 + 8)
  self.title = "Spritesheet"
  self.window_color = 13
  self.window_text = 7
  self.scroll_index = 0
end

function SpriteSheetEditor:DrawContent()
  local sprites_per_line = floor(self.w / 8)
  local sprites_on_screen = floor((self.h - 8) / 8)
  local sprite_index = self.scroll_index * sprites_per_line

  local x = 0
  local y = 1
  repeat
    spr(sprite_index, self.x + (x * 8), self.y + (y * 8), 1, 1, false, false, -1)
    if sprite_index == sprite_editor_ctx.selected_sprite and (global_timer % 10) > 5 then -- Selection cursor
      set_color(0)
      gfx_rect(self.x + (x * 8), self.y + (y * 8),self.x + (x * 8) + 8, self.y + (y * 8) + 1)
      gfx_rect(self.x + (x * 8), self.y + (y * 8) + 7,self.x + (x * 8) + 8, self.y + (y * 8) + 8)
      gfx_rect(self.x + (x * 8), self.y + (y * 8),self.x + (x * 8) + 1, self.y + (y * 8) + 8)
      gfx_rect(self.x + (x * 8) + 7, self.y + (y * 8),self.x + (x * 8) + 8, self.y + (y * 8) + 8)
    end
    if x == sprites_per_line - 1 then
      x = 0
      y = y + 1
      if(y == sprites_on_screen) then sprite_index = 254 end
    else
      x = x + 1
    end

    sprite_index = sprite_index + 1
  until sprite_index == 256
  x = self.x
  y = self.y + self.h - 8
  local sprite = {
    0,0,16,16,16,16,0,0,
    0,16,8,10,10,8,16,0,
    16,8,8,10,10,8,8,16,
    16,8,8,10,10,8,8,16,
    16,8,8,10,10,8,8,16,
    16,8,8,8,8,8,8,16,
    0,16,8,10,10,8,16,0,
    0,0,16,16,16,16,0,0,
  }

  spr_array(sprite, x, y)
  set_color(16)
  draw_string("CPU Hog!", x + 10, y + 2)
end

function SpriteSheetEditor:UpdateContent()
  local inBounds = self:InBounds(mouse.x, mouse.y) and self.panel_global.being_dragged == nil
  if inBounds then
    --Spritesheet scrolling
    if btn(0) then
      self.scroll_index = self.scroll_index - 1
    end
    if btn(2) then
      self.scroll_index = self.scroll_index + 1
    end
    if self.scroll_index < 0 then self.scroll_index = 0 end
    if self.scroll_index > 30 then self.scroll_index = 30 end
    if btn(9) and mouse.y - self.y > 8 then
      local my = (mouse.y - (self.y + (8)))
      local sel_x = floor((mouse.x - self.x) / 8)
      local sel_y = floor(my / 8)
      sel_y = sel_y + self.scroll_index
      sprite_editor_ctx.selected_sprite = sel_y * 8 + sel_x
    end

  end
end
