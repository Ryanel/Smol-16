SpriteSheetEditor = Panel:extend()

function SpriteSheetEditor:new()
  SpriteSheetEditor.super:new()
  self:SetBounds(16, 32, 64, 128)
  self.title = "Spritesheet"
  self.window_color = 13
  self.window_text = 7
  self.scroll_index = 0
end

function SpriteSheetEditor:DrawContent()
  local sprites_per_line = 8
  local sprites_on_screen = 16
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
  until sprite_index == 255
end

function SpriteSheetEditor:UpdateContent()
  local inBounds = self:InBounds(mouse.x, mouse.y)
  if inBounds then
    --Spritesheet scrolling
    if btnp(0) then
      self.scroll_index = self.scroll_index - 1
    end
    if btnp(2) then
      self.scroll_index = self.scroll_index + 1
    end
    if self.scroll_index < 0 then self.scroll_index = 0 end
    if self.scroll_index > 20 then self.scroll_index = 20 end
  end
end

spritesheet = SpriteSheetEditor()
