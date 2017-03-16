ModeSwitcher = Panel:extend()

function ModeSwitcher:new()
  ModeSwitcher.super:new()
  self:SetBounds(0,0,256,8)
  self.title = "Mode Switcher"
  self.no_chrome = true
  self.nodrag_x = true
  self.nodrag_y = true
  self.minimisable = false
  self.total_modes = 2
end

function ModeSwitcher:DrawContent()
  set_color(12)
  draw_rect(self.x, self.y, self.x + self.w, self.y + self.h)

  -- Draw modes
  local modes = 0
  local x = 0
  local y = 0
  repeat
    if(modes == 0) then
      set_pixel(0 + (x * 8),0,5); set_pixel(7 + (x * 8),0,5); set_pixel(1 + (x * 8),1,6); set_pixel(6 + (x * 8),1,6); set_pixel(2 + (x * 8),2,7); set_pixel(5 + (x * 8),2,7); set_pixel(2 + (x * 8),5,7); set_pixel(5 + (x * 8),5,7); set_pixel(1 + (x * 8),6,6); set_pixel(6 + (x * 8),6,6); set_pixel(0 + (x * 8),7,5); set_pixel(7 + (x * 8),7,5);
    end
    if modes == 1 then
      set_pixel(3 + (x * 8),0,8);set_pixel(4 + (x * 8),0,8);set_pixel(2 + (x * 8),1,8);set_pixel(3 + (x * 8),1,9);set_pixel(4 + (x * 8),1,9);set_pixel(5 + (x * 8),1,8);set_pixel(1 + (x * 8),2,8);set_pixel(2 + (x * 8),2,9);set_pixel(3 + (x * 8),2,9);set_pixel(4 + (x * 8),2,9);set_pixel(5 + (x * 8),2,9);set_pixel(6 + (x * 8),2,8);set_pixel(1 + (x * 8),3,9);set_pixel(2 + (x * 8),3,10);set_pixel(3 + (x * 8),3,10);set_pixel(4 + (x * 8),3,10);set_pixel(5 + (x * 8),3,10);set_pixel(6 + (x * 8),3,9);set_pixel(0 + (x * 8),4,9);set_pixel(1 + (x * 8),4,10);set_pixel(2 + (x * 8),4,10);set_pixel(3 + (x * 8),4,16);set_pixel(4 + (x * 8),4,10);set_pixel(5 + (x * 8),4,16);set_pixel(6 + (x * 8),4,10);set_pixel(7 + (x * 8),4,9);set_pixel(0 + (x * 8),5,9);set_pixel(1 + (x * 8),5,10);set_pixel(2 + (x * 8),5,10);set_pixel(3 + (x * 8),5,16);set_pixel(4 + (x * 8),5,10);set_pixel(5 + (x * 8),5,16);set_pixel(6 + (x * 8),5,10);set_pixel(7 + (x * 8),5,9);set_pixel(1 + (x * 8),6,9);set_pixel(2 + (x * 8),6,10);set_pixel(3 + (x * 8),6,10);set_pixel(4 + (x * 8),6,10);set_pixel(5 + (x * 8),6,10);set_pixel(6 + (x * 8),6,9);set_pixel(2 + (x * 8),7,9);set_pixel(3 + (x * 8),7,9);set_pixel(4 + (x * 8),7,9);set_pixel(5 + (x * 8),7,9);

    end
    if (editor_mode == modes and global_timer % 30 > 15) then
      set_color(7)
      draw_rect(self.x + (x * 8), self.y + (y * 8),self.x + (x * 8) + 8, self.y + (y * 8) + 1)
      draw_rect(self.x + (x * 8), self.y + (y * 8) + 7,self.x + (x * 8) + 8, self.y + (y * 8) + 8)
      draw_rect(self.x + (x * 8), self.y + (y * 8),self.x + (x * 8), self.y + (y * 8) + 8)
      draw_rect(self.x + (x * 8) + 7, self.y + (y * 8),self.x + (x * 8) + 8, self.y + (y * 8) + 8)
    end
    x = x + 1
    modes = modes + 1
  until modes == self.total_modes
  -- Selection
  if(self:InBounds(mouse.x, mouse.y)) then
    local mode = floor(mouse.x / 8)
    if(editor_modes[mode] == nil) then return end

    -- Tooltip
    set_color(0)
    local x = mouse.x + 4
    local y = mouse.y + 8
    local str = editor_modes[mode].name
    draw_rect(x, y, x + string.len(str) * 4 + 4, y + 8)
    set_color(7)
    draw_string(str, x + 2, y + 1)
  end
end

function ModeSwitcher:UpdateContent()

  if btnp(9) and self:InBounds(mouse.x, mouse.y) then
    local mode_to_switch = floor(mouse.x / 8)
    if(editor_modes[mode_to_switch] == nil) then return end

    editor_modes[editor_mode]:Hide()
    editor_mode = mode_to_switch
    editor_modes[editor_mode]:Show()
  end

end

mode_switcher = ModeSwitcher()
