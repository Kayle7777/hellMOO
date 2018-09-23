start = toint(args[1]);
stop = toint(args[2]);

if (start>stop || start <=0 || stop <=0)
    player:tell("Arguments must both be positive, and argument 1 must be less than argument 2.");
    return;
endif

retlist = {};
for num in [start..stop]
    if (this:prime(num))
        retlist = {@retlist, num};
    endif
endfor
player:tell(toliteral(retlist));
