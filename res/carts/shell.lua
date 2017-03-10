--[[
shell.lua
This is the Smol-16 shell!
By: Corwin McKnight
]]

-- Variables
local timer = 0
local cursor = {
    x = 0,
    y = 0,
    x_coord = 0,
    y_coord = 0,
    visible = true
}

function doInput()
    if btnp(0) then cursor.y = cursor.y - 1 end -- UP
    if btnp(1) then cursor.x = cursor.x + 1 end -- RIGHT
    if btnp(2) then cursor.y = cursor.y + 1 end -- DOWN
    if btnp(3) then cursor.x = cursor.x - 1 end -- LEFT
    -- Ensure cursor stays in bounds
    if(cursor.x < 0) then cursor.x = 0 end
    if(cursor.y < 0) then cursor.y = 0 end
end

function updateCursor()
    cursor.x_coord = cursor.x * 4
    cursor.y_coord = cursor.y * 6
    cursor.visible = (timer % 30) < 15
end

-- System callback functions
function _init()
    cls()
    pal()
end

function _update()
    timer = timer + 1
    doInput()
    updateCursor()
end

-- Drawing functions

function drawCursor()
    color(7) -- Set default color to white
    if (cursor.visible) then
        color(7)
        rect(cursor.x_coord, cursor.y_coord, cursor.x_coord + 4, cursor.y_coord + 6)
    end
end


function _draw()
    cls() -- Clear screen
    color(7) -- Set default color to white
    draw_string("$> Hello, Console!", 0, 0)
    drawCursor() -- Draw cursor
    flip() -- You must inform the GPU that there's a new frame rendered
end
