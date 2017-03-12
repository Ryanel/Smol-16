Panel = class(function()
    function __init()
      this.x = 0
      this.y = 0
      this.w = 128
      this.h = 64
      this.window_color = 7
      this.title = ""
      this.hide_pane = false
    end

    function set_bounds(x, y, w, h)
      this.x = x
      this.y = y
      this.w = w
      this.h = h
    end

    function in_bounds()
      local mouse_in = false
      if (mouse.x >= this.x and mouse.x <= this.x + this.w) then
        if(mouse.y >= this.y and mouse.y <= this.y + this.h) then
          mouse_in = true
        end
      end
      this.is_in = mouse_in
    end

    function update()

    end

    function draw()
      if(not this.hide_pane) then
        set_color(this.window_color)
        draw_rect(this.x, this.y, this.x + this.w, this.y + 8) -- Titlebar
        set_color(1)
        draw_string(this.title, this.x + 8 ,this.y + 1)
        set_color(6)
        draw_rect(this.x, this.y + 8, this.x + this.w, this.y + this.h) -- Titlebar
      else

      end

      this.draw_content()
    end

    function draw_content()

    end

    function OnDrag(x, y)
      -- Move panel x and y
    end
  end)
