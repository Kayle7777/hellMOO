incom = this.incompatible_with;
allmutes = $ou:leaves($mutation);
for x in (allmutes)
    if (this in x.incompatible_with)
        incom = setadd(incom, x);
    endif
endfor
last_incom = {};
while (last_incom != incom)
    last_incom = incom;
    for x in (allmutes)
        for y in (incom)
            if (y in x.requires)
                incom = setadd(incom, x);
            endif
        endfor
    endfor
endwhile
for x in (this.requires)
    if (typeof(x) != LIST)
        incom = {@incom, @x:incompatible_with()};
    endif
endfor
return incom;
