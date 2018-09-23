"Show the list of inactive employees for the whole corp.";
"8075 on *id";
ia = verb == "@bizinactives"?1|0;
vcall = ia?"Inactive Employees:"|"Active Employees:";
displayed = {};
connected = connected_players();
player:tell($ansi.yellow + $ansi.bold_on + vcall);
for rank in ($lu:reverse($lu:slice($lu:sort_alist($hash_utils:to_alist(dobj.levels), 2), 1)))
    display = dobj.ranks[rank];
    reallist = {};
    for _player in (display)
        checker = ia?(time() - _player.last_connect_time >= dobj.takeover_wait) && !(_player in connected)| (_player in connected) || (time() - _player.last_connect_time < dobj.takeover_wait);
        if (checker)
            reallist = setadd(reallist, _player);
        endif
    endfor
    reallist = $set_utils:difference(reallist, displayed);
    displayed = {@displayed, @display};
    if (!reallist)
        reallist = "None";
        long = "";
    else
        long = tostr(length(reallist)) + $ansi.bold_off + " -- ";
        reallist = $su:english_list($lu:sort_suspended(1, $lu:map_prop(reallist, "name")));
    endif
    dobj:tell_info(player, $su:capitalize(rank), $ansi.yellow, $ansi.bold_on, long, reallist, $ansi.reset);
endfor
