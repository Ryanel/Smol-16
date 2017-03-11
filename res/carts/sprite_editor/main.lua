spr_edit_index = 0
selected_color = 0
select_cursor_color = 7

palette_cursor = {
    color = 0,
    cursor_color = 7
}

cursor = {
    x = 0,
    y = 0
}

global_timer = 0

function _init()
    screen_clear()
    palette_reset() -- Resets Palette
    poke16(0x1E000 + (255 * 2), 0xABCDEF)
end

function _update()
    if btn(4) then selected_color = selected_color + 1 end
    if btn(5) then selected_color = selected_color - 1 end

    -- Enforce limits

    if (selected_color < 0) then selected_color = 0 end
    if (selected_color > 255) then selected_color = 255 end

    global_timer = global_timer + 1
end

function draw_palette()
    local pal_color = 0

    repeat
        set_color(pal_color)

        local x_offset = floor((pal_color * 4) % 256)
        local y_offset = floor(pal_color / 64)
        local x = x_offset
        local y = (y_offset * 4) + 200

        draw_rect(x, y, x + 4, y + 4)
        if (pal_color == selected_color and (global_timer % 30) > 10) then
            if(pal_color == select_cursor_color) then
                set_color(select_cursor_color - 1)
            else
                set_color(select_cursor_color)
            end

            draw_rect(x, y, x + 4, y + 4)
            set_color(pal_color)
            draw_rect(x + 1, y + 1, x + 3, y + 3)
        end

        pal_color = pal_color + 1
    until pal_color == 256
end

function _draw()
    screen_clear()
    set_color(12)
    draw_rect(0,0, 256, 8)
    draw_rect(0,224 - 8, 256, 224)
    set_color(selected_color)
    draw_string("Selected color:" .. selected_color, 8,224 - 7)
    draw_string("X:" .. cursor.x .. " ; Y:" .. cursor.y, 8, 1)
    draw_palette()
    flip()
end
