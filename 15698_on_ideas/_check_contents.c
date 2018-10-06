{needle, haystack} = args;
matches = {};
containers = {};
for x in (haystack)
  if (ticks_left() < 1000)
    suspend(0);
  endif
  if (valid(found = $mu:match(needle, {x})))
    matches = {@matches, found};
  endif
  if (x.contents && !is_a(x, $room) && !is_a(x, $player))
    containers = {@containers, x};
  endif
endfor
return {matches ? matches | {}, containers};
