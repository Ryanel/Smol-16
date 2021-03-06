# Smol-16

Smol-16 is a fantasy game console, inspired by [Pico-8](http://www.lexaloffle.com/pico-8.php). It is not made by laxaloffle.
However, it's not a clone, but more or a "decendant". If the Pico-8 is the NES, then the Smol-16 is like the SNES.

![Smol-16, running the sprite editor](docs/screenshots/sprite_editor_1.png)

While the Pico-8 had more of a *I could do this in a week* sort of philosophy, the Smol-16 is a **I can make a full game** sort of philosophy.

## Note
Smol-16 is in early development! Be wary about using it (though do contribute and watch it's progress!)

## Technical Specifications
* 256 x 224 pixel display (SNES resolution)
* 256 color palette (BGR-15 programmable)]
* 256 sprites on screen, 8x8 tiles, 4bpp (16 colors)
* Program code is in Lua, no token limits
* 8 channel sound, sampled at 48khz

## Features
* A Lua standard library, editable by the user.
    * Treat it like editing the Microcode on a N64. It's to get as much performance as possible out of the machine

## Quirks
* Color 0 is transparent for sprite operations, but black. (Color 16 is also black)

# TODO
* Allow multiple sprites edited at once
* Finish Text Input
