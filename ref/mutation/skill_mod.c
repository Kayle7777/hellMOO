for x in (this.skill_mods)
    if (x[1] == args[1])
        return x[2];
    endif
endfor
return 0;
