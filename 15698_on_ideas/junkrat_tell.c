{getlist} = args;
header_colors = $ansi.bg_blue;
headers = {"What", "Where", "Amount"};
row_colors = {$ansi.yellow, $ansi.red+$ansi.bold_on, $ansi.red+$ansi.bold_on};
rows = {};
for x in (getlist)
    for y in (x[1])
        rows = {@rows, {y[1].name, x[2].name, tostr(y[2])}};
    endfor
endfor
widths = {20, 26, 6};
gettable = $su:make_table(header_colors, headers, row_colors, rows, widths);
return gettable;
