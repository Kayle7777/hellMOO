if (!toint(dobjstr))
    player:tell("You can only pass integer arguments.");
    return;
endif
intfact = toint(dobjstr);
retnumber = intfact;
for n in [1..intfact]
    subfact = n!=intfact ? intfact - n | 1;
    retnumber = retnumber * subfact;
endfor
player:tell(tostr("The factorial of ", dobjstr, " is ", retnumber));
