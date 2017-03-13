--[[
The standard library for Smol16
This is parsed before a cart is loaded. All functions here are avalable for use.
]]

_std_version = 1

function require(location)
  local path = _cart_path .. "/" .. location
  print("[Cart]: Requiring " .. path)
  dofile(path)
end

dofile("data/std/math.lua")
dofile("data/std/memory.lua")
dofile("data/std/graphics.lua")
