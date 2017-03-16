SpriteEditor = Panel:extend()

function SpriteEditor:new()
  SpriteEditor.super:new()
  self:SetBounds(96, 32, 128, 128 + 8)
  self.title = "Sprite Editor"
  self.sprite_index = 0
end

function SpriteEditor:DrawContent()
  local sx0 = 0
  local sy0 = 0
  -- Draw index
  local sx1 = 8
  local sy1 = 8

  local dx0 = self.x
  local dy0 = self.y + 8
  local scale = self.w / 8

  repeat
    repeat
      local pix = peek8(0x20000 + (sprite_editor_ctx.selected_sprite * 64) + (sy0 * sy1) + sx0)

      if (sprite_editor_ctx.palette ~= -1) then
        pix = peek8(0x1E200 + (pal * 256) + pix)
      end
      set_color(pix)

      local scaled_x = sx0 * scale
      local scaled_y = sy0 * scale
      if(pix ~= 0) then
        draw_rect(dx0 + scaled_x, dy0 + scaled_y,dx0 + scaled_x + scale, dy0 + scaled_y + scale)
      else
        draw_rect(dx0 + scaled_x, dy0 + scaled_y,dx0 + scaled_x + (scale / 2), dy0 + scaled_y + (scale / 2))
        draw_rect(dx0 + scaled_x + (scale / 2), dy0 + scaled_y + (scale / 2),dx0 + scaled_x + scale, dy0 + scaled_y + scale)
      end

      sx0 = sx0 + 1
    until sx0 == sx1
    sx0 = 0
    sy0 = sy0 + 1
  until sy0 == sy1
end

function SpriteEditor:UpdateContent()
  local inBounds = self:InBounds(mouse.x, mouse.y)
  if inBounds then
    if btn(9) and mouse.y - self.y > 8 then
      local scale = self.w / 8
      local my = (mouse.y - (self.y + 8))
      local sel_x = floor((mouse.x - self.x) / scale)
      local sel_y = floor(my / scale)
      spr_set(sprite_editor_ctx.selected_sprite, sel_x, sel_y, sprite_editor_ctx.selected_color)
    end
  end
end
