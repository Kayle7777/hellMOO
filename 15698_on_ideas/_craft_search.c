{searchitem, alreadyfound, reqd} = args;
sname = searchitem.name;
"search for searchitem in all containers near player";
"returns LIST {List {OBJ founditem}, OBJ container}";
benchcontents = $lu:setremove_all_list(this.contents, alreadyfound);
benchfound = this:_check_contents(sname, benchcontents, searchitem);
if (benchfound[1])
    return {this:_glob_check(sname, benchcontents, reqd, searchitem), this};
endif
playerinventory = $lu:setremove_all_list(player.contents, alreadyfound);
pfound = this:_check_contents(sname, playerinventory, searchitem);

"This is to prevent the whole thing from breaking, if the player has a container";
rpfound = {};
for x in (pfound[2])
    rlcontents = $lu:setremove_all_list(x.contents, alreadyfound);
    ll = this:_check_contents(sname, rlcontents, searchitem);
    if (!ll[1])
        continue;
    endif
    rpfound = {@rpfound, x};
endfor
if (pfound[1])
    "If it's directly in the player inventory, no container";
    return {this:_glob_check(sname, playerinventory, reqd, searchitem), player};
elseif (rpfound)
    "Does player have any containers on hand, if so check them";
    for playercontainers in (rpfound)
        pccontainers = $lu:setremove_all_list(playercontainers.contents, alreadyfound);
        pcfound = this:_check_contents(sname, pccontainers, searchitem);
        if (pcfound[1] && playerontainers.open)
            return {this:_glob_check(sname, pccontainers, reqd, searchitem), playercontainers};
        endif
    endfor
"Nothing found in player or player containers at this point";
else
    "Now check the room";
    rccontaining = $lu:setremove_all_list(player.location.contents, alreadyfound);
    rfound = this:_check_contents(sname, rccontaining, searchitem);
    if (rfound[1])
        "Found directly in the room on the floor";
        return {this:_glob_check(sname, rccontaining, reqd, searchitem), player.location};
    elseif (rfound[2])
        "Any containers in room";
        rfound[2] = setremove(rfound[2], this);
        for roomcontainers in (rfound[2])
            if (!is_a(roomcontainers, $container))
                continue;
            endif
            roomconcurrent = $lu:setremove_all_list(roomcontainers.contents, alreadyfound);
            rcfound = this:_check_contents(sname, roomconcurrent, searchitem);
            if (rcfound[1] && roomcontainers.open)
                return {this:_glob_check(sname, roomconcurrent, reqd, searchitem), roomcontainers};
            endif
        endfor
    endif
    "Nothing found.";
    return 0;
endif
