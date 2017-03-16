GraphicsExporter = Panel:extend()

function GraphicsExporter:new()
  GraphicsExporter.super:new()
  local width = 50
  local height = 16
  self:SetBounds(256 - width, 8, width, height)
  self.title = "Exporter"
  self.window_color = 5
  self.window_text = 8
  self.scroll_index = 0
  self.minimised = false
  self.export_mode = 0
end

function GraphicsExporter:DrawButton(x, y, w, h, str)
  set_color(16)
  local lx = self.x + x
  local ly = self.y + y
  draw_rect(lx, ly + 8, lx + w, ly + h + 8)
  set_color(7)
  draw_rect(lx + 1, ly + 9, lx + w - 1, ly + h + 7)
  set_color(16)
  draw_string(str,lx + 2, ly + 10)
end

function GraphicsExporter:DrawContent()
  self:DrawButton(0,0, 16,9, "Lua")
  self:DrawButton(16,0, 19,9, "Cart")
  self:DrawButton(16 + 19,0, 15,9, "PNG")
end

function GraphicsExporter:UpdateContent()
  if btnp(9) and self:InBounds(mouse.x, mouse.y) then
    local lx = mouse.x - self.x
    if lx <= 16 then -- LUA
      print("==========BEGIN EXPORT==========")

      local func = "set_pixel("
      local x = 0
      local y = 0
      repeat
        repeat
          local c = spr_get(sprite_editor_ctx.selected_sprite, x, y)
          if c ~= 0 and c ~= nil then
            print(func .. x .. "," .. y .. "," .. c ..")")
          end
          x = x + 1
        until x == 8
        x = 0
        y = y + 1
      until y == 8

      print("===========END EXPORT===========")
    end

    if lx > 16 and lx <= 16 + 19 then -- CART

    end
  end
end
