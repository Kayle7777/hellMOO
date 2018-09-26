
{searchitem} = args;
searchitem = args[1];

pfound = #134933:_check_contents(searchitem.name, player.contents);
ptf = pfound[1] ? 1 | 0;
if (ptf)
    player:tell("Searching self...");
    player:queue_action($actions.get, {{searchitem}, {}}, player);
elseif (pfound[2])
    for pcontainers in (pfound[2])
        player:tell("Searching self containers...");
        player:queue_action($actions.get, {{$mu:match(searchitem.name, pcontainers.contents)}, pcontainers, {}}, 1, tostr("get ", searchitem.name, " from ", pcontainers.name));
        suspend(1);
        player:queue_action($actions.put, {{$mu:match(searchitem.name, player.contents)}, this, {}}, 1, tostr("put ", searchitem.name, " in ", this.name));
    endfor
else
    rfound = #134933:_check_contents(searchitem.name, player.location.contents);
    roomtf = rfound[1] ? 1 | 0;
    if (roomtf)
        player:tell("Searching room...");
        player:tell(tostr("get ", searchitem.name));
        player:queue_action($actions.get, {{$mu:match(searchitem.name, player.contents)}, player.location, {}}, 1, tostr("get ", searchitem.name));
        suspend(1);
        player:queue_action($actions.put, {{$mu:match(searchitem.name, player.contents)}, this, {}}, 1, tostr("put ", searchitem.name, " in ", this.name));
    else
        for containers in (rfound[2])
            cfound = #134933:_check_contents(searchitem.name, containers.contents);
            c1tf = cfound[1] ? 1 | 0;
            if (c1tf)
                player:tell("Searching container1...");
                player:queue_action($actions.get, {{$mu:match(searchitem.name, containers.contents)}, containers, {}}, 1, tostr("get ", searchitem.name, " from ", containers.name));
                suspend(1);
                player:queue_action($actions.put, {{$mu:match(searchitem.name, player.contents)}, this, {}}, 1, tostr("put ", searchitem.name, " in ", this.name));
            endif
        endfor
    endif
endif
