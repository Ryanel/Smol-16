ModeSwitcher = Panel:extend()

function ModeSwitcher:new()
  ModeSwitcher.super:new()
  self:SetBounds(0,0,256,8)
  self.title = "Mode Switcher"
  self.no_chrome = true
  self.nodrag_x = true
  self.nodrag_y = true
  self.minimisable = false
  self.total_modes = 4
end

function ModeSwitcher:DrawContent()
  set_color(12)
  draw_rect(self.x, self.y, self.x + self.w, self.y + self.h)

  -- Draw modes
  local modes = 0
  local x = 1
  local y = 0
  repeat
    if(modes == 0) then
      local sprite = {
        10,5,10,5,10,5,10,0,
        10,5,10,5,10,5,10,5,
        5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
        5,5,5,5,5,5,5,5,
      }
      spr_array(sprite, x * 8, 0)
    end
    if modes == 1 then
      local sprite = {
        0,0,0,8,8,0,0,0,
        0,0,8,9,9,8,0,0,
        0,8,9,9,9,9,8,0,
        0,9,10,10,10,10,9,0,
        9,10,10,16,10,16,10,9,
        9,10,10,16,10,16,10,9,
        0,9,10,10,10,10,9,0,
        0,0,9,9,9,9,0,0,
      }
      spr_array(sprite, x * 8, 0)
    end

    if modes == 2 then
      local sprite = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,7,0,0,0,0,0,0,
        0,0,7,0,0,0,0,0,
        0,7,0,0,0,0,0,0,
        0,0,0,0,7,7,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
      }

      spr_array(sprite, x * 8, 0)
    end

    if modes == 3 then
      local sprite = {
        0,0,0,0,0,0,0,0,
        0,7,7,7,7,7,7,0,
        0,6,0,0,6,0,0,0,
        0,7,7,7,7,7,7,0,
        0,0,6,5,0,6,0,0,
        0,7,7,7,7,7,7,0,
        0,6,0,6,5,0,6,0,
        0,0,0,0,0,0,0,0,
      }

      spr_array(sprite, x * 8, 0)
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
    local mode = floor(mouse.x / 8) - 1
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
    local mode_to_switch = floor(mouse.x / 8) - 1
    if(editor_modes[mode_to_switch] == nil) then return end

    editor_modes[editor_mode]:Hide()
    editor_mode = mode_to_switch
    editor_modes[editor_mode]:Show()
  end

end

mode_switcher = ModeSwitcher()
