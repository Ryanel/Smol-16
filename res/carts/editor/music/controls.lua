local width = 256
local height = 64

TrackerControlPanel = Panel:extend()

function TrackerControlPanel:new()
  TrackerControlPanel.super:new()

  self:SetBounds(0, 0, width, height)
  self.title = "Tracker"
  self.window_color = 6
  self.window_bg = 5
  self.window_text = 9
  self.no_chrome = true
  self.nodrag_x = true
end

function TrackerControlPanel:DrawContent()
  self:DrawBorder()
end

function TrackerControlPanel:DrawBorder()
  local x = 0
  local y = self.y + self.h
  repeat
    set_pixel(x,y,5)
    x = x + 1
  until x == 256
end

function TrackerControlPanel:UpdateContent()
  if(global_timer % 4 == 0) then
    if ctx_music.row >= ctx_music.row_max then
      ctx_music.row = 0
    else
      ctx_music.row = ctx_music.row + 1
    end
  end
end
