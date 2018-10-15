{who, ?silent = 0} = args;
if (!this in who.augments)
    return 0;
endif
who.augments = setremove(who.augments, this);
"Remove the skill mods";
for x in (this.skill_mods)
    if (!silent)
        $mutation:report_change(who, x[1].name, abs(x[2]), x[2] < 0);
    endif
    x[1]:flush(who);
endfor
"Something here about bodyparts";
if (this.health_change)
    who.health_max = who.health_max - this.health_change;
    if (!silent)
        $mutation:report_change(who, "health max", this.health_change, this.health_change < 0);
    endif
endif
this.users = setremove(this.users, who);
return 1;
