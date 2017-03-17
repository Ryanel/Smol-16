CartSelector = Panel:extend()

function CartSelector:new()
  CartSelector.super:new()
  local width = 96
  local height = 64
  self:SetBounds(128 - (width / 2), 8, width, height)
  self.title = "Cart Selector"
  self.window_color = 6
  self.window_text = 8
end

function CartSelector:DrawContent()

end

function CartSelector:UpdateContent()

end
