{searchitem, alreadyfound, reqd} = args;
sname = searchitem.name;
"search for searchitem in all containers near player";
"returns LIST {List {OBJ founditem}, OBJ container}";
benchfound = this:_check_contents(sname, this.contents, reqd, searchitem, alreadyfound);
if (benchfound[1])
    return {benchfound[1], this};
endif
pfound = this:_check_contents(sname, player.contents, reqd, searchitem, alreadyfound);

"This is to prevent the whole thing from breaking, if the player has a container";
rpfound = {};
for x in (pfound[2])
    ll = this:_check_contents(sname, x.contents, reqd, searchitem, alreadyfound);
    if (!ll[1])
        continue;
    endif
    rpfound = {@rpfound, x};
endfor
if (pfound[1])
    "If it's directly in the player inventory, no container";
    return {pfound[1], player};
elseif (rpfound)
    "Does player have any containers on hand, if so check them";
    for playercontainers in (rpfound)
        pcfound = this:_check_contents(sname, playercontainers.contents, reqd, searchitem, alreadyfound);
        if (pcfound[1] && playercontainers.open)
            return {pcfound[1], playercontainers};
        endif
    endfor
"Nothing found in player or player containers at this point";
else
    "Now check the room";
    rfound = this:_check_contents(sname, player.location.contents, reqd, searchitem, alreadyfound);
    if (rfound[1])
        "Found directly in the room on the floor";
        return {rfound[1], player.location};
    elseif (rfound[2])
        "Any containers in room";
        for roomcontainers in (rfound[2])
            if (!is_a(roomcontainers, $container))
                continue;
            endif
            rcfound = this:_check_contents(sname, roomcontainers.contents, reqd, searchitem, alreadyfound);
            if (rcfound[1] && roomcontainers.open)
                return {rcfound[1], roomcontainers};
            endif
        endfor
    endif
    "Nothing found.";
    return 0;
endif
