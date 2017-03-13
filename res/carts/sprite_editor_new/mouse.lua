Mouse = Object:extend()

function Mouse:new()
  self.x = 0
  self.y = 0
  self.color = 1
end

function Mouse:draw()
  if(global_timer % 15 == 0) then
    self.color = ((self.color + 1) % 16)
    self.color = math.max(self.color, 3)
  end

  set_color(self.color)
  draw_rect(self.x,self.y, self.x + 2, self.y + 2)
  draw_rect(self.x,self.y, self.x + 6, self.y + 2)
  draw_rect(self.x,self.y, self.x + 2, self.y + 6)
  set_color(self.color - 1)
  draw_rect(self.x + 2,self.y + 2, self.x + 4, self.y + 4)
  draw_rect(self.x + 2,self.y + 2, self.x + 5, self.y + 4)
  draw_rect(self.x + 2,self.y + 2, self.x + 4, self.y + 5)
  set_color(self.color - 2)
  draw_rect(self.x + 4,self.y + 4, self.x + 6, self.y + 6)
end

function Mouse:update()
  self.x = _get_mouse_x()
  self.y = _get_mouse_y()
end

mouse = Mouse()
