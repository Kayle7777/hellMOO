#109:show_score_full   this none this
{?oneskill = #-1, ?command = "sc"} = args;
player:tell("");
i = {};
command = command[1..2];
if (command != "sk")
    if (!valid(oneskill))
        this:show_score_stats();
        player:tell("");
        this:tell_implants();
    if (is_a(this, $player) && !is_a(this, $orphan))
        this:show_score_mutations();
        player:tell("");
    endif
    if (is_a(this, $rpg_player))
        this:show_xp();
        player:tell("");
    endif
    endif
endif
if (command == "ss")
    return;
endif
player:tell(tostr($ansi.underline_on, $ansi.bold_on, $ansi.bg_blue, $ansi.white, "Skill Raw    +   + Total Depends Improve ", $ansi.reset, "   "));
weapon_skill = this:weapon().skill;
if (valid(oneskill))
    all_skills = {oneskill};
else
    all_skills = {$skills.dodge};
    all_skills = setadd(all_skills, weapon_skill);
    all_skills = {@all_skills, @setremove(setremove($ou:leaves_suspended($skill), $skills.dodge), weapon_skill)};
endif
if (is_a(this, $player))
    focus_skills = this.focus_skills;
elseif (is_a(this, $clone) && is_a(this.player, $player))
    focus_skills = this.player.focus_skills;
else
    focus_skills = {};
endif
skills = {};
skip_count = 0;
skip_skills = {$skills.dodge, weapon_skill};
shortskills = player:check_pref("shortskills");
for skill in (all_skills)
    yield;
    if (!valid(oneskill) && is_a(skill, $stat))
        continue;
    endif
    raw = this.("_skill_" + skill.name)[1];
    ip = this.("_skill_" + skill.name)[2];
    mod = this:skill_modifier_for(skill);
    if (!valid(oneskill))
        if (!raw && !ip && !mod)
            continue;
        endif
    endif
    yield;
    total = skill:total(this);
    if (valid(oneskill) || !shortskills || total > 8)
        skills = listappend(skills, {skill, skill:name(), raw, ip, mod, total});
    endif
    if (skill in skip_skills)
        skip_count = skip_count + 1;
    endif
endfor
if (skip_count)
    prefix_skills = skills[1..min(skip_count, $)];
    prefix_skills = $lu:sort_alist(prefix_skills, 6);
    prefix_skills = $lu:reverse(prefix_skills);
    skills = skills[skip_count + 1..$];
endif
skills = $lu:sort_alist(skills, 6);
skills = $lu:reverse(skills);
if (skip_count)
    skills = {@prefix_skills, @skills};
endif
lines = {};
for skill in (skills)
    skill = skill[1];
    name = skill[2];
    raw = skill[3];
    ip = skill[4];
    mod = skill[5];
    total = skill[6];
    deps = "";
    for dep in (skill.depends_on)
        deps = tostr(deps, ",", dep.abbrev);
    endfor
    if (deps)
        deps = deps[2..$];
    endif
    if (skill in focus_skills)
        line = tostr($ansi.bold_on, $su:left(name, 11), $ansi.reset);
    else
        line = $su:left(name, 11);
    endif
    if (raw < 0 && ip > 0)
        raw = raw + 1;
        ip = 100 - ip;
        if (raw == 0)
            raw = "-0";
        endif
    endif
    raw = tostr(raw);
    ip = tostr(ip);
    if (length(ip) < 2)
        ip = "0" + ip;
    endif
    lcost = skill:learn_cost_for(this);
    if (toint(raw) < 15)
        icost = $su:right(tostr(lcost, "xp "), -8);
    else
        icost = $su:right("  ", -8);
    endif
    line = tostr(line, $ansi.bold_on, $su:right(raw, -2), $ansi.reset, ".", $su:left(ip, -3));
    rawitem = 0;
    totitem = 0;
    if (skill.depends_on)
        for dep in (skill.depends_on)
            rawitem = rawitem + dep:raw(this);
            totitem = totitem + dep:total(this);
        endfor
        $cu:sin(0);
        rawitem = rawitem / length(skill.depends_on);
        totitem = totitem / length(skill.depends_on);
    endif
    rawtot = totitem - rawitem;
    mod = this:skill_modifier_for(skill) + rawtot;
    if (is_a(this, #132))
        mutmod = this:mutation_modifier_for(skill);
        mod = mod - mutmod;
    endif
    if (mod > 0)
        line = tostr(line, $ansi.bold_on, $ansi.green, $su:right(tostr("+", mod), -3), " ", $ansi.reset);
    elseif (mod < 0)
        line = tostr(line, $ansi.bold_on, $ansi.red, $su:right(tostr(mod), -3), " ", $ansi.reset);
    else
        line = tostr(line, $su:space(4));
    endif
    if (is_a(this, #132))
        if (mutmod > 0)
            line = tostr(line, $ansi.bold_on, $ansi.purple, $su:right(tostr("+", mutmod), -3), " ", $ansi.reset);
        elseif (mutmod < 0)
            line = tostr(line, $ansi.bold_on, $ansi.red, $su:right(tostr(mutmod), -3), " ", $ansi.reset);
        else
            line = tostr(line, $su:space(4));
        endif
    else
        line = tostr(line, $su:space(4));
    endif
    if (total >= 0)
        line = tostr(line, $ansi.bold_on, "[", $ansi.cyan, $su:right(tostr(total), 2), $ansi.white, "] ", $ansi.reset);
    else
        line = tostr(line, $ansi.bold_on, "[", $ansi.red, $su:right(tostr(total), 2), $ansi.white,"] ", $ansi.reset);
    endif
    if (skill in focus_skills)
        line = tostr(line, $ansi.bold_on, $ansi.yellow, $su:left(deps, 7), $ansi.reset, " ");
    else
        line = tostr(line, $ansi.yellow, $su:left(deps, 7), $ansi.reset, " ");
    endif
    if (is_a(this, $rpg_player) && lcost <= this.xp)
        icost = tostr($ansi.bold_on, $ansi.green, icost, $ansi.reset);
    endif
    line = tostr(line, icost);
    ln = skill:level_desc_for(this);
    if (skill in focus_skills)
        line = tostr(line, $ansi.bold_on, $ansi.yellow, $su:left(ln, -33), $ansi.reset);
    else
        line = tostr(line, $ansi.yellow, $su:left(ln, -33), $ansi.reset);
    endif
    lines = listappend(lines, line);
    yield;
endfor
player:tell_lines(lines);
if (is_player(this) && !this.description)
  player:tell("You think you'd be a lot cooler if you had a description.  (@describe me as \"A guy who blah blah blah...\")");
endif
