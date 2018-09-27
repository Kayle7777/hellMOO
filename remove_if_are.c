{ifare, inlist} = args;
ifare = args[1];
inlist = args[2];

removelist = $lu:are(ifare, inlist);

for x in (ifare)
    inlist = setremove(inlist, x);
endfor
return inlist;
