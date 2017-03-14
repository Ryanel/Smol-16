SpriteSheetEditor = Panel:extend()

function SpriteSheetEditor:new()
  SpriteSheetEditor.super:new()
  self:SetBounds(16, 32, 64, 128)
  self.title = "Spritesheet"
end

spritesheet = SpriteSheetEditor()
