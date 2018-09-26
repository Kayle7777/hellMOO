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
    if ($mu:is_one_of($mutations.junkrat, player.mutations))
        ingredient_search_list = recipe.ingredients;
        for benchcontents in (this.contents)
            for _ingredient in (ingredient_search_list)
                if (valid($mu:match(benchcontents.name, {_ingredient[1]})))
                    ingredient_search_list = setremove(ingredient_search_list, _ingredient);
                endif
            endfor
        endfor
        putlist = {};
        for remaining in (ingredient_search_list)
            howmanyneeded = remaining[2];
            while (howmanyneeded > 0)
                found = this:_craft_search(remaining[1]);
                player:queue_action($actions.get, {{found[1]}, found[2]}, 1, tostr("get " found[1].name, " from ", found[2].name));
                putlist = {@putlist, found[1]}
                howmanyneeded = howmanyneeded -1;
            endwhile
        endfor
    else
        player:tell("According to ", recipe:dname(), ", you need ", ing:iname(), " -- and you don't have one on ", this:dname(), ".");
        return;
    endif
endif
player:queue_action($actions.craft, {recipe, player, this}, 1, "assemble");
