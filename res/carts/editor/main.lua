global_timer = 0

cart_header = {
  name = "Sprite Editor"
}

require("object.lua")
require("panel.lua")
require("dialog.lua")
require("editor_mode.lua")
require("mode_switcher.lua")
require("cart/editor_cart.lua")
require("graphics/editor_graphics.lua")
require("mouse.lua")

local cpu_adverage = {}
local cpu_adverage_index = 0
local cpu_adverage_samples = 30

sprite_editor_ctx = {
  selected_sprite = 0,
  palette = -1,
  selected_color = 0
}
cart_editor_ctx = {
  cart_name = ""
}
function _init()
  palette_reset()

  editor_modes[0] = EditorCart(0, "Cart")
  editor_modes[1] = EditorGraphics(1, "Graphics")
  editor_mode = 1
  poke8(0x1E200 + 10, 9)
  poke8(0x1E200 + 9, 8)
  poke8(0x1E300 + 10, 12)
  poke8(0x1E300 + 9, 13)

  local i = 0
  repeat
    cpu_adverage[i] = stat_cpu()
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
  cpu_adverage[cpu_adverage_index] = stat_cpu()
  cpu_adverage_index = cpu_adverage_index + 1
  if(cpu_adverage_index == cpu_adverage_samples) then
    cpu_adverage_index = 0
  end
end

function _draw()
  cls(1)

  --Draw cpu
  set_color(7)

  editor_modes[editor_mode]:Draw()
  mode_switcher:Draw()
  dialog:Draw()
  mouse:draw()
  draw_cpu()
  flip()
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
  draw_string("AVG CPU: "..round(cpu_adv*100)*0.01 .. "%", 200, 1)
end
