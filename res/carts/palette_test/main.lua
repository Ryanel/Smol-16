timer = 0
function _init()
  ppu.cls(0)
  ppu.pal_reset()
end

function _update()
  --[[
  pct_edit(8, timer, timer ,timer)
  pct_edit(9, timer, timer / 2 ,timer / 2)
  pct_edit(10, 40 + timer / 10, timer * 10 ,100)
  pct_edit(7, sin(timer / 100) * 128, 128, 128)
  pct_edit(0, 0, timer % 64, timer % 64)
  if (timer % 60 > 30) then
    pct_edit(6, 0, 0 ,255)
  else
    pct_edit(6, 255, 255 ,0)
  end
  ]]
  --[[

  ]]
  timer = timer + 1
end

function _render()
  ppu.cls(0)
  local i = 0
  local k = 0
  local co = 0
  repeat
    k = 0
    repeat
      i = 0
      repeat
        ppu.poke8(i + (k * (256 / 16)) + co * 256, k) -- Writes indexes directly to VRAM
        i = i + 1
      until i == 16
      k = k + 1
    until k == 16
    co = co + 1
  until co == 16

  i = 0
  repeat
    local x = (i * 8) % 256
    local y = floor((i * 8) / 256)
    set_color((i % 15) + 1)
    draw_char(i, x, 64 + (y * 8))
    i = i + 1
  until i == 256

  set_color(8)

  draw_string("Hiya there, everyone! This is Smol-16. It's a game console.",0, 224 - 32)

  set_color(7)
  draw_string("HIYA THERE, EVERYONE! THIS IS SMOL-16. IT'S A GAME CONSOLE.",0, 224 - 48)

  set_color(10)
  draw_string("hiya there, everyone! this is smol-16. it's a game console.",0, 224 - 64)

  flip()
end
