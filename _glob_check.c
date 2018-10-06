{sname, what} = args;
match_inv = $mu:match_list(sname, what);
for x in [1..length(match_inv)]
    if ($ou:has_prop(match_inv[x], "amount"))
        amt = match_inv[x].amount;
    else
        amt = 1;
    endif
    match_inv[x] = {match_inv[x], amt};
endfor
return match_inv;
