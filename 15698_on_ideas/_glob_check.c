{sname, what, reqd, searchitem} = args;
if (sname[1..7] != "generic")
    match_inv = {$mu:match(sname, what)};
else
    chil = children(searchitem);
    for x in (chil)
        if (valid(li = $mu:match(x.name, what)))
            match_inv = {li};
            break;
        endif
    endfor
endif
for x in [1..length(match_inv)]
    if ($ou:has_prop(match_inv[x], "amount"))
        amt = match_inv[x].amount;
        if (amt > reqd)
            amt = reqd;
        endif
    else
        amt = 1;
    endif
    match_inv[x] = {match_inv[x], amt};
endfor
return match_inv;
