nl = args[1];
l = {};
c = {};
for th in (nl)
    for x in [1..length(th[1])]
        l = {@l, tostr(th[1][x].name, x == length(th[1]) ? "" | ", ")};
    endfor
    c = {@c, tostr(th[2].name)};
endfor
return {l, c};
