{who, name, value, increased} = args;
color = increased ? $ansi.green | $ansi.red;
tag = increased ? "increased" | "decreased";
who:systell(tostr(color, $ansi.bold_on, "Your ", name, " ", tag, " by ", value, "!", $ansi.reset));
