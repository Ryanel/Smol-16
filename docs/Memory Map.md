#Memory

Addresses are 32bit's long.
Ram is not flat.

WRAM: (Work RAM)
        0x0       -> 0xFFFF Program RAM
VRAM: (Video RAM)
        0x10000   -> 0x1E000 Framebuffer
        0x1E000   -> 0x1E200 PCT
        0x1E200   -> 0x1EA00 SPT (x8, each 0x100)
        0x1EA00   -> 0x1EB00 Font
        0x1EE00   -> 0x1EF00 Sprite Attribute Table
        -- 0x1000 free here
        0x1FF00   -> 0x20000 Video Registers
        0x20000   -> 0x28000 Sprite Data (64 bytes per sprite, 128 x 256, 16 sprites across, 32 down)
ARAM: (Audio RAM)
