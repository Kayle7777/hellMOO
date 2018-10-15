#23379:mutate   this none none
"TAKE A LOOK AT #23379, THE GENERIC MUTATOR ROOM THING";
"Develop a mutation from this location.";
if (is_a(player, $orphan))
    player:tell("You don't think you're old enough for that yet.");
    return;
endif
if (is_a(player, $roboplayer))
    player:tell("You're a robot. How do you expect to develop a mutation?");
    return;
endif
this.mutation:mutate(player);
