SpriteEditor = Panel:extend()

function SpriteEditor:new()
  SpriteEditor.super:new()
  self:SetBounds(112, 32, 128, 128)
  self.title = "Sprite Editor"
end

editor = SpriteEditor()
