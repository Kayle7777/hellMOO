{recipe} = args;
recipe = args[1];
ingredient_search_list = recipe.ingredients;
foundcount = 0;
totalcount = 0;
for x in (recipe.ingredients)
    totalcount = totalcount + x[2];
endfor
"Above loop should make ingredient_search_list == the list we need to iterate through with correct required quantities";
getlist = {};
alreadyfound = {};
for iter in [1..length(ingredient_search_list)]
    for qty in [1..ingredient_search_list[iter][2]]
        "Each item to search for, looks like {#obj, 2}";
        looking = this:_craft_search(ingredient_search_list[iter][1], alreadyfound);
        if (!looking || length(looking[1]) == 0)
            continue;
        elseif (looking[2] == this)
            for x in (looking[1])
                foundcount = foundcount + x[2];
                alreadyfound = {@alreadyfound, x[1]};
            endfor
            continue;
        endif
        for x in (looking[1])
            foundcount = foundcount + x[2];
            alreadyfound = {@alreadyfound, x[1]};
        endfor
        getlist = {@getlist, looking};
    endfor
endfor
player:tell("You begin sniffing around for missing ingredients.");
player.location:aab({player}, tostr(player.name, " begins sniffing around, looking for parts."));
waitdot = ".";
for x in [1..random(4)]
    suspend(1);
    player:tell(waitdot);
    waitdot = tostr(waitdot, ".");
endfor
if (length(getlist) == 0)
    player:tell("You didn't find anything.");
return;
endif

telltable = this:junkrat_tell(getlist);
player:tell(foundcount);
player:tell_lines(telltable);

msg = totalcount == foundcount ? "You found all the ingredients, move to workbench?" | "Not all ingredients found, move these items to workbench?";
conf = $cu:yes_or_no(msg);
if (conf)
    for x in (getlist)
        for y in (x[1])
            if (x[2] != player)
                for qty in [1..y[2]]
                    player:queue_action($actions.get, {{y[1]}, x[2], {}}, 1, tostr("get ", y[1].name, " from ", x[2].name));
                endfor
            endif
        endfor
    endfor

putlist = {};

"Due to the way globs work, there needs to be a lot of logic to make the player put the correct things in";
    for x in (putlist)
        for y in (x[1])
            for qty in [1..y[2]]
                player:queue_action($actions.put, {{y[1]}, this, {}}, 1, tostr("put ", y[1].name, " in ", this.name));
            endfor
        endfor
    endfor
endif

return;
