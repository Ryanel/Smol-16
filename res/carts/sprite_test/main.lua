function tellme(offset, story)
        local n,v
        for n,v in pairs(story) do
                if n ~= "loaded" and n ~= "_G" then
                io.write (offset .. n .. " " )
                print (v)
                if type(v) == "table" then
                        tellme(offset .. "--> ",v)
                end
                end
        end
end



function _init()
    tellme("",_G)

    pal_reset() -- Resets Palette
end

function _update()
end

function _draw()
    flip()
end
