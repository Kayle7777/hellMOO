{recipe} = args;
recipe = args[1];
ingredient_search_list = recipe.ingredients;
for benchcontents in (this.contents)
    for iter in [1..length(ingredient_search_list)]
        if (valid($mu:match(benchcontents.name, {ingredient_search_list[iter][1]})))
            "This is a match in the bench, for one of the ingredients. ingredient_search_list[iter][2] will be the quantity we need";
            ingredient_search_list[iter][2] = (ingredient_search_list[iter][2] - 1);
            if (ingredient_search_list[iter][2] <= 0)
                ingredient_search_list = setremove(ingredient_search_list, ingredient_search_list[iter]);
            endif
        endif
    endfor
endfor
"Above loop should make ingredient_search_list == the list we need to iterate through with correct required quantities";
getlist = {};
player:tell("current search list: ", toliteral(ingredient_search_list));
alreadyfound = {};
for iter in [1..length(ingredient_search_list)]
    for x in [1..ingredient_search_list[iter][2]]
        "Each item to search for, looks like {#obj, 2}";
        looking = this:_craft_search(ingredient_search_list[iter][1], alreadyfound);
        if (!looking || looking[2] == player)
            looking = 0;
        endif
        if (looking)
            "Adds {LIST {OBJ founditem}, OBJ container} to getlist";
            if (length(looking[1]) > ingredient_search_list[iter][2])
                while (length(looking[1]) > ingredient_search_list[iter][2])
                    looking[1] = setremove(looking[1], looking[1][ingredient_search_list[iter][2]]);
                endwhile
            endif
            getlist = {@getlist, looking};
            for x in (looking[1])
                alreadyfound = {@alreadyfound, x};
            endfor
            ingredient_search_list[iter][2] = ingredient_search_list[iter][2] - length(looking[1]);
        else
            "Couldn't find anything...";
            break;
        endif
    endfor
endfor
"getlist now should equal everything that was found relevant to ingredients";
for get_things in (getlist)
    locname = 0;
    if (get_things[2].name == player.location.name)
        locname = "here";
    endif
    if (length(get_things[1]) > 1)
        for x in (get_things[1])
            player:queue_action($actions.get, {{x}, get_things[2], {}}, 1, tostr("get ", x.name, " from ", locname ? locname | get_things[2].name));
        endfor
    endif
    player:queue_action($actions.get, {get_things[1], get_things[2], {}}, 1, tostr("get ", get_things[1][1].name, " from ", locname ? locname | get_things[2].name));
endfor
return;
