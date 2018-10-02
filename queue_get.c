for get_things in (getlist)
    put_things = {get_things[1], player};
    putlist = {@putlist, put_things};
    locname = 0;
    if (get_things[2].name == player.location.name)
        locname = "here";
    endif
    if (length(get_things[1]) > 1)
        for x in (get_things[1])
            player:queue_action($actions.get, {{x}, get_things[2], {}}, 1, tostr("get ", x.name, " from ", locname ? locname | get_things[2].name));
        endfor
    endif
    player:queue_action($actions.get, {get_things[1], get_things[2], {}}, 1, tostr("get ", get_things[1][1].name, " from ", locname ? locname | get_things[2].name));
endfor
