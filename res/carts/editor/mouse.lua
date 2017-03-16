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

  set_pixel(0 + self.x,0 + self.y,8)
  set_pixel(0 + self.x,1 + self.y,9)
  set_pixel(1 + self.x,1 + self.y,8)
  set_pixel(0 + self.x,2 + self.y,9)
  set_pixel(1 + self.x,2 + self.y,9)
  set_pixel(2 + self.x,2 + self.y,8)
  set_pixel(0 + self.x,3 + self.y,9)
  set_pixel(1 + self.x,3 + self.y,9)
  set_pixel(2 + self.x,3 + self.y,9)
  set_pixel(3 + self.x,3 + self.y,8)
  set_pixel(0 + self.x,4 + self.y,9)
  set_pixel(1 + self.x,4 + self.y,9)
  set_pixel(2 + self.x,4 + self.y,9)
  set_pixel(3 + self.x,4 + self.y,9)
  set_pixel(4 + self.x,4 + self.y,8)
  set_pixel(0 + self.x,5 + self.y,9)
  set_pixel(1 + self.x,5 + self.y,9)
  set_pixel(0 + self.x,6 + self.y,9)

end

function Mouse:update()
  self.x = _get_mouse_x()
  self.y = _get_mouse_y()
end

mouse = Mouse()
