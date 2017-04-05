#Smol16 specs

* Ram: 128kb
* Screen: 256x224px (32 x 28 cells). Each cell has it's own pallete (16 colors).
* Layers: LY1, LY2, LY3, SPRITE
* Sprites: 8x8 -> 64x64, 128 simultainous. Sprites limited to 16 colors
* Cartsize: 1Mbit
* Sound: 4 channels (A), 64 tones (B). (AABBBBBB)
* Input
    * DPAD
    * A
    * B
    * X
    * Y
    * Select

## Memory Map
0x00000 -> 0x04000 Sprite memory
0x10000 -> 0x1F000 VRAM
0x1F000 -> 0x1F100 Palette
0x1F100 -> 0x1F200 Palette
0x1FF00 -> 0x1FFFF System IO Space
    * 0x1FF00 = FRAME_READY
## Sprite
64 bytes. 1 byte per pixel.
8 x 8 size

## Palette
Starts at 0x1F000
3 bytes per entry. R, G, B.
Entry 0 is always transparent
