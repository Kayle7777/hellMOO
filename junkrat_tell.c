{?getlist = {}, ?putlist = {}} = args;

putlines = this:_list_comp(putlist);
getlines = this:_list_comp(getlist);

widths = {20, 40};
header_color = {$ansi.bg_blue};
headers = {"What", "Where"};

table = $su:make_table(header_colors, headers, row_colors, rows, widths);
