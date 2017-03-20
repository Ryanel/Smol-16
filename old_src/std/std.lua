--[[
The standard library for Smol16
This is parsed before a cart is loaded. All functions here are avalable for use.
]]

_std_version = 1

function console_log(message)
  local header_name = ""
  if(cart_header ~= nil) then header_name = cart_header.name
  else header_name = "Cart" end
  print("["..header_name.."]: ".. message)
end

function require(location)
  local path = _cart_path .. "/" .. location
  console_log("Requiring " .. path)
  dofile(path)
end

function load_sample(id)
  local sample_path = _cart_path .. "/sfx/"..id..".wav"
  snd_loadsample(id, sample_path)
end

dofile("data/std/math.lua")
dofile("data/std/memory.lua")
dofile("data/std/graphics.lua")
dofile("data/std/file.lua")
