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
    if (player:room():is_falling(me))
        player.flight_ncatch = 0;
        player:tell("You focus your mind and stop your fall.");
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
