
{searchitem} = args;
searchitem = args[1];

pfound = #134933:_check_contents(searchitem.name, player.contents);
ptf = pfound[1] ? 1 | 0;
if (ptf)
    player:tell("Searching self...");
    player:queue_action($actions.get, {{searchitem}, player});
elseif (pfound[2])
    for pcontainers in (pfound[2])
        player:tell("Searching self containers...");
        player:queue_action($actions.get, {{searchitem}, pcontainers, 1, tostr("get ", searchitem, " from ", pcontainers)});
    endfor
else
    rfound = #134933:_check_contents(searchitem.name, player.location.contents);
    roomtf = rfound[1] ? 1 | 0;
    if (roomtf)
        player:tell("Searching room...");
        player:queue_action($actions.get, {{searchitem}, player.location, 1, tostr("get ", searchitem)});
    else
        for containers in (rfound[2])
            cfound = #134933:_check_contents(searchitem.name, containers.contents);
            c1tf = cfound[1] ? 1 | 0;
            if (c1tf)
                player:tell("Searching container1...");
                player:queue_action($actions.get, {{searchitem}, containers, 1, tostr("get ", searchitem, " from ", containers)});
            else
                for containers2 in (cfound[2])
                    c2found = #134933:_check_contents(searchitem.name, containers2.contents);
                    c2tf = c2found[1] ? 1 | 0;
                    if (c2tf)
                        player:tell("Searching container2...");
                        player:queue_action($actions.get, {{searchitem}, containers2, 1, tostr("get ", searchitem, " from ", containers2)});
                    endif
                endfor
            endif
        endfor
    endif
endif
