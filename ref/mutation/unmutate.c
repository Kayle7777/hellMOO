{who, ?silent = 0} = args;
if (!this in who.mutations)
    return 0;
endif
who.mutations = setremove(who.mutations, this);
for x in (this.skill_mods)
    if (!silent)
        this:report_change(who, x[1].name, abs(x[2]), x[2] < 0);
    endif
    x[1]:flush(who);
endfor
if (this.health_bonus)
    who.health_max = who.health_max - this.health_bonus;
    if (!silent)
        this:report_change(who, "health max", this.health_bonus, this.health_bonus < 0);
    endif
endif
fork (0)
    if (!silent)
        who:systell(tostr($ansi.green, $ansi.bold_on, "You've lost the '", this.name, "' mutation!", $ansi.reset));
    endif
    if (is_a(who.respawn, #2180))
        who.respawn:update_clone(who, 0, 1);
    endif
endfork
who.mutation_slots = who.mutation_slots + 1;
this.mutants = setremove(this.mutants, who);
return 1;
