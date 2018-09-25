 "Show the list of inactive employees for the whole corp.";
 displayed = {};
 connected = connected_players();
 player:tell($ansi.yellow + $ansi.bold_on + "Inactive Employees:");
 for rank in ($lu:reverse($lu:slice($lu:sort_alist($hash_utils:to_alist(dobj.levels), 2), 1)))
   display = dobj.ranks[rank];
   reallist = {};
   for inactive in (display)
     if (time() - inactive.last_connect_time >= dobj.takeover_wait && !(inactive in connected))
      reallist = setadd(reallist, inactive);
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
