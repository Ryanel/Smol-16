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

function enforce_limits()
    if (selected_color < 0) then selected_color = 0 end
    if (selected_color > 255) then selected_color = 255 end
end

function update_input()
    cursor.x = _get_mouse_x()
    cursor.y = _get_mouse_y()

end

function _update()
    update_input()
    if btn(9) and cursor.y > 200 and cursor.y < 216 then -- Palette selection
        local pal_x = floor((cursor.x) / 4)
        local pal_y = floor((cursor.y - 200) / 4)
        selected_color = floor(pal_y * 64 + pal_x)
    end


    global_timer = global_timer + 1
    enforce_limits()
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
    -- Draw UI bars
    set_color(12)
    draw_rect(0,0, 256, 8)
    draw_rect(0,224 - 8, 256, 224)
    set_color(7)
    draw_string("Sprite Editor (no file)" , 8,224 - 7)
    draw_string("X:" .. cursor.x .. " ; Y:" .. cursor.y, 8, 1)
    -- Draw Palette
    set_color(13)
    draw_rect(0,224 - 32, 256, (224 - 32) + 8)
    set_color(7)
    draw_string("Palette (" .. selected_color .. ")", 8,224 - 31)

    draw_palette()

    draw_rect(cursor.x,cursor.y, cursor.x + 2, cursor.y + 2)
    draw_rect(cursor.x + 1,cursor.y + 1, cursor.x + 3, cursor.y + 3)
    draw_rect(cursor.x + 2,cursor.y + 2, cursor.x + 4, cursor.y + 4)
    flip()
end
