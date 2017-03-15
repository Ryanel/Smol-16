Panel = Object:extend()

function Panel:new(x, y, w, h)
  self.x = x or 0
  self.y = y or 0
  self.w = w or 0
  self.h = w or 0

  -- Window properties
  self.window_color = 7
  self.window_text = 8
  self.title = ""
  self.no_chrome = false

  -- Dragging
  self.dragging_x = -100
  self.dragging_y = -100
  self.dragging_is = false
  self.nodrag_x = false
  self.nodrag_y = false
end

function Panel:SetBounds(x, y, w, h)
  self.x = x
  self.y = y
  self.w = w
  self.h = h
end

function Panel:Update()
  self:UpdateContent()
  self:DragTitleBar() --FIXME: Moves all other windows
end

function Panel:Draw()
  self:DrawTitlebar()
  self:DrawContent()
end

function Panel:DrawTitlebar()
  if(self.no_chrome) then return end
  set_color(self.window_color)
  draw_rect(self.x, self.y, self.x + self.w, self.y + 8) -- Titlebar
  set_color(self.window_text)
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
  if(self.no_chrome) then return end -- Nothing to drag, abort.
  if btn(9) and self:InBounds(mouse.x, mouse.y) then
    -- Determine if we're on the title bar
    if mouse.y - self.y < 8 then
      if self.dragging_is == false then
        -- We just start dragging
        self.dragging_x = mouse.x - self.x
        self.dragging_y = mouse.y - self.y
        self.dragging_is = true
      end
      if self.nodrag_y == false then self.y = mouse.y - self.dragging_y end
      if self.nodrag_x == false then self.x = mouse.x - self.dragging_x end
    end
  else
    if self:InBounds(mouse.x, mouse.y) then
      self.dragging_is = false
    end
  end
end
