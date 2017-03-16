EditorCart = EditorMode:extend()

function EditorCart:new(index, name)
  EditorCart.super:new(index, name)
  self.name = "Cart"

end

function EditorCart:Show()
  editor.background_color = 0
end

function EditorCart:Hide()
end

function EditorCart:Update()
end

function EditorCart:Draw()
end
