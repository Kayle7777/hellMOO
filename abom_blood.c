who = args[1];
if (this.location == who)
    rng = random(20);
    if (who:is_freak() && rng != 1)
        if (rng > 14)
            who:tell("The ", this.name, " stops sizzling and burning.");
            $recycler:_recycle(this);
        endif
        return pass(@args);
    endif
    body = who:random_bodypart();
    who:tell("The ", this.name, " sizzles and pops on your ", body.name, ".");
    who:take_damage(this.damage[1], this.damage[2] + random(this.damage[3] - this.damage[2]), body, this);
endif
return pass(@args);
