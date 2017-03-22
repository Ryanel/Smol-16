SpriteSheetEditor = Panel:extend()

function SpriteSheetEditor:new()
  SpriteSheetEditor.super:new()
  self:SetBounds(0, 32, 8 * 8, 128)
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

  if (global_timer % 10) > 5 then -- Selection cursor
    x = floor(sprite_editor_ctx.selected_sprite % 8)
    y = floor(sprite_editor_ctx.selected_sprite / 8)
    local width = sprite_editor_ctx.selected_sprite_width * 8
    local height = sprite_editor_ctx.selected_sprite_height * 8
    local lx = 0
    local ly = 0
    local sx = self.x + (x * 8)
    local sy = self.y + (y * 8) + 8

    repeat
      set_pixel(sx + lx, sy + 0, 16)
      set_pixel(sx + lx, sy + height -1 , 16)
      lx = lx + 1
    until lx == width
    repeat
      set_pixel(sx, sy + ly, 16)
      set_pixel(sx + width - 1, sy + ly, 16)
      ly = ly + 1
    until ly == height
  end
end

function SpriteSheetEditor:UpdateContent()
  local inBounds = self:InBounds(mouse.x, mouse.y) and self.panel_global.being_dragged == nil
  if inBounds then
    --Spritesheet scrolling
    if io.btnp(0) then
      --self.scroll_index = self.scroll_index - 1
      sprite_editor_ctx.selected_sprite = sprite_editor_ctx.selected_sprite - 8
    end
    if io.btnp(1) then
      --self.scroll_index = self.scroll_index - 1
      sprite_editor_ctx.selected_sprite = sprite_editor_ctx.selected_sprite + 1
    end
    if io.btnp(2) then
      --self.scroll_index = self.scroll_index + 1
      sprite_editor_ctx.selected_sprite = sprite_editor_ctx.selected_sprite + 8
    end
    if io.btnp(3) then
      --self.scroll_index = self.scroll_index - 1
      sprite_editor_ctx.selected_sprite = sprite_editor_ctx.selected_sprite - 1
    end

    if self.scroll_index < 0 then self.scroll_index = 0 end
    if self.scroll_index > 30 then self.scroll_index = 30 end
    if io.btn(9) and mouse.y - self.y > 8 then
      local my = (mouse.y - (self.y + (8)))
      local sel_x = floor((mouse.x - self.x) / floor(self.w / 8))
      local sel_y = floor(my / 8) + self.scroll_index
      local sel_sprite = sel_y * floor(self.w / 8) + sel_x
      if io.btn(4) then -- Multiselect
        if(sel_sprite == sprite_editor_ctx.selected_sprite + 1) then
          sprite_editor_ctx.selected_sprite_width = 2
        end
        if(sel_sprite == sprite_editor_ctx.selected_sprite + floor(self.w / 8)) then
          sprite_editor_ctx.selected_sprite_height = 2
        end
        if(sel_sprite == sprite_editor_ctx.selected_sprite + floor(self.w / 8) + 1) then
          sprite_editor_ctx.selected_sprite_height = 2
          sprite_editor_ctx.selected_sprite_width = 2
        end
      else
        sprite_editor_ctx.selected_sprite = sel_sprite
        sprite_editor_ctx.selected_sprite_width = 1
        sprite_editor_ctx.selected_sprite_height = 1
      end
    end
  end

  if sprite_editor_ctx.selected_sprite < 0 then sprite_editor_ctx.selected_sprite = 0 end
  if sprite_editor_ctx.selected_sprite > 256 then sprite_editor_ctx.selected_sprite = 256 end
end
