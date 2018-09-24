#40:queue_action   this none this
{?action = $action, ?cargs = {}, ?inter = 1, ?cmd = "", ?no_cancel = 0} = args;
if (this.executing && this.executing[1] == $actions.attack && this.executing[3] && !this.queue)
  if (action == $actions.attack && `cargs[1] == this.executing[2][1] ! E_RANGE => 0)
    this.executing[3] = 0;
    this:tell($ansi.cyan, "[ Finishing current attack. ]", $ansi.reset);
    return;
  elseif (this.executing[3])
    this:cancel_current_action();
    pass(@args);
  endif
elseif (this.executing || this.queue && action == $actions.attack)
  pass(@args);
  this.queue[$][3] = 0;
else
  pass(@args);
endif
