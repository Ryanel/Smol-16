GraphicsExporter = Panel:extend()

function GraphicsExporter:new()
  GraphicsExporter.super:new()
  local width = 50
  local height = 16
  self:SetBounds(256 - width, 8, width, height)
  self.title = "Exporter"
  self.window_color = 5
  self.window_text = 9
  self.minimised = true
  self.export_mode = 0
end

function GraphicsExporter:DrawContent()
  self:DrawButton(0,0, 16,9, "Lua")
  self:DrawButton(16,0, 19,9, "Cart")
  self:DrawButton(16 + 19,0, 15,9, "PNG")
end

function GraphicsExporter:UpdateContent()
  if io.btnp(9) and self:InBounds(mouse.x, mouse.y) then
    local lx = mouse.x - self.x
    if lx <= 16 then -- LUA
      print("==========BEGIN EXPORT==========")
      print("local sprite = {")
      local x = 0
      local y = 0
      local vals = {0,0,0,0,0,0,0,0,0}
      repeat
        repeat
          local c = spr_get(sprite_editor_ctx.selected_sprite, x, y)
          vals[x] = c
          x = x + 1
        until x == 8
        print(vals[0] .. "," .. vals[1] .. "," .. vals[2] .. "," .. vals[3] .. "," .. vals[4] .. "," .. vals[5] .. "," .. vals[6] .. "," .. vals[7] .. ",")
        x = 0
        y = y + 1
      until y == 8
      print("}")
      print("===========END EXPORT===========")
      dialog:ShowDialog("Export complete", "Check the console!")
    end

    if lx > 16 and lx <= 16 + 19 then -- CART
      print("Exporting to cart " .. cart_info.loaded_cart)
      local filepath = cart_info.cart_path .. cart_info.loaded_cart .. "/gfx/spr0.bin"
      local file = io.open (filepath , "wb")
      local i = 0
      repeat
        file:write(string.char(peek8(0x20000 + i)))
        i = i + 1
      until i == 64 * 256

      file:close()
    end
  end
end
