#85048:fly   none none none
"Launch yourself into the sky.";
if (player.fighting || player:is_fighting())
    return player:tell("You're too busy right now!");

elseif ($drugs.shock:doses_for(player))
    return player:tell("You're in shock!");

elseif ($drugs.broken_leg:doses_for(player))
    player:tell("Augh! Your broken leg twists and crunches under you as you try to leap into the air!");
    return player:take_damage($damages.kinetic, random(10), $bodyparts.leg, player);
endif

if (is_a(player.location, #761))
    if (player:room():is_falling(player))
        "This attempts to find the fly task, code is mostly the same as is_falling";
        "The other solution I found was to add a new property to players. Then add an additional condition to the while loop in _fall to check for it. _fall initially sets it to 1, but if a player types their flight mutation 'fly' again, it would set it to 0. I liked that way better but adding a new property to players isn't ideal I think...";
        for task in (queued_tasks())
          {id, start, ticks, clock_id, prog, verb_loc, verb_name, line_num, verb_this} = task;
          if (verb_name == "_fall" && verb_this == here && player.location == verb_this)
            flight_task = id;
          endif
        endfor
        if (flight_task)
            this:_recover(player, flight_task);
            return player:tell("You attempt to recover");
        endif
    else
        return player:tell("You're already in flight.  Try flying around a bit, or climbing or diving.");
    endif

elseif (is_a(player.location, #1047))
    return player:tell("Try surfacing first.");

elseif (!player.location.outdoor)
    return player:tell("Flying indoors is a bad idea, pal.");

elseif (player.location:sky_room() == #-1)
    return player:tell("There isn't a safe path up here.");

elseif (player:encumbrance() <= -2)
    player:aat(player:dnamec(), " grunts and strains, hopping frantically up and down.");
    player:tell("Hm.  You seem to be weighed down too heavily to take off.");
    return;
endif

player:queue_action(this, {player, "ascend"}, 1, "fly");
