{who, ?silent = 0} = args;
if (this in who.augments)
    if (!silent)
        who:tell("You've already got a ", this.name, " installed.");
    endif
    return 0;
"Something to handle bodypart replacers overlapping here";

endif
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
who.augments = {@who.augments, this};
for x in (this.skill_mods)
    "Syntax for these is LIST {{#329, -4}, ...}";
    if (!silent)
        $mutation:report_change(who, x[1].name, abs(x[2]), x[2] > 0);
    endif
    x[1]:flush(who);
endfor
if (this.health_change)
    who.health_max = who.health_max + this.health_change;
    if (!silent)
        $mutation:report_change(who, "health max", this.health_change, this.health_change > 0);
    endif
endif

"Something here to who:aat a message about the completion of the augmentation maybe..";

if (is_a(who, $rpg_player))
    this.users = {@this.users, who};
endif

"Maybe update their clone? Depends.";
return 1;
