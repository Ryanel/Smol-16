
-- Setup the enviroment

local memory_map = {
    sprite = 0x20000,
    vram = 0x10000,
    palette = 0x1E000,
    kernal_draw_color = 0x1F300,
    kernal_pos_x = 0x1F301,
    kernal_pos_y = 0x1F302,
    kernal_clip_x = 0x1F303,
    kernal_clip_y = 0x1F304,
    kernal_clip_w = 0x1F305,
    kernal_clip_h = 0x1F306,
    kernal_print_x = 0x1F308,
    kernal_print_y = 0x1F30A
}

_rng_seed = 111

function rnd(max)
    local result = 0
    _rng_seed = (_rng_seed * 58321) + 113224
    _rng_seed = _rng_seed % 9930185
    return result % max
end


function sin(z)
    return math.sin(z)
end

function bit(p)
    return 2 ^ (p)
end

-- Typical call:  if hasbit(x, bit(2)) then ...
function hasbit(x, p)
    return x % (p + p) >= p
end

function memcpy(dest, src, len)
    local i = 0
    repeat
        poke8(dest + i, peek8(src + i))
        i = i + 1
    until i == len
end

function pset_raw(x, y, c)
    local index = y * screenWidth + x
    poke8(index + memory_map.vram, c)
end

function pget(x, y)
    return peek8(y * screenWidth + x)
end

function floor(n)
    return n - (n % 1)
end

function flip(nb)
    if not nb then nb = 0 end

    poke8(0x1FF00, 0xFF)
    if nb then return end -- Nonblocking
    repeat until peek8(0x1FF00) == 0x0 -- Blocking

end

function pset(x, y, c)
    if(c == 0) then return end
    local correctedX = x + peek8(memory_map.kernal_pos_x)
    local correctedY = y + peek8(memory_map.kernal_pos_y)
    if (c == nil) then
        c = peek8(memory_map.kernal_draw_color)
    end
    pset_raw(correctedX, correctedY, c)
end

function line(x0, y0, x1, y1)
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
        pset(x, y)
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

function draw_string(str, x, y)
    local index = 1
    local draw_x = x
    local draw_y = y
    repeat
        draw_char(string.byte(str, index) - 32, draw_x, draw_y)
        draw_x = draw_x + 4
        index = index + 1
    until index == string.len(str) + 1

end

function draw_char(c, drawx, drawy)
    local sprite_x = 0
    local sprite_y = 0
    repeat
        repeat
            local location = 0x1000 + (c * 3) + floor(sprite_y / 2)
            local index = sprite_x
            if (sprite_y % 2) == 1 then index = index + 4 end
            if hasbit(peek8(location), bit(index)) then
                pset(sprite_x + drawx, sprite_y + drawy)
            end
            sprite_x = sprite_x + 1
        until sprite_x == 4
        sprite_y = sprite_y + 1
        sprite_x = 0
    until sprite_y == 6
end

function rect(x0, y0, x1, y1)
    local x = x0
    local y = y0

    while true do
        if(y == y1) then break end
        repeat
            pset(x,y); x = x + 1;
        until x > x1 or x == x1
        x = x0
        y = y + 1
    end
end

function sprite(n, x0, y0, w, h, fx, fy)
    -- Handle default values
    if not w then w = 1 end
    if not h then h = 1 end
    if not fx then fx = false end
    if not fy then fy = false end

    local x = 0
    local y = 0
    local x1 = 8 * w
    local y1 = 8 * h
    while true do
        if(y == y1) then break end
        repeat
            local data = peek8(memory_map.sprite + (n * 64) + (y * y1) + x)
            if(fx and not fy) then
                pset(x0 + x1 - x - 1,y0 + y, data)
            end
            if(fy and not fx) then
                pset(x0 + x,y0 + y1 - y - 1, data)
            end
            if(fx and fy) then
                pset(x0 + x1 - x - 1,y0 + y1 - y - 1, data)
            end
            if(not fx and not fy) then
                pset(x0 + x,y0 + y, data)
            end
            x = x + 1
        until x > x1 or x == x1
        x = 0
        y = y + 1
    end
end
function pal()
    pal_reset()
end

function pct_edit(index,r,g,b)
    local color = _to_bgr(floor(r),floor(g),floor(b))
    poke16(0x1E000 + (index * 2), color)
end

function color (color) poke8(memory_map.kernal_draw_color, color) end

-- Define exection enviroment
_ENV = {
    -- Exposed standard lua library stuff. The goal is to get rid of this
    string = string,
    math = math,
    -- Exposed HW functions
    poke8 = poke8,
    poke16 = poke16,
    peek8 = peek8,
    peek16 = peek16,
    screenWidth = screenWidth,
    screenHeight = screenHeight,

    -- STD functions
    color = color,
    pal = pal,
    pal_reset = pal_reset,
    pset = pset,
    pset_raw = pset_raw,
    draw_char = draw_char,
    draw_string = draw_string,
    bit = bit,
    hasbit = hasbit,
    _rng_seed = _rng_seed,
    -- Math
    floor = floor,

    -- Utils
    _to_bgr = _to_bgr
}
