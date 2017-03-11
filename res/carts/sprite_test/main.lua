function _init()
    screen_clear()
    palette_reset() -- Resets Palette

    local y = 0
    -- Write default sprites
    spr_set(0, 2, y, 9)
    spr_set(0, 3, y, 9)
    spr_set(0, 4, y, 9)
    spr_set(0, 5, y, 9)
    y = y + 1

    spr_set(0, 1, y, 9)
    spr_set(0, 2, y, 10)
    spr_set(0, 3, y, 10)
    spr_set(0, 4, y, 10)
    spr_set(0, 5, y, 10)
    spr_set(0, 6, y, 9)
    y = y + 1
    spr_set(0, 0, y, 9)
    spr_set(0, 1, y, 10)
    spr_set(0, 2, y, 10)
    spr_set(0, 3, y, 10)
    spr_set(0, 4, y, 10)
    spr_set(0, 5, y, 10)
    spr_set(0, 6, y, 10)
    spr_set(0, 7, y, 9)
    y = y + 1
    spr_set(0, 0, y, 9)
    spr_set(0, 1, y, 10)
    spr_set(0, 2, y, 10)
    spr_set(0, 3, y, 10)
    spr_set(0, 4, y, 10)
    spr_set(0, 5, y, 10)
    spr_set(0, 6, y, 10)
    spr_set(0, 7, y, 9)
    y = y + 1
    spr_set(0, 0, y, 9)
    spr_set(0, 1, y, 10)
    spr_set(0, 2, y, 10)
    spr_set(0, 3, y, 10)
    spr_set(0, 4, y, 10)
    spr_set(0, 5, y, 10)
    spr_set(0, 6, y, 10)
    spr_set(0, 7, y, 9)
    y = y + 1
    spr_set(0, 0, y, 9)
    spr_set(0, 1, y, 10)
    spr_set(0, 2, y, 10)
    spr_set(0, 3, y, 10)
    spr_set(0, 4, y, 10)
    spr_set(0, 5, y, 10)
    spr_set(0, 6, y, 10)
    spr_set(0, 7, y, 9)
    y = y + 1
    spr_set(0, 1, y, 9)
    spr_set(0, 2, y, 10)
    spr_set(0, 3, y, 10)
    spr_set(0, 4, y, 10)
    spr_set(0, 5, y, 10)
    spr_set(0, 6, y, 9)
    y = y + 1
    spr_set(0, 2, y, 9)
    spr_set(0, 3, y, 9)
    spr_set(0, 4, y, 9)
    spr_set(0, 5, y, 9)

    poke8(0x1E200 + 10, 9)
    poke8(0x1E200 + 9, 8)
    poke8(0x1E300 + 10, 12)
    poke8(0x1E300 + 9, 13)
end

function _update()
end

function _draw()
    screen_clear()
    spr(0, 0, 0,  1, 1, false, false, -1)
    spr(0, 16, 0, 1, 1, false, false,  0)
    spr(0, 32, 0, 1, 1, false, false,  1)

    flip()
end
