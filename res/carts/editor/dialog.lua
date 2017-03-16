Dialog = Panel:extend()
local width = 128
local height = 32
function Dialog:new()
  Dialog.super:new()

  self:SetBounds((256 / 2 ) - (width / 2), 8, width, height)
  self.title = "Exporter"
  self.window_color = 5
  self.window_text = 9
  self.visible = false
  self.message = "No message"
end

function Dialog:ShowDialog(title, message)
  self.title = title
  self.message = message
  self.minimised = false
  self:Show()
end
function Dialog:DrawContent()
  set_color(8)
  draw_string(self.message, self.x + 8, self.y + 10)
  self:DrawButton(width - 34, 22 - 8, 32, 8, "Close")
end

function Dialog:UpdateContent()

end

function Dialog:Update()
  Dialog.super.Update(self)
  if self.minimised then self:Hide() end
end

dialog = Dialog()
