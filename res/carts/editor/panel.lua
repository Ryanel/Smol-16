Panel = Object:extend()

function Panel:new(x, y, w, h)
  self.x = x or 0
  self.y = y or 0
  self.w = w or 0
  self.h = w or 0

  -- Window properties
  self.window_color = 7
  self.window_bg = 6
  self.window_text = 8
  self.title = ""
  self.no_chrome = false

  -- Dragging
  self.dragging_x = -100
  self.dragging_y = -100
  self.dragging_is = false
  self.nodrag_x = false
  self.nodrag_y = false
  self.minimised = false
  self.minimisable = true
  self.visible = true
  self.panel_global = {
    being_dragged = nil
  }
end

function Panel:SetBounds(x, y, w, h)
  self.x = x
  self.y = y
  self.w = w
  self.h = h
end

function Panel:Hide()
  self.visible = false
end

function Panel:Show()
  self.visible = true
end

function Panel:Update()
  local inBounds = self:InBounds(mouse.x, mouse.y)
  if btnp(9) and mouse.y - self.y <= 8 and inBounds then -- If we're clicking on the titlebar
    if(mouse.x >= self.x + self.w - 8 and self.minimisable) then -- Minimise
      if self.minimised then
        self.minimised = false
      else
        self.minimised = true
      end
    end
  end
  if self.visible and self.minimised == false then
    self:UpdateContent()
  end
  if self.visible then
    self:DragTitleBar() --FIXME: Moves all other windows
  end
end

function Panel:DrawButton(x, y, w, h, str)
  set_color(16)
  local lx = self.x + x
  local ly = self.y + y
  gfx_rect(lx, ly + 8, lx + w, ly + h + 8)
  set_color(7)
  gfx_rect(lx + 1, ly + 9, lx + w - 1, ly + h + 7)
  set_color(16)
  draw_string(str,lx + 2, ly + 10)
end

function Panel:Draw()
  if self.visible == true then
    self:DrawTitlebar()
  end
  if self.minimised == false and self.visible then
    self:DrawContent()
  end
end

function Panel:DrawTitlebar()
  if(self.no_chrome) then return end
  set_color(self.window_color)
  gfx_rect(self.x, self.y, self.x + self.w, self.y + 8) -- Titlebar
  set_color(self.window_text)
  draw_string(self.title, self.x + 4 ,self.y + 1)

  -- Draw controls
  if self.minimisable then
    set_color(8)
    gfx_rect(self.x + self.w - 8, self.y, self.x + self.w, self.y + 8)
    set_color(7)
    gfx_rect(self.x + self.w - 7, self.y + 3, self.x + self.w - 1, self.y + 5)
  end
  if self.minimised == false then
    set_color(self.window_bg)
    gfx_rect(self.x, self.y + 8, self.x + self.w, self.y + self.h) -- Titlebar
  end
end

function Panel:UpdateContent() end
function Panel:DrawContent() end

function Panel:InBounds(x, y)
  return self:InRect(x,y,self.x, self.y, self.w, self.h)
end

function Panel:InRect(x, y, rx, ry, rw, rh)
  local inside = false
  if (x >= rx and x <= rx + rw) then
    if(y >= ry and y <= ry + rh) then
      inside = true
    end
  end
  return inside
end

function Panel:DragTitleBar()
  if(self.no_chrome) then return end -- Nothing to drag, abort.
  if btn(9) and self:InBounds(mouse.x, mouse.y) then
    -- Determine if we're on the title bar
    if mouse.y - self.y < 8 and (self.panel_global.being_dragged == nil or self.panel_global.being_dragged == self) then
      if self.dragging_is == false then
        self.panel_global.being_dragged = self
        -- We just start dragging
        self.dragging_x = mouse.x - self.x
        self.dragging_y = mouse.y - self.y
        self.dragging_is = true
      end
    end
  else
    if self:InBounds(mouse.x, mouse.y) then
      self.dragging_is = false
      self.panel_global.being_dragged = nil
    end
  end
  if self.dragging_is == true then
    if self.nodrag_y == false then self.y = mouse.y - self.dragging_y end
    if self.nodrag_x == false then self.x = mouse.x - self.dragging_x end
  end
end
