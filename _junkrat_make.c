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
alreadyfound = {};
for iter in [1..length(ingredient_search_list)]
    for qty in [1..ingredient_search_list[iter][2]]
        "Each item to search for, looks like {#obj, 2}";
        looking = this:_craft_search(ingredient_search_list[iter][1], alreadyfound);
        if (length(looking[1]) == 0)
            continue;
        endif
        if (looking[2] == this)
            for x in (looking[1])
                alreadyfound = {@alreadyfound, x};
            endfor
            continue;
        endif
        for x in (looking[1])
            alreadyfound = {@alreadyfound, x};
        endfor
        getlist = {@getlist, looking};
    endfor
endfor
putlist = {};
for x in (getlist)
    if (!x[2] == player)
        putlist = {@putlist, {x[1], player}};
    endif
endfor
player:tell("You begin sniffing around for missing ingredients.");
waitdot = ".";
for x in [1..3]
    suspend(1);
    player:tell(waitdot);
    waitdot = tostr(waitdot, ".");
endfor
telltable = this:junkrat_tell(getlist);
player:tell_lines(telltable);
"getlist now should equal everything that was found relevant to ingredients";
"This is where initial idea about queueing actions immediately would go.";
conf = 0;

return;
