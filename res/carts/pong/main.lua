-- Adapted for Smol16 from https://blog.afoolishmanifesto.com/posts/pong/

-- pong
--   <3 frew

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
-- "paddle" objects.  they have
-- six members each:
--
--  x      - the column
--  y      - the row
--  h      - the height
--  score
--  ai     - computer controlled
--  player - which player

l = {
  x      =  5,
  y      = 50,
  h      = 24,
  score  =  0,
  ai     = true,
  player = 1
}

r = {
  x      = screenWidth - 8,
  y      = 50,
  h      = 24,
  score  =  0,
  ai     = true,
  player = 0
}

function do_ai(p, b)
  if (b.y < p.y + p.h/2) then
     p.y = p.y - 1
  elseif (b.y > p.y + p.h/2) then
     p.y = p.y + 1
  end
end

function update_player(p, b)
  if (btn(0) or btn(2)) then
    l.ai = false
  end

  if (not p.ai) then
    if (btn(0, p.player)) then p.y = p.y - 1 end
    if (btn(2, p.player)) then p.y = p.y + 1 end
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
  b.x  = 50
  b.y  = middle
  b.h  = 4
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
  elseif (b.x > screenWidth) then
     l.score = l.score + 1
     reset_ball(b)
  -- ball hit ceiling or floor
  elseif (
    b.y < 0 or b.y > screenHeight) then
     b.dy = -b.dy
  -- ball hit left paddle
  elseif (b.x < l.x and
      b.y >= l.y - b.h and
      b.y <= l.y + l.h + b.h
     ) then
     b.dx = -b.dx
     calc_angle = true
     p = l
  -- ball hit right paddle
  elseif (b.x > r.x and
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
     -- angle.  i had to look
     -- up sin and cosine for
     -- this, but it might be
     -- just as easy to play
     -- with the numbers till
     -- you get what you want
     rl = rl
     angle = sin(rl)
     b.dy = (rl - 0.5) * 3

     -- boop
     --sfx(0)
  end
end

function _init()
    screen_clear()
    palette_reset()
    set_color(1)
end

function _update()
  update_player(l, b)
  update_player(r, b)
  update_ball(b)

  intersection(l, r, b)
end

function drawshape(s)
  draw_rect(floor(s.x)  , floor(s.y), floor(s.x+4), floor(s.y+s.h))
end

function _draw()
    screen_clear()
    set_color(12)
    drawshape(l)
    set_color(10)
    drawshape(r)
    set_color(8)
    drawshape(b)

    -- draw the dotted line in
    -- the middle of the field
    set_color(6)
    for i=0,64 do
      draw_rect(127  , 1 + i*5  ,
               127+2, i*5+3)
    end
    set_color(12)
    draw_string(l.score, l.x + 5, 5, 4)
    set_color(10)
    draw_string(r.score, r.x - 14, 5, 4)
    flip()
end
