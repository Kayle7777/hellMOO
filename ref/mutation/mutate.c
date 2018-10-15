{who, ?silent = 0} = args;
if (this in who.mutations)
    if (!silent)
        who:tell("You've already got the '", this.name, "' mutation.");
    endif
    return 0;
elseif (!who.mutation_slots)
    if (!silent)
        who:tell("You don't have any free mutation slots.");
    endif
    return 0;
endif
if ($mutations.purity:is_on(who))
    who:tell("Your genetic purity prevents you from accepting any mutations. Sorry.");
    return 0;
endif
for x in (this.incompatible_with)
    if (bad = $lu:list_is_a(who.mutations, x))
        if (!silent)
            who:tell("You realize your ", bad[1].name, " mutation will keep you from ever developing the '", this.name, "' mutation.");
        endif
        return 0;
    endif
endfor
for x in (who.mutations)
    if ($lu:is_one_of(x, this.incompatible_with))
        if (!silent)
            who:tell("You realize your ", x.name, " mutation will keep you from ever developing the '", this.name, "' mutation.");
        endif
        return 0;
    endif
endfor
for x in (this.requires)
    if (typeof(x) == LIST)
        found = 0;
        for y in (x)
            if (y in who.mutations)
                found = 1;
                break;
            endif
        endfor
        if (!found)
            if (!silent)
                who:tell("You realize you can never develop this mutation without first having ", $su:english_list($lu:map_verb(x, "name"), "", " or "));
            endif
            return 0;
        endif
    else
        if (!(x in who.mutations))
            if (!silent)
                who:tell("You realize you can never develop this mutation without first having ", x.name, ".");
            endif
            return 0;
        endif
    endif
endfor
if (valid(this.class) && this.class_max)
    got = 0;
    for x in (who.mutations)
        if (x.class == this.class)
            got = got + 1;
        endif
    endfor
    classname = strsub(this.class.name, "generic ", "");
    if (got >= this.class_max)
        if (!silent)
            who:tell("You realize you've already got ", $su:english_number(this.class_max), " ", classname, "s, and can't get any more.");
        endif
        return 0;
    endif
    got = got + 1;
    if (!silent)
        if (got < this.class_max)
            who:tell("You realize you can only get ", this.class_max - got, " more ", classname, "s.");
        elseif (got == this.class_max)
            who:tell("You realize you can't get any more ", classname, "s after this.");
        endif
    endif
endif


who.mutations = {@who.mutations, this};
for x in (this.skill_mods)
    if (!silent)
        this:report_change(who, x[1].name, abs(x[2]), x[2] > 0);
    endif
    x[1]:flush(who);
endfor
if (this.health_bonus)
    who.health_max = who.health_max + this.health_bonus;
    if (!silent)
        this:report_change(who, "health max", this.health_bonus, this.health_bonus > 0);
    endif
endif
if (!silent)
    fork (0)
        who:aat($su:ps(this.mutate_msg, who));
        suspend(1);
        who:systell(tostr($ansi.green, $ansi.bold_on, "You've developed the '", this.name, "' mutation!", $ansi.reset));
    endfork
endif
if (is_a(who, $rpg_player))
    this.mutants = setadd(this.mutants, who);
endif
who.mutation_slots = who.mutation_slots - 1;
if (is_a(who, $player) && is_a(who.respawn, #2180))
    fork (5)
        who.respawn:update_clone(who);
    endfork
endif
if (is_a(who, $rpg_player))
    $nets.gamenet:announce(#2, tostr($su:nn(who), " has developed the '", this.name, "' mutation."), 1);
endif
return 1;
