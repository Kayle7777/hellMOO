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
    player:tell("According to ", recipe:dname(), ", you need ", ing:iname(), " -- and you don't have one on ", this:dname(), ".");
    clist = this.contents;
    searchlist = recipe.ingredients;
    for benchcontents in (this.contents)
        for _ingredient in (searchlist)
            if (valid($mu:match(benchcontents.name, {_ingredient[1]})))
                searchlist = setremove(searchlist, _ingredient);
            endif
        endfor
    endfor
    player:tell(toliteral(searchlist));
    for remaining in (searchlist)
        found = #134933:_check_contents(remaining[1].name, player.location.contents);
        roomtf = found[1] ? player:queue_action() | 0;
        if (!roomtf)
            for containers in (found[2])
                cfound = #134933:_check_contents(remaining[1].name, containers.contents);
                c1tf = cfound[1]? "Put the queue action here, because they found it in the first container layer" | 0;
                if (!c1tf)
                    for containers2 in (cfound[2])
                        c2found = #134933:_check_contents(remaining[1].name, containers2.contents);
                        c2tf = c2found[1]? "Put the queue action here, because they found it in the second container layer" | 0;
                    endfor
                endif
            endfor
        endif
    endfor
    return;
endif
player:queue_action($actions.craft, {recipe, player, this}, 1, "assemble");
