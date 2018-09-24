decplaces = dobjstr;
init = "3.";
for i in [1..toint(dobjstr)]
    init = init + "0";
endfor
init = tofloat(init);
for i in [2..this:factorial(toint(decplaces))]
    iter = i*2;
    nilakantha = tostr((4/((iter-2)*(iter-1)*(iter))), ".");
    for n in [1..toint(dobjstr)]
        nilakantha = nilakantha + "0";
    endfor
    nilakantha = tofloat(nilakantha) + 1;
    if (i%2 == 0)
        init = init + (nilakantha-1);
    else
        init = init - (nilakantha-1);
    endif
endfor
player:tell(tostr("Pi to ", dobjstr, " decimal places is ", init,"."));
