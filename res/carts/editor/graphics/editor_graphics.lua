EditorGraphics = EditorMode:extend()

sprite_editor_ctx = {
  selected_sprite = 0,
  selected_sprite_width = 1,
  selected_sprite_height = 1,
  palette = -1,
  selected_color = 0
}

require("graphics/palette.lua")
require("graphics/sprite_editor.lua")
require("graphics/spritesheet.lua")
require("graphics/export.lua")
function EditorGraphics:new(index, name)
  EditorMode.super:new(index, name)
  self.name = "Graphics"
  self.palette = Palette()
  self.editor = SpriteEditor()
  self.spritesheet = SpriteSheetEditor()
  self.export = GraphicsExporter()
end

function EditorGraphics:Show()
  editor.background_color = 1
  self.palette:Show()
  self.editor:Show()
  self.spritesheet:Show()
  self.export:Show()
end

function EditorGraphics:Hide()
  self.palette:Hide()
  self.editor:Hide()
  self.spritesheet:Hide()
  self.export:Hide()
end

function EditorGraphics:Update()
  self.palette:Update()
  self.editor:Update()
  self.spritesheet:Update()
  self.export:Update()
end

function EditorGraphics:Draw()
  self.palette:Draw()
  self.editor:Draw()
  self.spritesheet:Draw()
  self.export:Draw()
end
