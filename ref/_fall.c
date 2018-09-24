#761:_fall   this none this
who = args[1];
altitude = args[2];
amax = altitude;
speed = 0;
accel = this.accel;
speed_max = this.speed_max;
sdescs = {"", "Umm.", "Whoa.", "Whoa!", "Shit!", "SHIT!", "SHIIIIT!!", "AAAAAGGGHH!!", "AAAAAGGGHHHHH!!!"};
target = this:random_ground();
if (!valid(target))
  0 && $nets.marvinnet:_announce(#-1, "No valid ground for " + $su:nn(this) + " at " + $su:nn(area(this)), 1);
  if (0 && who.listening)
    who:tell("Well it doesn't seem like you really can fall here. Not really sure what to tell you...");
  endif
  this:announce_all(who:dnamec(), " blows around violently in the breeze.");
  exits = this.exits;
  for exit in (exits)
    if (is_a(exit, $flyer.hatch_type[2]))
      exits = setremove(exits, exit);
    endif
  endfor
  if (exits)
    exits[random($)]:move(who);
  else
    player:tell("Well... this is awkward. I guess contact an admin? I dunno, man, I'm just making suggestions here.");
  endif
  return;
endif
announced = 0;
dcode = random(999999);
player.flight_ncatch = 1;
while (is_a(who, $actor) && who.location == this && altitude > 0 && player.flight_ncatch)
  smeter = $rpg:graphical_meter(speed, speed_max, 15, 0, $ansi.red, $ansi.red);
  ameter = $rpg:graphical_meter(altitude, amax, 20, 0, $ansi.cyan, $ansi.cyan);
  who.altitude = altitude;
  sdesc = min(8, max(speed / 9, 1));
  sdesc = sdescs[sdesc];
  who:tell("spd ", smeter, " alt ", ameter, " (", altitude, " m) ", sdesc);
  para = #-1;
  for x in (who.wearing ! ANY => {})
    if (this.atmospheric == 1)
      if (is_a(x, #770))
        para = x;
        if (!para.deployed)
          para.deploy_code = dcode;
        endif
      endif
    endif
  endfor
  if (valid(para) && para.location == who && para.deployed && para.deploy_code == dcode)
    speed = max(10, speed - para.deceleration);
  else
    speed = min(speed + accel, speed_max);
  endif
  altitude = max(0, altitude - speed);
  if (is_a(who, $creature))
    who.altitude = altitude;
  endif
  if (altitude < 150 && !announced)
    target:announce_all("That human figure in the sky seems to be falling straight toward your position!");
    announced = 1;
  endif
  suspend(1);
endwhile
if (is_a(who, $actor) && altitude < 1 && who.location == this)
  if (is_a(target, #761) && target.atmospheric == 1 && this.atmospheric == 0)
    who:tell($ansi.bold_on + $ansi.red + "You are consumed by the searing heat of reentry!" + $ansi.reset);
    who:take_damage(#280, 500, $bodypart, #2);
  endif
  who:moveto(target);
  "  target:fall_into(who, speed - 6);";
  target:fall_into(who, this, speed - 6);
endif
