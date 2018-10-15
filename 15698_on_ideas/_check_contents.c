{sname, what, reqd, searchitem, alreadyfound} = args;
matches = {};
containers = {};
what = $lu:setremove_all_list(what, alreadyfound);
for x in (what)
    if (ticks_left() < 1000)
        suspend(0);
    endif
    isfound = $ou:isa(x,searchitem) == valid(x) && (searchitem==x || searchitem in $ou:ancestors(x));
    found = isfound ? x | $nothing;
    if (is_a(found, #118324) || is_a(found, $dispenser) || is_a(found, $liquid))
        continue;
    endif
    "Something here to handle liquids";
    if (valid(found))
        matches = {@matches, found};
    endif
    if (x.contents && !is_a(x, $room) && !is_a(x, $player) && !is_a(x, #118324) && !is_a(x, $dispenser))
        containers = {@containers, x};
    endif
endfor

if (length(sname) >= 7 && sname[1..7] == "generic")
    for y in (children(searchitem))
        found = $mu:match(y.name, what);
        if (valid(found))
            matches = {@matches, found};
        endif
    endfor
endif

if (length(matches) > reqd)
    matches = matches[1..reqd];
endif

for x in [1..length(matches)]
    if ($ou:has_prop(matches[x], "amount"))
        amt = matches[x].amount;
        if (amt > reqd)
            amt = reqd;
        endif
    else
        amt = 1;
    endif
    matches[x] = {matches[x], amt};
endfor


return {matches ? matches | {}, containers};
