r = "";
if ("mutate" in verbs(this))
    r = tostr(r, $ansi.green, $ansi.bold_on, "m", $ansi.reset);
endif
if ("unmutate" in verbs(this))
    r = tostr(r, $ansi.red, $ansi.bold_on, "u", $ansi.reset);
endif
if ("heartbeat" in verbs(this))
    r = tostr(r, $ansi.cyan, $ansi.bold_on, "h", $ansi.reset);
endif
if (r)
    r = " <" + r + ">";
endif
if (this.ij_category)
    r = tostr(r, " [", this.ij_category, "]");
endif
if ("corpse_meats" in verbs(this))
    r = r + "  corpse meats";
endif
if (!is_clear_property(this, "skill_mods") && this.skill_mods)
    r = r + "  ";
    for x in (this.skill_mods)
        if (x[1].abbrev)
            r = r + x[1].abbrev;
        else
            r = r + x[1].name;
        endif
    r = r + (x[2] > 0 ? "+" | "") + tostr(x[2]) + " ";
    endfor
endif
r = $su:trim(r);
if (r)
    r = pass(@args) + "  " + r;
else
    r = pass(@args);
endif
return r;
