
{searchitem} = args;
searchitem = args[1];
sname = searchitem.name;
"search for searchitem in all containers near player";
"returns LIST {List {OBJ founditem}, OBJ container}";
pfound = this:_check_contents(sname, player.contents);
if (pfound[1])
    "If it's directly in the player inventory, no container";
    return {$mu:match_list(sname, player.contents), player};
elseif (pfound[2])
    "Does player have any containers on hand, if so check them";
    for pcontainers in (pfound[2])
        pcfound = this:_check_contents(sname, pcontainers);
        if (pcfound[1])
            return {$mu:match_list(sname, pcontainers.contents), pcontainers};
        endif
    endfor
"Nothing found in player or player containers at this point";
else
    "Now check the room";
    rfound = this:_check_contents(sname, player.location.contents);
    if (rfound[1])
        "Found directly in the room on the floor";
        return {$mu:match_list(sname, player.location.contents), here};
    elseif (rfound[2])
        "Any containers in room";
        for roomcontainers in (rfound[2])
            rcfound = this:_check_contents(sname, roomcontainers.contents);
            if (rcfound[1])
                return {$mu:match_list(sname, roomcontainers.contents), roomcontainers};
            endif
        endfor
    endif
    "Nothing found.";
    return 0;
endif
