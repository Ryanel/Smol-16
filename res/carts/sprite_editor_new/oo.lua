function class(def)
  local class = {}
  local parents = {}

  local upv
  local env = _G

  local wraps
  local function super(parent_class)
    if not parent_class then
      parent_class = parents[1]
    end

    local this = this
    local that = {}
    for k,v in pairs(parent_class) do
      that[k] = type(v) == 'function' and wraps(this, v) or v
    end

    return setmetatable(that, that)
  end

  function wraps(this, func)
    return function(...)
      local t = env.this
      local s = env.super

      env.this = this
      env.super = super

      local ret = pcall(func, ...)

      env.this = t
      env.super = s

      return ret
    end
  end

  function class.__init()end

  for i=1,math.huge do
    inherit, v = debug.getlocal(def, i)
    if not inherit then break end

    local parent_class = _G[inherit]
    for i=1,math.huge do
      local name, pclass = debug.getlocal(2,i,1)
      if not name then break
      elseif name == inherit then
        parent_class = pclass
        break
      end
    end

    if parent_class and type(parent_class) == 'table' then
      table.insert(parents, parent_class)
      for k,v in pairs(parent_class) do
        class[k] = v
      end
    else
      error(string.format('Class "%s" not valid.', name))
    end
  end

  for i=1,math.huge do
    local name, value = debug.getupvalue(def, i)
    if not name then break
    elseif name == '_ENV' then
      env = value
      upv = i
      break
    end
  end

  local _env = setmetatable({}, {
      __index= function(t, name)
        local value = class[name]
        return value ~= nil and value or env[name]
      end,
      __newindex = function(t, name, value)
        class[name] = value
      end
    })

  local function senv(env)
    if upv then debug.setupvalue(def, upv, env)
    else _G = env end
  end

  senv(_env)
  env.pcall(def, env.table.unpack(parents))
  senv(env)

  return setmetatable({}, {
      __ipairs = function() return ipairs(class) end,
      __pairs = function() return pairs(class) end,
      __index = function(t, name) return class[name] end,
      __index_new = function(t, name, value) class[name] = value end,
      __call = function(...)
        local this = {}
        for k,v in pairs(class) do
          this[k] = type(v) == 'function' and wraps(this, v) or v
        end
        this.__class = class
        this.__init(...)

        return setmetatable(this, this)
      end
    })
end
