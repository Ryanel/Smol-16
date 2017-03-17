EditorMusic = EditorMode:extend()

require("music/pattern.lua")
require("music/controls.lua")
ctx_music = {
  idx = 0,
  row = 0,
  row_max = 64
}

function EditorMusic:new(index, name)
  EditorMusic.super:new(index, name)
  self.name = "Music"
  self.pattern = PatternPanel()
  self.controls = TrackerControlPanel()
end

function EditorMusic:Show()
  self.pattern:Show()
  self.controls:Show()
  editor.background_color = 6
end

function EditorMusic:Hide()
  self.pattern:Hide()
  self.controls:Hide()
end

function EditorMusic:Update()
  self.pattern:Update()
  self.controls:Update()
end

function EditorMusic:Draw()
  self.pattern:Draw()
  self.controls:Draw()
end
