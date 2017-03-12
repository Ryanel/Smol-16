Mouse = class(function ()
    function __init()
      this.x = 0
      this.y = 0
      this.color = 1
    end
    function draw()
      if(global_timer % 15 == 0) then
        this.color = ((this.color + 1) % 16)
        this.color = math.max(this.color, 3)
      end

      set_color(this.color)
      draw_rect(this.x,this.y, this.x + 2, this.y + 2)
      draw_rect(this.x,this.y, this.x + 6, this.y + 2)
      draw_rect(this.x,this.y, this.x + 2, this.y + 6)
      set_color(this.color - 1)
      draw_rect(this.x + 2,this.y + 2, this.x + 4, this.y + 4)
      draw_rect(this.x + 2,this.y + 2, this.x + 5, this.y + 4)
      draw_rect(this.x + 2,this.y + 2, this.x + 4, this.y + 5)
      set_color(this.color - 2)
      draw_rect(this.x + 4,this.y + 4, this.x + 6, this.y + 6)
    end
    function update()
      this.x = _get_mouse_x()
      this.y = _get_mouse_y()
    end

  end)

mouse = Mouse()
