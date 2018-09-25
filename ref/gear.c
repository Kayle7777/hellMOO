if (player:check_pref("blindgear"))
  this:blind_gear(args);
  return;
endif
if (!player.programmer || !dobjstr)
  who = this;
else
  who = valid(dobj) ? dobj | $su:match_player(dobjstr);
  if (!valid(who) || !is_a(who, $creature))
    player:tell("gear who?");
    return;
  endif
endif
player:tell($ansi.header + "Bodypart  Armor                     Beat  Slash Stab  Bullt Burn
Elec  Acid" + $ansi.reset);
dtypes = {#268, #277, #278, #279, #280, #281, #282};
for part in (who.body_parts)
  data = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  armors = who:wearing_on(part);
  anew = {};
  for x in (armors)
    if (x.armor)
      anew = setadd(anew, x);
    endif
  endfor
  armors = anew;
  for armor in ({@armors, who})
    deter = is_a(armor, $clothing) ? (armor.health_max - armor.health) / 3 | 0;
    for aval in (armor.armor)
      i = 1;
      while (i <= length(dtypes))
        if (is_a(dtypes[i], aval[1]))
          data[i][1] = data[i][1] + max(0, aval[2] - deter);
          data[i][2] = data[i][2] + max(0, aval[3] - deter);
        endif
        i = i + 1;
      endwhile
    endfor
  endfor
  s = $su:left(part.name, -9) + " ";
  astr = "";
  first = 1;
  for x in (armors)
    astr = astr + (first ? "" | "+") + x.name;
    first = 0;
  endfor
  s = s + $ansi.yellow + $su:left(astr, -25) + $ansi.reset + " ";
  for x in (data)
    if (x[1] || x[2])
      s = s + $ansi.bold_on + $su:left(tostr(x[1]) + "-" + tostr(x[2]), -5) + $ansi.reset + "
";
    else
      s = s + "      ";
    endif
  endfor
  player:tell(s);
endfor
dpen = 0.0;
for x in (who.wearing)
  dpen = dpen + x.dodge_mod;
endfor
dpen = tofloat(toint(dpen * 10.0) / 10);
player:tell($ansi.bold_on, "Total dodge penalty from armor: ", $ansi.blue, dpen, $ansi.reset);
player:tell($ansi.header + "Weapon                  Raw   Hit Spd Par DType base  effec cr%
eDPS Cond  " + $ansi.reset);
oweap = setremove(who:occupants($weapon), myweap = who:weapon());
weapons = {myweap, @oweap};
if (!(who.unarmed_weapon in weapons))
  if (typeof(who.unarmed_weapon) == LIST)
    weapons = {@weapons, @who.unarmed_weapon};
  else
    weapons = {@weapons, who.unarmed_weapon};
  endif
endif
for w in (weapons)
  hit = w:tohit(who);
  dmg = w:damage();
  raw = tostr(w.min_skill) + "-" + tostr(ceil = w:grind_ceiling());
  if (ceil > 8)
    raw = tostr(w.min_skill) + "-*";
  endif
  praw = w.skill:raw(who);
  if (praw < w.min_skill)
    rawcolor = $ansi.red;
  elseif (praw > ceil)
    rawcolor = $ansi.yellow;
  else
    rawcolor = $ansi.green;
  endif
  edmg = w:damage(who, (hit - 10) / 2);
  scaling = w:calculate_scaling(who, (hit - 10) / 2);
  first = 1;
  dc = 0;
  dps = 0.0;
  for d in (dmg)
    dc = dc + 1;
    ed = edmg[dc];
    if (first)
      name = w.long_name_msg || w.name;
      if (w == myweap || w in who.wielding)
        s = $ansi.bold_on + $ansi.yellow + $su:left(name, -23) + $ansi.reset + " ";
      else
        s = $ansi.yellow + $su:left(name, -23) + $ansi.reset + " ";
      endif
      s = s + rawcolor + $su:left(raw, -5) + $ansi.reset + " ";
      if (w in who.wielding && length(who:occupants($weapon, "wielding")) > 1)
        hit = hit + $rpg.dual_wield_tohit;
      endif
      s = s + $su:left(tostr(hit), -3) + " ";
      spd = w:speed(who);
      if (w in who.wielding && length(who:occupants($weapon, "wielding")) > 1)
        spd = spd * 2.0;
      endif
      s = s + $su:left(tostr(spd), -3) + " ";
      if (w.parry_class == 999)
        pstr = $ansi.red + "-  " + $ansi.reset;
      else
        pstr = $ansi.green + $su:left($su:space(w.parry_class, "*"), -3) + $ansi.reset;
      endif
      s = s + pstr + " ";
    else
      s = "                                        + ";
    endif
    s = s + $ansi.red + $ansi.bold_on + $su:left(d[1].abbrev, -5) + " " + $ansi.reset;
    s = s + $su:left(tostr(max(d[2], 1)) + "-" + tostr(max(d[3], 1)), -5) + " ";
    s = s + $su:left(tostr(max(ed[2], 1)) + "-" + tostr(max(ed[3], 1)), -5) + " ";
    s = s + $su:right(tostr(ed[4]) + "%", -3) + "  ";
    dps = dps + (tofloat(ed[2]) + tofloat(ed[3] - ed[2]) / 2.0);
    dps = dps * (tofloat(100 + d[4]) / 100.0);
    if (0)
      if (dc == 1 && !is_a(w, $gun))
        s = s + $su:right(tostr(scaling[1]), 4) + " " + $su:right(tostr(scaling[2]), 4) + " ";
      else
        s = s + "          ";
      endif
    endif
    if (dc == length(dmg))
      dps = dps / spd ! ANY => 0.0;
      s = s + $ansi.bold_on + $su:left(tostr(dps), -4) + $ansi.reset;
      healthp = toint(tofloat(w.health) / tofloat(w.health_max) * 100.0);
      healthcolor = $ansi.green;
      if (healthp < 76)
        healthcolor = $ansi.yellow;
      endif
      if (healthp < 26)
        healthcolor = $ansi.red;
      endif
      s = s + " " + $ansi.bold_on + healthcolor + tostr(healthp) + "%" + $ansi.reset;
    endif
    player:tell(s);
    first = 0;
    $cu:sin();
  endfor
  $cu:sin();
endfor
