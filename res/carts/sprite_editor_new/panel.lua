Panel = Object:extend()

function Panel:new(x, y, w, h)
  self.x = x or 0
  self.y = y or 0
  self.w = w or 0
  self.h = w or 0
  self.window_color = 7
  self.title = ""
  self.no_chrome = false
  self.cursor_hold = {}
  self.cursor_hold.x = -100
  self.cursor_hold.y = -100
  self.cursor_hold.is = false
end

function Panel:SetBounds(x, y, w, h)
  self.x = x
  self.y = y
  self.w = w
  self.h = h
end

function Panel:Update()
  self:UpdateContent()
  --self:DragTitleBar() FIXME: Moves all other windows
end

function Panel:Draw()
  self:DrawTitlebar()
  self:DrawContent()
end

function Panel:DrawTitlebar()
  if(self.no_chrome) then return end
  set_color(self.window_color)
  draw_rect(self.x, self.y, self.x + self.w, self.y + 8) -- Titlebar
  set_color(8)
  draw_string(self.title, self.x + 8 ,self.y + 1)
  set_color(6)
  draw_rect(self.x, self.y + 8, self.x + self.w, self.y + self.h) -- Titlebar
end

function Panel:UpdateContent() end
function Panel:DrawContent() end

function Panel:InBounds(x, y)
  local inside = false
  if (x >= self.x and x <= self.x + self.w) then
    if(y >= self.y and y <= self.y + self.h) then
      inside = true
    end
  end
  return inside
end

function Panel:DragTitleBar()
  if(self.no_chrome) then return end
  if btn(9) then
    if(self.cursor_hold.is == false) then
      self.cursor_hold.x = mouse.x - self.x
      self.cursor_hold.y = mouse.y - self.y
      self.cursor_hold.is = true
    end
    if(mouse.y - self.y < 8 and self:InBounds(mouse.x, mouse.y)) then
      self.y = mouse.y - self.cursor_hold.y
      if self.w < 255 then
        self.x = mouse.x - self.cursor_hold.x
      end
    end
  else
    self.cursor_hold.is = false
  end
end
