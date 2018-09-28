#498353:_check_contents   this none this
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
  if (x.contents && !is_a(x, $room))
    containers = {@containers, x};
  endif
endfor
return {matches ? matches | {}, containers};
