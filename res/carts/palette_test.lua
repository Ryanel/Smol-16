pal() -- Resets Palette
local i = 0
local k = 0
repeat
    i = 0
    repeat
        poke8(i + 0x10000 + (k * 16), i) -- Writes indexes directly to VRAM
        i = i + 1
    until i == 255
    k = k + 1
until k == 256

color(8)

i = 0
repeat
    local x = (i * 8) % screenWidth
    local y = floor((i * 8) / screenWidth)
    color((i % 15) + 1)
    draw_char(i, x, 24 + (y * 8))
    i = i + 1
until i == 256

color(7)

draw_string("Hiya there, everyone! This is Smol-16. It's a game console.",0, screenHeight - 14)

flip()

draw_string("HIYA THERE, EVERYONE! THIS IS SMOL-16. IT'S A GAME CONSOLE.",0, screenHeight - 28)
draw_string("hiya there, everyone! this is smol-16. it's a game console.",0, screenHeight - 42)
