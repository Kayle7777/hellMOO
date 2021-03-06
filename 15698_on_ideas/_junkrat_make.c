{recipe} = args;
ingredient_search_list = recipe.ingredients;
foundcount = 0;
totalcount = 0;
for x in (recipe.ingredients)
    totalcount = totalcount + x[2];
endfor
"Above loop should make ingredient_search_list == the list we need to iterate through with correct required quantities";
player:tell("You begin sniffing around for missing ingredients.");
player.location:aab({player}, tostr(player.name, " begins sniffing around, looking for parts."));
getlist = {};
alreadyfound = {};
for iter in [1..length(ingredient_search_list)]
    ingredient_search_list[iter] = {@ingredient_search_list[iter], ingredient_search_list[iter][2]};
endfor
for iter in [1..length(ingredient_search_list)]
    for qty in [1..ingredient_search_list[iter][2]]
        "Each item to search for, looks like {#obj, 2}";
        if (ingredient_search_list[iter][3] <= 0)
            break;
        endif
        looking = this:_craft_search(ingredient_search_list[iter][1], alreadyfound, ingredient_search_list[iter][3]);
        if (!looking || length(looking[1]) == 0)
            continue;
        elseif (looking[2] == this)
            for x in (looking[1])
                ingredient_search_list[iter][3] = ingredient_search_list[iter][3] - x[2];
                foundcount = foundcount + x[2];
                alreadyfound = {@alreadyfound, x[1]};
            endfor
            continue;
        endif
        for x in (looking[1])
            ingredient_search_list[iter][3] = ingredient_search_list[iter][3] - x[2];
            foundcount = foundcount + x[2];
            alreadyfound = {@alreadyfound, x[1]};
        endfor
        getlist = {@getlist, looking};
    endfor
endfor
if (length(getlist) == 0)
    player:tell("You didn't find anything.");
    return;
endif

telltable = this:junkrat_tell(getlist);
player:tell_lines(telltable);

conf = $cu:yes_or_no(totalcount == foundcount ? "You found all the ingredients, move to workbench?" | "Not all ingredients found, move these items to workbench?");
if (conf)
    putlist = {};
    globlist = {};
    gotlist = {};
    for x in (getlist)
        for y in (x[1])
            for qty in [1..y[2]]
                if (length(player.queue) > 24)
                    while (length(player.queue) > 24)
                        suspend(2);
                    endwhile
                endif
                if (x[2] != player)
                    player:queue_action($actions.get, {{y[1]}, x[2], {}}, 0, tostr("get ", y[1].name, " from ", x[2].name));
                endif
                if (y[2] == 1)
                    gotlist = {@gotlist, y[1]};
                else
                    globlist = {@globlist, {y[1].item, y[2]}};
                endif
            endfor
        endfor
    endfor
    globlist = $lu:remove_duplicates(globlist);
    gotlist = {@gotlist, globlist};
    "This seems redundant, but to handle globs rpg:spawning into players inventories, need to search through inventory after they are already got.";
    tr = 1;
    while (tr)
        suspend(2);
        ll = player.queue;
        for x in [1..length(ll)]
            if (ll[x][1] != #5838)
                ll = setremove(ll, ll[x]);
            endif
        endfor
        if (!ll)
            tr = 0;
        endif
    endwhile
    for x in (gotlist)
        if (typeof(x) == OBJ)
            putlist = {@putlist, x};
        else
            "Now x is the list of globs + quant, looks like {{#obj, 4}, {#obj, 5}}";
            for each in (x)
                for qty in [1..each[2]]
                    "Do this qty many times";
                    for x in (player.contents)
                        "x == each thing in player.contents";
                        if (!$lu:is_one_of(x, putlist) && is_a(x, each[1]))
                            putlist = {@putlist, x};
                        endif
                    endfor
                endfor
            endfor
        endif
    endfor
    for x in (putlist)
        if (length(player.queue) > 24)
            while (length(player.queue) > 24)
                suspend(2);
            endwhile
        endif
        player:queue_action($actions.put, {{x}, this, {}}, 1, tostr("put ", x.name, " in ", this.name));
    endfor
endif

return;
