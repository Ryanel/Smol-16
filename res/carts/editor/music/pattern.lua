local width = 256
local height = 224 - 64

local ui_config = {
  row = {
    width = 11,
    main_row = 9,
    height = 8
  },
  tracks = {
    num = 8
  }
}
PatternPanel = Panel:extend()

function PatternPanel:new()
  PatternPanel.super:new()

  self:SetBounds(0, 224-height, width, height)
  self.title = "Tracker"
  self.window_color = 6
  self.window_bg = 5
  self.window_text = 9
  self.no_chrome = true
  self.nodrag_x = true
end

function PatternPanel:DrawChrome()
  local step = (width - ui_config.row.width) / ui_config.tracks.num
  local i = 0
  repeat
    local x = round((i * step) + self.x + ui_config.row.width)
    local y = self.y
    repeat
      set_pixel(x,y,5)
      y = y + 1
    until y == self.y + self.h
    i = i + 1
  until i == ui_config.tracks.num + 1
  self:DrawRowNums()
end

function PatternPanel:DrawRowNums()
  local pat_num = ctx_music.row - ui_config.row.main_row
  local r_index = 0
  set_color(16)
  repeat
    if pat_num >= 0 then
      draw_string(string.format("%02X",pat_num),2, self.y + r_index * ui_config.row.height + 2)
    end
    r_index = r_index + 1
    pat_num = pat_num + 1
  until pat_num >= ctx_music.row_max
end

function PatternPanel:DrawContent()
  self:DrawChrome()
  self:DrawCurrentRow()
end

function PatternPanel:DrawCurrentRow()
  local x = 0
  local y = self.y + (ui_config.row.main_row*ui_config.row.height)
  repeat

    set_pixel(x,y,8)
    set_pixel(x,y + ui_config.row.height,8)
    x = x + 1
  until x == 256
end

function PatternPanel:UpdateContent()
  if(global_timer % 4 == 0) then
    if ctx_music.row >= ctx_music.row_max then
      ctx_music.row = 0
    else
      ctx_music.row = ctx_music.row + 1
    end
  end
end
