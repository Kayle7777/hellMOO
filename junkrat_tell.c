{?getlist = {}, ?putlist = {}} = args;

putlines = this:_list_comp(putlist);
getlines = this:_list_comp(getlist);

widths = {20, 40};
header_colors = {$ansi.bg_blue};
headers = {"What", "Where"};
row_colors = {$ansi.yellow, $ansi.red+$ansi.bold_on};

puttable = $su:make_table(header_colors, headers, row_colors, putlines, widths);
gettable = $su:make_table(header_colors, headers, row_colors, getlines, widths);

return {gettable, puttable};
