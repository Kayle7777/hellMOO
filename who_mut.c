{?mut = 0, @strs} = args;
if (!mut)
    return player:tell("You know why this didn't work");
endif
if (strs)
    for x in [1..length(strs)]
        sep = x < length(strs) ? " " | "";
        mut = tostr(mut, " ", strs[x], sep);
    endfor
    player:tell(mut);
endif
for x in ($mutations.contents)
    if (mut == x.name)
        mut = x;
        break;
    endif
endfor
if (typeof(mut) == STR)
    return player:tell("That's not a real mutation name");
endif
players = connected_players();
nonmins = {};
for p in (players)
    if (!is_a(p, $immortal))
        nonmins = {@nonmins, p};
    endif
endfor
ismut = {};
for i in [1..length(nonmins)]
    if ($lu:is_one_of(mut, nonmins[i].mutations))
        ismut = {@ismut, nonmins[i]};
    endif
endfor

if (!ismut)
    return player:tell("No connected players with ", mut.name);
endif
return $whofo:_who(ismut, {}, 1);
