this.lastnumber = toint(args[1]);
prime = 1;
for n in [2..this.lastnumber - 1]
  if ((this.lastnumber % n) == 0)
    prime = 0;
    break;
  endif
endfor
return prime;
