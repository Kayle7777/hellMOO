
{searchitem} = args;
searchitem = args[1];

pfound = #134933:_check_contents(searchitem.name, player.contents);
ptf = pfound[1] ? 1 | 0;
if (ptf)
    player:tell("Searching self...");
    return player:queue_action($actions.get, {{searchitem}, player});
elseif (pfound[2])
    for pcontainers in (pfound[2])
        player:tell("Searching self containers...");
        return player:queue_action($actions.get, {{searchitem}, pcontainers, 1, tostr("get ", searchitem.name, " from ", pcontainers.name)});
    endfor
else
    rfound = #134933:_check_contents(searchitem.name, player.location.contents);
    roomtf = rfound[1] ? 1 | 0;
    if (roomtf)
        player:tell("Searching room...");
        player:tell(tostr("get ", searchitem.name));
        return player:queue_action($actions.get, {{searchitem}, player.location, 1, tostr("get ", searchitem.name)});
    else
        for containers in (rfound[2])
            cfound = #134933:_check_contents(searchitem.name, containers.contents);
            c1tf = cfound[1] ? 1 | 0;
            if (c1tf)
                player:tell("Searching container1...");
                return player:queue_action($actions.get, {{searchitem}, containers, 1, tostr("get ", searchitem.name, " from ", containers.name)});
            endif
        endfor
    endif
endif
