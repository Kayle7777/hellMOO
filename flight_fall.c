@list $mutations.flight:fall
#85048:fall   none none none
"Stop flying and fall to the ground.";
room = player:room();
if (!(player.posture in {"reclining", "sitting"}))
  if (is_a(room, #761))
    if (room:is_falling(player))
      player:tell("You're already falling!");
      return;
    endif
    player:aat(player:dnamec() + " leans back and starts to fall.");
    player:room():_fall(player, player.altitude);
  elseif ($ou:has_verb(room, "_drown"))
    if (is_a(room, #1034))
      player:aat(player:dname() + " leans back and slaps against the water.");
    elseif (is_a(room, #1047))
      player:aat(player:dname() + " lays back in the water.");
    endif
    player:set_posture("reclining");
    fork (2)
      $skills.swim:check(player, room:swim_mod()) < 0 && room:_drown(player);
    endfork
  else
    player:aat(player:dnamec() + " crumples to the ground dejectedly.");
    player:take_damage($damages.beating, random(max(player:weight(), 10000) / 10000), player:random_bodypart());
    player:set_posture("reclining");
  endif
else
  player:tell("It wouldn't make sense to do that when you are " + player.posture + ".");
endif
