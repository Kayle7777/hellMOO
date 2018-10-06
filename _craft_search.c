{searchitem, alreadyfound} = args;
searchitem = args[1];
alreadyfound = args[2];
sname = searchitem.name;
"search for searchitem in all containers near player";
"returns LIST {List {OBJ founditem}, OBJ container}";
pfound = this:_check_contents(sname, player.contents);
if (pfound[1])
    playerinventory = $lu:setremove_all_list(player.contents, alreadyfound);
    "If it's directly in the player inventory, no container";
    return {this:_glob_check(sname, playerinventory), player};
elseif (pfound[2])
    "Does player have any containers on hand, if so check them";
    for pcontainers in (pfound[2])
        pccontainers = $lu:setremove_all_list(pcontainers, alreadyfound);
        pcfound = this:_check_contents(sname, pcccontainers);
        if (pcfound[1])
            return {this:_glob_check(sname, pccontainers), pcontainers};
        endif
    endfor
"Nothing found in player or player containers at this point";
else
    "Now check the room";
    rccontaining = $lu:setremove_all_list(player.location.contents, alreadyfound);
    rfound = this:_check_contents(sname, rccontaining);
    if (rfound[1])
        "Found directly in the room on the floor";
        return {this:_glob_check(sname, rccontaining), player.location};
    elseif (rfound[2])
        "Any containers in room";
        for roomcontainers in (rfound[2])
            if (!is_a(roomcontainers, $container))
                continue;
            endif
            roomconcurrent = $lu:setremove_all_list(roomcontainers.contents, alreadyfound);
            rcfound = this:_check_contents(sname, roomconcurrent);
            if (rcfound[1])
                return {this:_glob_check(sname, roomconcurrent), roomcontainers};
            endif
        endfor
    endif
    "Nothing found.";
    return 0;
endif
