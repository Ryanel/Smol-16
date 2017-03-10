# Colors
There are 256 maximum colors on screen at once. Each color is a palette index.
Each displayable pixel is `1` byte long.

## Framebuffer
The framebuffer resides in memory at 0x10000
It is `256 * 224 = 57344 bytes`, or `0xE000` bytes.

## Palettes

### PCT (Palette Color Table)
This defines the colors that the system works with.
It is `512` bytes long, with each entry being a short.

Each entry is a BGR16 value, it's represented like this:

`0BBBBBGG GGGRRRRR`

This allows 32,767 possible colors, in which 255 can be used at any one time.

Notice how I said *255*. The system does not "count" color 0 when doing drawing operations. It _skips_ over that color when blitting. Or, in other words, it's transparent. A work around is to directly write a 0 to the framebuffer, and it will be displayed as black (but black's also color 0x1, so not much use in it)

The PCT is exposed in memory, directly after the Framebuffer.

### SPT (Sub Palette Table)
Unlike the PCT, this does not store colors, it stores indexes to PCT entries. Each entry is 1 byte, so the table is `256 bytes (0x100)`.
This is actually _not_ used by the hardware, but by the standard drawing functions.
They act as switchboards, changing colors.

A psudocode example:
```lua
function sprite(s, x, y, pal)
    -- Go over each pixel. Let's say this one is 0xA
    local color_to_write = spt[pal][pixel_color]
    -- color_to_write is now 0xB, as the SPT maps entry 0xA to 0xB
end
```
There are 8 SPT's avalable, SPT0-7. Since there is no state associated with them (unlike the PCT), you can overwrite the SPT's anytime you want. This allows for 8 regular SPT's and an infinite amount of virtual SPTs.

## Backgrounds
There are 2 backgrounds, BG0 and BG1
