{getlist} = args;

header_colors = $ansi.bg_blue;
headers = {"What", "Where"};
row_colors = {$ansi.yellow, $ansi.red+$ansi.bold_on};
rows = {};
for x in (getlist)
    for y in (x[1])
        rows = {@rows, {y.name, x[2].name}};
    endfor
endfor
widths = {20, 20};
gettable = $su:make_table(header_colors, headers, row_colors, rows, widths);
return gettable;
