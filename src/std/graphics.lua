mem_vram = 0x10000
mem_videoregs = 0x1FF00

-- Draws to the screen, and blocks if nb = 0
function flip(nb)
    if not nb then nb = 0 end
    poke8(mem_videoregs + 0x00, 0xFF)
    if nb then return end -- Nonblocking
    repeat until peek8(mem_videoregs + 0x00) == 0x0 -- Blocking
end

function set_pixel(x, y, c)
    if(c == 0) then return end
    if(x > 255 or x < 0) then return end
    if(y > 223 or y < 0) then return end
    if (c == nil) then
        c = peek8(mem_videoregs + 0x50)
    end
    local index = (y * screenWidth) + x
    poke8(index + mem_vram, c)
end

function set_color(c)
    poke8(mem_videoregs + 0x50, c)
end


-- Drawing functions

function draw_rect(x0, y0, x1, y1)
    local x = x0
    local y = y0

    while true do
        if(y == y1) then break end
        repeat
            set_pixel(x,y); x = x + 1;
        until x > x1 or x == x1
        x = x0
        y = y + 1
    end
end

function draw_line(x0, y0, x1, y1)
    local x = x0
    local y = y0
    local dx = math.abs(x1 - x0)
    local dy = math.abs(y1 - y0)
    local sx = 0
    local sy = 0
    local err = 0

    if x0 < x1 then sx = 1
    else sx = -1 end
    if y0 < y1 then sy = 1
    else sy = -1 end

    if dx > dy then err=dx/2
    else err = -dy / 2 end
    while true do
        set_pixel(x, y)
        if(x == x1 and y == y1) then
            break
        end
        local err2 = err
        if err2 > -dx then
            err = err - dy
            x = x + sx
        end
        if err2 < -dy then
            err = err + dx
            y = y + sy
        end
    end
end

function draw_string(str, x, y, rel_size)
    if not rel_size then rel_size = 1 end
    local index = 1
    local draw_x = x
    local draw_y = y
    repeat
        draw_char(string.byte(str, index) - 32, draw_x, draw_y, rel_size)
        draw_x = draw_x + 4 * rel_size
        index = index + 1
    until index == string.len(str) + 1

end

function draw_char(c, drawx, drawy, rel_size)
    if not rel_size then rel_size = 1 end
    local sprite_x = 0
    local sprite_y = 0
    repeat
        repeat
            local location = 0x1F000 + (c * 3) + floor(sprite_y / 2)
            local index = sprite_x
            if (sprite_y % 2) == 1 then index = index + 4 end
            if hasbit(peek8(location), bit(index)) then
                local scaled_x = sprite_x * rel_size
                local scaled_y = sprite_y * rel_size
                draw_rect(scaled_x + drawx, scaled_y + drawy, scaled_x + drawx + rel_size, scaled_y + drawy + rel_size)
            end
            sprite_x = sprite_x + 1
        until sprite_x == 4
        sprite_y = sprite_y + 1
        sprite_x = 0
    until sprite_y == 6
end

function spr(num, dx0, dy0, width, height, flip_x, flip_y ,pal)
    if not pal then pal = -1 end
    if not width then width = 1 end
    if not height then height = 1 end
    if not flip_x then flip_x = false end
    if not flip_y then flip_y = false end

    -- Sprite index
    local sx0 = 0
    local sy0 = 0
    -- Draw index
    local sx1 = 8 * width
    local sy1 = 8 * height
    repeat
        repeat
            local pix = peek8(0x20000 + (num * 64) + (sy0 * sy1) + sx0)

            if (pal ~= -1) then
                pix = peek8(0x1E200 + (pal * 256) + pix)
            end

            set_pixel(sx0 + dx0, sy0 + dy0, pix)
            sx0 = sx0 + 1
        until sx0 == sx1
        sx0 = 0
        sy0 = sy0 + 1
    until sy0 == sy1

end

function spr_set(num, x, y, c)
    poke8(0x20000 + (num * 64) + (8 * y) + x, c)
end
