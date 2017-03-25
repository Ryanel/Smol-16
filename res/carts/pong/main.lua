-- Adapted for Smol16 from https://blog.afoolishmanifesto.com/posts/pong/

-- pong
-- <3 frew

-- this is a simple pong game
-- written to learn pico-8 and
-- basic game programming.

-- the structure should be
-- fairly easy to understand,
-- but i'll write out some
-- notes in these comments to
-- help others learn.

------------------------------

-- first off, we have the
-- following two "player" or
-- "paddle" objects. they have
-- six members each:
--
-- x - the column
-- y - the row
-- h - the height
-- score
-- ai - computer controlled
-- player - which player

_cart_header = {
  name = "Pong",
  entry = "_init",
  irq_clock = "_update",
  irq_ppu = "_render",
  irq_spu = "_irq_spu"
}

--load_sample(0)
file_load_spritesheet("carts/pong/gfx/spr0.bin")
l = {
  x = 5,
  y = 50,
  h = 24,
  score = 0,
  ai = true,
  player = 1
}

r = {
  x = 256 - 8,
  y = 50,
  h = 24,
  score = 0,
  ai = true,
  player = 0
}

function do_ai(p, b)
  if (b.y < p.y + p.h/5) then
    p.y = p.y - 1
  elseif (b.y > p.y + p.h/5) then
    p.y = p.y + 1
  end
end

function update_player(p, b)
  if (io.btn(0) or io.btn(2)) then
    l.ai = false
  end

  if (not p.ai) then
    if (io.btn(0, p.player)) then p.y = p.y - 2 end
    if (io.btn(2, p.player)) then p.y = p.y + 2 end
  else
    do_ai(p, b)
  end
end

function update_ball(b)
  b.x = b.x + b.dx
  b.y = b.y + b.dy
end

middle = r.y + r.h/2
function reset_ball(b)
  b.x = 50
  b.y = middle
  b.h = 4
  b.dx = 2
  b.dy = 0
end

b = {}
reset_ball(b)

function intersection(l, r, b)
  -- calc_angle will be true
  -- if a player hit the ball.
  calc_angle = false
  -- and p will be set to which
  -- player hit the ball.
  p = {}

  -- ball passed left paddle
  if (b.x < 0) then
    r.score = r.score + 1
    reset_ball(b)
    -- ball passed right paddle
  elseif (b.x > 256) then
    l.score = l.score + 1
    reset_ball(b)
    -- ball hit ceiling or floor
  elseif (
      b.y < 0 or b.y > 224) then
      b.dy = -b.dy
      snd_sfx(0)
      -- ball hit left paddle
    elseif (b.x < l.x and
        b.y >= l.y - b.h and
        b.y <= l.y + l.h + b.h
      ) then
        b.dx = -b.dx
        calc_angle = true
        p = l
        -- ball hit right paddle
      elseif (b.x > r.x - 8 and
          b.y >= r.y - b.h and
          b.y <= r.y + r.h + b.h
        ) then
          b.dx = -b.dx
          calc_angle = true
          p = r
        end

        if (calc_angle) then
          -- every now and then
          -- increase ball speed
          if (rnd(1) > 0.9) then
            b.dx = b.dx *(1 + rnd(0.01))
          end

          -- this is complicated!
          -- the first line scales
          -- the location that therectfill
          -- paddle one third of the
          -- way from the top, it
          -- will be set to
          -- circa 0.3
          rl = (b.y - p.y)/p.h

          -- this basically makes it
          -- as if the paddle were
          -- part of a circle, so
          -- that bouncing off the
          -- middle is flat, the top
          -- is a sharp angle, and
          -- the bottom is a sharp
          -- angle. i had to look
          -- up sin and cosine for
          -- this, but it might be
          -- just as easy to play
          -- with the numbers till
          -- you get what you want
          rl = rl
          b.dy = (rl - 0.5) * 3

          -- boop
          snd_sfx(0)
        end
      end

      function _init()
        ppu.cls(0)
        ppu.pal_reset()
      end

      function _update()
        update_player(l, b)
        update_player(r, b)
        update_ball(b)

        intersection(l, r, b)

        if io.btnp(4) then
          b.dx = -b.dx
        end
        if io.btn(5) then
          b.y = 0
          b.dy = -1
        end
      end

      function drawshape(s)
        gfx_rect(floor(s.x) , floor(s.y), floor(s.x+4), floor(s.y+s.h))
      end

      function _render()
        ppu.cls(0)

        spr(1, floor(l.x - 4), floor(l.y))
        spr(1 + 8, floor(l.x - 4), floor(l.y + 8))
        spr(1 + 16, floor(l.x - 4), floor(l.y + 16))

        spr(2, floor(r.x), floor(r.y))
        spr(2 + 8, floor(r.x), floor(r.y + 8))
        spr(2 + 16, floor(r.x), floor(r.y + 16))
        spr(0, floor(b.x), floor(b.y))

        -- draw the dotted line in
        -- the middle of the field
        set_color(6)
        for i=0,64 do
          gfx_rect(127 , 1 + i*5 ,
            127+2, i*5+3)
        end
        set_color(12)
        draw_string(l.score, l.x + 5, 5, 4)
        set_color(10)
        draw_string(r.score, r.x - 14, 5, 4)
        set_color(7)
        draw_string("CPU: "..cpu.get_usage() .. "%", 8, 224 - 8)
        flip()
      end
