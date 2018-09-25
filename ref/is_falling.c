#761:is_falling   this none this
{who} = args;
for task in (queued_tasks())
  {id, start, ticks, clock_id, prog, verb_loc, verb_name, line_num, verb_this} = task;
  if (verb_name == "_fall" && verb_this == here && who.location == verb_this)
    flight_task = id;
  endif
endfor
