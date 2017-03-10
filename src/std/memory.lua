function memcpy(dest, src, len)
    local i = 0
    repeat
        poke8(dest + i, peek8(src + i))
        i = i + 1
    until i == len
end
