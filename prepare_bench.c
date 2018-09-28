"15698 on *id";

"Assemble a recipe indicated by number.";
r = this:all_recipes();
if (!r)
    player:tell("There aren't any recipes in ", this:dname(), ".  You'll have to put one in.");
return;
endif
NUM = tonum(dobjstr);
if (NUM < 1)
    player:tell("You need to give a number.  Try 'make 1 on ", this.name, "'.");
return;

elseif (NUM > length(r))
    player:tell("There are only ", length(r), " recipes in ", this:dname(), ".");
return;
endif

recipe = r[NUM];
if (!this:is_accepted_recipe(recipe))
    player:tell(recipe:dname(), " can't be assembled on ", this:iname(), ".");
return;
endif
if (valid(recipe.needs_bench) && !is_a(this, recipe.needs_bench))
    player:tell("You realize you can't make ", recipe.makes:iname(), " on ", this:iname(), " -- you'd need ", recipe.needs_bench:iname(), ".");
return;
endif
if (is_a(this, recipe.needs_bench))
    "";
else
    if (!is_a(recipe, this.recipe_type))
        player:tell(recipe:dnamec(), " cannot be used on ", this:dname(), ".");
        return;
    endif
endif
ing = recipe:find_ingredients(this);
if (typeof(ing) == OBJ)
    if ($lu:is_one_of($mutations.junkrat, player.mutations))
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
            "Each item to search for, looks like {#obj, 2}";
            looking = this:_craft_search(ingredient_search_list[iter][1], alreadyfound);
            player:tell("Looking:    ", toliteral(looking));
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
                "Couldn't find anything, break out";
                break;
            endif
        endfor
        "getlist now should equal everything that was found relevant to ingredients";
        player:tell(toliteral(getlist));
        for get_things in (getlist)
            "player:queue_action($actions.get, {{get_things[1]}, get_things[2]}, 1, tostr('get things from ', get_things[2].name));";

        endfor
    else
        player:tell("According to ", recipe:dname(), ", you need ", ing:iname(), " -- and you don't have one on ", this:dname(), ".");
        return;
    endif
endif
player:queue_action($actions.craft, {recipe, player, this}, 1, "assemble");
