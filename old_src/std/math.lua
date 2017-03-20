function floor(n)
  return n - (n % 1)
end

function round(n)
  return n>=0 and floor(n+0.5) or math.ceil(n-0.5)
end

function bit(p)
  return 2 ^ (p)
end

function hasbit(x, p)
  return x % (p + p) >= p
end

function sin(z)
  return math.sin(z)
end

_rng_seed = 111

function rnd(max)
  local result = 0
  _rng_seed = (_rng_seed * 58321) + 113224
  _rng_seed = _rng_seed % 9930185
  return result % max
end
