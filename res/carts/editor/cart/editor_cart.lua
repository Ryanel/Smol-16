EditorCart = EditorMode:extend()

require("cart/cart_selector.lua")

cart_info = {
  loaded_cart = "adventure",
  cart_path = "./carts/"
}

function EditorCart:new(index, name)
  EditorCart.super:new(index, name)
  self.name = "Cart"
  self.selector = CartSelector()
end

function EditorCart:Show()
  editor.background_color = 5

  self.selector:Show()
end

function EditorCart:Hide()
  self.selector:Hide()
end

function EditorCart:Update()
  self.selector:Update()
end

function EditorCart:Draw()
  self.selector:Draw()
end
