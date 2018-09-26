
{searchitem} = args;
searchitem = args[1];
sname = searchitem.name;
"search for searchitem in all containers near player";
"returns LIST {OBJ founditem, OBJ container}";
pfound = #134933:_check_contents(sname, player.contents);
ptf = pfound[1] ? 1 | 0;
if (ptf)
    return {$mu:match(sname, player.contents), player};
elseif (pfound[2])
    for pcontainers in (pfound[2])
        return {$mu:match(sname, pcontainers.contents), pcontainers};
    endfor
else
    rfound = #134933:_check_contents(sname, player.location.contents);
    roomtf = rfound[1] ? 1 | 0;
    if (roomtf)
        return {$mu:match(sname, here)};
    else
        for containers in (rfound[2])
            cfound = #134933:_check_contents(sname, containers.contents);
            c1tf = cfound[1] ? 1 | 0;
            if (c1tf)
                return {$mu:match(sname, containers)};
            endif
        endfor
    endif
endif
