EditorMusic = EditorMode:extend()

require("music/pattern.lua")

ctx_music = {
  idx = 0,
  row = 0,
  row_max = 64
}

function EditorMusic:new(index, name)
  EditorMusic.super:new(index, name)
  self.name = "Music"
  self.pattern = PatternPanel()
end

function EditorMusic:Show()
  self.pattern:Show()
  editor.background_color = 6
end

function EditorMusic:Hide()
  self.pattern:Hide()
end

function EditorMusic:Update()
  self.pattern:Update()
end

function EditorMusic:Draw()
  self.pattern:Draw()
end
