{needle, haystack} = args;
matches = {};
containers = {};
for x in (haystack)
    if (ticks_left() < 1000)
        suspend(0);
    endif
    found = $mu:match(needle, {x});
    if (is_a(found, #118324) || is_a(found, $dispenser))
        continue;
    endif
    if (valid(found))
        matches = {@matches, found};
    endif
    if (x.contents && !is_a(x, $room) && !is_a(x, $player) && !is_a(x, #118324) && !is_a(x, $dispenser))
        containers = {@containers, x};
    endif
endfor
return {matches ? matches | {}, containers};
