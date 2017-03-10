cursor = {}
cursor.x = 0
cursor.y = 0

cur_color = 8
shouldClear = false
size = 1
pal()

function _init()

end

function _update()

    if btn(0) then cursor.y = cursor.y - 1 end -- UP
    if btn(1) then cursor.x = cursor.x + 1 end -- RIGHT
    if btn(2) then cursor.y = cursor.y + 1 end -- DOWN
    if btn(3) then cursor.x = cursor.x - 1 end -- LEFT

    if btnp(4) then cur_color = cur_color + 1 end
    if btnp(5) then cur_color = cur_color - 1 end

    if btnp(6) then size = size + 1 end
    if btnp(7) then size = size - 1 end
    if size < 1 then size = 1 end
    color(cur_color)
end

function _draw()
    if shouldClear then
        cls()
    end

    rect(cursor.x,cursor.y,cursor.x + size,cursor.y + size)
    flip()
end
