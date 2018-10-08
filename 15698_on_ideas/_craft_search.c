{searchitem, alreadyfound, reqd} = args;
sname = searchitem.name;
"search for searchitem in all containers near player";
"returns LIST {List {OBJ founditem}, OBJ container}";
benchcontents = $lu:setremove_all_list(this.contents, alreadyfound);
benchfound = this:_check_contents(sname, benchcontents, reqd, searchitem);
if (benchfound[1])
    return {benchfound[1], this};
endif
playerinventory = $lu:setremove_all_list(player.contents, alreadyfound);
pfound = this:_check_contents(sname, playerinventory, reqd, searchitem);

"This is to prevent the whole thing from breaking, if the player has a container";
rpfound = {};
for x in (pfound[2])
    rlcontents = $lu:setremove_all_list(x.contents, alreadyfound);
    ll = this:_check_contents(sname, rlcontents, reqd, searchitem);
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
        pccontainers = $lu:setremove_all_list(playercontainers.contents, alreadyfound);
        pcfound = this:_check_contents(sname, pccontainers, reqd, searchitem);
        if (pcfound[1] && playercontainers.open)
            return {pcfound[1], playercontainers};
        endif
    endfor
"Nothing found in player or player containers at this point";
else
    "Now check the room";
    rccontaining = $lu:setremove_all_list(player.location.contents, alreadyfound);
    rfound = this:_check_contents(sname, rccontaining, reqd, searchitem);
    if (rfound[1])
        "Found directly in the room on the floor";
        return {rfound[1], player.location};
    elseif (rfound[2])
        "Any containers in room";
        rfound[2] = setremove(rfound[2], this);
        for roomcontainers in (rfound[2])
            if (!is_a(roomcontainers, $container))
                continue;
            endif
            roomconcurrent = $lu:setremove_all_list(roomcontainers.contents, alreadyfound);
            rcfound = this:_check_contents(sname, roomconcurrent, reqd, searchitem);
            if (rcfound[1] && roomcontainers.open)
                return {rcfound[1], roomcontainers};
            endif
        endfor
    endif
    "Nothing found.";
    return 0;
endif
