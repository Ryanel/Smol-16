global_timer = 0

cart_header = {
  name = "Sprite Editor"
}

editor = {
  background_color = 1
}

require("object.lua")
require("panel.lua")
require("dialog.lua")
require("editor_mode.lua")
require("mode_switcher.lua")
require("cart/editor_cart.lua")
require("graphics/editor_graphics.lua")
require("music/editor_music.lua")
require("mouse.lua")

local cpu_adverage = {}
local cpu_adverage_index = 0
local cpu_adverage_samples = 30

function _init()
  ppu.pal_reset()

  editor_modes[0] = EditorCart(0, "Cart")
  editor_modes[1] = EditorGraphics(1, "Graphics")
  editor_modes[4] = EditorMusic(4, "Music")
  editor_mode = 1

  editor_modes[editor_mode]:Show()

  LoadCart();

  mem.poke8(0x1E200 + 10, 9)
  mem.poke8(0x1E200 + 9, 8)
  mem.poke8(0x1E300 + 10, 12)
  mem.poke8(0x1E300 + 9, 13)

  local i = 0
  repeat
    cpu_adverage[i] = cpu.get_usage()
    i = i + 1
  until i == cpu_adverage_samples
end

function _update()
  mouse:update()

  editor_modes[editor_mode]:Update()
  mode_switcher:Update()
  dialog:Update()

  -- Update Global Timer
  global_timer = global_timer + 1

  -- Update CPU Adverage
  cpu_adverage[cpu_adverage_index] = cpu.get_usage()
  cpu_adverage_index = cpu_adverage_index + 1
  if(cpu_adverage_index == cpu_adverage_samples) then
    cpu_adverage_index = 0
  end
end

function _render()
  ppu.cls(editor.background_color)
  draw_windows()
  mouse:draw()
  draw_cpu()
  flip()
end

function draw_windows()
  editor_modes[editor_mode]:Draw()
  mode_switcher:Draw()
  dialog:Draw()
end

function draw_cpu()
  local i = 0
  local cpu_adv = 0
  repeat
    cpu_adv = cpu_adv + cpu_adverage[i]
    i = i + 1
  until i == cpu_adverage_samples
  cpu_adv = cpu_adv / cpu_adverage_samples
  set_color(7)
  draw_string("AVG CPU: "..round(cpu_adv*10)*0.1 .. "%", 200, 1)
end
