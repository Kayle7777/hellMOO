who = args[1];
if (player == who)
    return this:_look_self_msg(@args);
else
    notice = this.notice_difficulty[1];
    if (this.notice_difficulty[2])
        notice = notice + this.notice_difficulty[2];
    endif
    if (is_player(player) && $skills.senses:check(player, notice))
        return this:_look_self_msg(@args);
    elseif (!is_player(player))
        return this:_look_self_msg(@args);
    endif
endif
