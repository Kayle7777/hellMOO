who = args[1];
who:tell($ansi.cyan, "Help on the '", $ansi.bold_on, $su:capitalize(this.name), $ansi.bold_off, "' mutation:");
who:tell("----------------------------------");
who:tell_lines(this:description());
for x in (this.skill_mods)
    who:tell(" * ", $su:left(x[1].name + ":", 20), $su:right(tostr(x[2]), 2));
endfor
who:tell("");
if (this.requires)
    who:tell($ansi.bold_on, "Requires: ");
    for x in (this.requires)
        who:tell($ansi.bold_on, " * ", $ansi.bold_off, typeof(x) == LIST ? $su:english_list($lu:map_verb(x, "name"), "", " or ") | x:name());
    endfor
endif
incom = this.incompatible_with;
for x in ($ou:leaves($mutation))
    if (this in x.incompatible_with)
        incom = setadd(incom, x);
    endif
endfor
if (incom)
    who:tell($ansi.bold_on, "Incompatible with: ", $ansi.bold_off, $su:english_list($lu:map_prop(incom, "name")));
endif
who:tell($ansi.reset);
