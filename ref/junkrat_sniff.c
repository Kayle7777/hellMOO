#350820:sniff   any any any
if (player:is_doing(#498353))
  return player:tell("Wait a minute, cowboy, you're already sniffin'.");
endif
len = length(args);
if (len == 1)
  if (thing = $mu:match(args[1], player.contents) && $ou:has_verb(thing, "sniff"))
    thing:sniff(player);
    return;
  endif
endif
if (!len || args[1] != "for")
  player:queue_action(this, {player.location});
  return;
endif
if (!(thing = args[2..$]))
  return player:tell("Sniff for? Sniff for what?");
endif
player:queue_action(#498353, {$lu:implode(thing, " ")});
