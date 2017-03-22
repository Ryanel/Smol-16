SpriteEditor = Panel:extend()

local zooms = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24}
local zoom_1b2 = {2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14}
local zoom_2b2 = {2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14}
function SpriteEditor:new()
  SpriteEditor.super:new()
  self.zoom_level = 6
  self:SetBounds(96, 32, 64, 128 + 8)

  self.title = "Sprite Editor"
  self.sprite_index = 0
end

function SpriteEditor:DrawContent()
  local sprite_i = sprite_editor_ctx.selected_sprite
  local sprite_w = sprite_editor_ctx.selected_sprite_width
  local sprite_h = sprite_editor_ctx.selected_sprite_height
  -- Draw Origins
  local draw_x = self.x
  local draw_y = self.y + 8
  local sx = 0
  local sy = 0
  local sw = 8 * sprite_w
  local sh = 8 * sprite_h
  local scale_x = self.w / sw
  local scale_y = (self.h - 8) / sh
  local cur_sprite = sprite_editor_ctx.selected_sprite
  repeat
    repeat
      cur_sprite = sprite_i + floor(sx / 8) + ((floor(sy / 8) * 8))
      local pix = spr_get(cur_sprite, sx % 8 , sy % 8)
      local sd_x = sx * scale_x
      local sd_y = sy * scale_y
      set_color(pix)
      gfx_rect(draw_x + sd_x, draw_y + sd_y, draw_x + sd_x + scale_x, draw_y + sd_y + scale_y)
      sx = sx + 1
    until sx == sw
    sx = 0
    sy = sy + 1
  until sy == sh
end

function SpriteEditor:UpdateContent()
  local inBounds = self:InBounds(mouse.x, mouse.y) and self.panel_global.being_dragged == nil
  if inBounds then
    if io.btn(9) and mouse.y - self.y > 8 then
      self:PutPixel()
    end
  end
  self:DoWindowScale()
end

function SpriteEditor:DoWindowScale()
  local inBounds = self:InBounds(mouse.x, mouse.y) and self.panel_global.being_dragged == nil

  if inBounds then
    if(io.btnp(5)) then
      self.zoom_level = self.zoom_level + 1
      if(zooms[self.zoom_level] == nil) then self.zoom_level = self.zoom_level - 1 end
    end
    if(io.btnp(4)) then
      self.zoom_level = self.zoom_level - 1
      if(zooms[self.zoom_level] == nil) then self.zoom_level = self.zoom_level + 1 end
    end
  end

  local zoom_amount = 4
  if(sprite_editor_ctx.selected_sprite_width == 1 and sprite_editor_ctx.selected_sprite_height == 1) then
    zoom_amount = zooms[self.zoom_level]
  end
  if((sprite_editor_ctx.selected_sprite_width == 2 or sprite_editor_ctx.selected_sprite_height == 2) and
    (sprite_editor_ctx.selected_sprite_width == 2 and sprite_editor_ctx.selected_sprite_height == 2) == false) then
    zoom_amount = zoom_1b2[self.zoom_level]
  end
  if(sprite_editor_ctx.selected_sprite_width == 2 and sprite_editor_ctx.selected_sprite_height == 2) then
    zoom_amount = zoom_2b2[self.zoom_level]
  end
  self.w = zoom_amount * 8 * sprite_editor_ctx.selected_sprite_width
  self.h = zoom_amount * 8 * sprite_editor_ctx.selected_sprite_height + 8
end

function SpriteEditor:PutPixel()
  local sprite_w = sprite_editor_ctx.selected_sprite_width
  local sprite_h = sprite_editor_ctx.selected_sprite_height
  local sw = 8 * sprite_w
  local sh = 8 * sprite_h
  local scale_x = self.w / sw
  local scale_y = (self.h - 8) / sh

  local my = (mouse.y - (self.y + 8))
  local sel_x = floor((mouse.x - self.x) / scale_x)
  local sel_y = floor(my / scale_y)

  if sel_x > sw - 1 then return end -- Keep in bounds
  if sel_y > sh - 1 then return end -- Keep in bounds

  local cur_sprite = sprite_editor_ctx.selected_sprite + floor(sel_x / 8) + ((floor(sel_y / 8) * 8))
  spr_set(cur_sprite, sel_x % 8 , sel_y % 8, sprite_editor_ctx.selected_color)
end
