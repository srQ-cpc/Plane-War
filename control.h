void Pause(){
	SetPos(56,2);
	cout<<"                ";
	SetPos(61,2);
	cout<<"暂停中...";
	char c=_getch();
	while(c!='p')
		c=_getch();
	SetPos(61,2);
	cout<<"         ";
	SetPos(56,2);
	cout<<"P l a n e  W a r";
	return;
}

int exit_game(){
    SetPos(56,2);
	cout<<"                ";
	SetPos(56,2);
	cout<<"确定退出游戏？Y/N";
	char c=_getch();
	while((c!='y')&&(c!='n'))
		c=_getch();
	if (c == 'y') return 1;
	else {
	     SetPos(56,2);
	     cout<<"                 ";
	     SetPos(56,2);
	     cout<<"P l a n e  W a r";
	     return 0;
    }
}

int restart(){
    SetPos(56,2);
	cout<<"                ";
	SetPos(56,2);
	cout<<"重新开始游戏？Y/N";
	char c=_getch();
	while((c!='y')&&(c!='n'))
		c=_getch();
	if (c == 'y') return 1;
	else {
	     SetPos(56,2);
	     cout<<"                 ";
	     SetPos(56,2);
	     cout<<"P l a n e  W a r";
	     return 0;
    }
}
     

void init_game(){
    system("cls");
    HideCursor();
    game_status = START;
    score = 0;
    p_hp = 100; 
    process = 0;
    boss = false; 
    return;
}

void print_score(){
     SetPos(58, 6);
	 cout << score;
}

void print_hp(){
	 SetPos(69, 6);
     cout << "     ";
     SetPos(69, 6);
	 cout << p_hp << " %";
}

void print_process(){
	 SetPos(71, 22);
     cout << "     ";
     SetPos(71, 22);
	 cout << process << " %";
}

int GameOver(){
     system("cls");				
	COORD p1={28,9};
	COORD p2={53,15};
	drawFrame(p1, p2, '=', '|');
	SetPos(32,11);
	string str=" G a m e O v e r !";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(80);
		cout<<str[i];
	}
	Sleep(1000);
	SetPos(31, 13);
	cout<<"     得分："<<score;
	SetPos(30, 16);
	Sleep(1000);
	cout<<"继续？ 是（Y）| 否（N）";
	char c=_getch();
	while((c!='y')&&(c!='n'))
		c=_getch();
	if (c == 'y') return 1;
	else return 0;
}

int GameSuc(){
    Sleep(2000);
     system("cls");				
	COORD p1={28,7};
	COORD p2={53,15};
	drawFrame(p1, p2, '=', '|');
	SetPos(32,9);
	string str=" Congratulation !";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(80);
		cout<<str[i];
	}
	Sleep(1000);
	SetPos(31, 11);
	cout<<"   通关奖励："<< 3000 + p_hp * (130 - init_rank);
	SetPos(31, 13);
	cout<<"     得分："<<score + 3000 + p_hp * (130 - init_rank);
	SetPos(30, 16);
	Sleep(1000);
	cout<<"继续？ 是（Y）| 否（N）";
	char c=_getch();
	while((c!='y')&&(c!='n'))
		c=_getch();
	if (c == 'y') return 1;
	else return 0;
}


void PlayGame(){
     init_game();
     bool f = drawMenu(); 
     drawPlaying(f);
     init_plane();
     init_bullet();
     e_init_bullet();
     b_init_bullet();
     init_enemy();
     int flag_bullet = 0; 
     int e_flag_bullet = 0; 
     int b_flag_bullet = 0; 
     int flag_enemy = 0; 
     game_status = PLAY;    
     while((game_status != OVER)&&(game_status != SUC)){
        Sleep(8);
		if(_kbhit())
		{
			char x = _getch();
			if ('a' == x || 's' == x || 'd' == x || 'w' == x)
			{
				move_plane(x);
				if (boss == false){
                         judge_plane();
				         if (game_status == OVER) break;
				         e_judge();
				         if (game_status == OVER) break;
                }
                else {
                    b_judge();
                    if (game_status == OVER) break;
                } 
				print_hp();
			}			
			else if ('p' == x)
				Pause();
			else if( 'k' == x)
				shoot();
			else if( 'e' == x){
				if (exit_game() == 1)
                return;
			}
			else if ('r' == x){
                 if (restart() == 1){
                     PlayGame();
                     return;
                 }
            }     
				
		}
		if( flag_bullet == 0 )
		{
			clear_bullet();
			move_bullet();
			if (boss == true) {
                     judge_boss();
			         if (game_status == SUC) break;
            }
			draw_bullet();
			if (boss == false){
                     judge_enemy();
                     print_score();
            }
		}			
		flag_bullet++;
		if( flag_bullet == 5 )
			flag_bullet = 0;
			
        
        if (boss == false){
                 	
		/* 处理敌人 */
		if( 0 == flag_enemy )
		{
			draw_enemy_to_null();
			enemy_move();
			if (game_status == OVER) break;
            if (process < 100) new_enemy();			
			draw_enemy();
			judge_enemy();
			judge_plane();
			if (game_status == OVER) break;
			print_score();
			print_hp();
			print_process();
		}
		
		rank = init_rank - process/3;
		
		flag_enemy++;
		if( flag_enemy >= rank )
			flag_enemy = 0;
		
        /* 处理敌人子弹 */	
		if( e_flag_bullet == 0 )
		{
			e_clear_bullet();
			e_move_bullet();
			e_shoot();
			e_judge();
			if (game_status == OVER) break;
			e_draw_bullet();
			print_hp();
		}			
		e_flag_bullet++;
		if( e_flag_bullet == init_rank/5 )
			e_flag_bullet = 0;
		
        if ((process == 100) && (enemy_end() == true)&&(bullet_end() == true)){
            boss = true;
            SetPos(71, 22);
            cout << "     ";
            SetPos(71, 22);
	        cout << "Boss";
            drawboss();
        }
        
        }
        else {
        
        /* 处理boss子弹 */	     
        if( b_flag_bullet == 0 )
		{
			b_clear_bullet();
			b_move_bullet();
			b_shoot();
			b_judge();
			if (game_status == OVER) break;
			b_draw_bullet();
			print_hp();
		}			
		b_flag_bullet++;
		if( b_flag_bullet == init_rank/5 )
			b_flag_bullet = 0;
			
			
        }
             
           	
		
    }
    if (game_status == OVER) 
       if (GameOver() == 1){
           PlayGame();
           return;
       }
       
    if (game_status == SUC) 
       if (GameSuc() == 1){
           PlayGame();
           return;
       }
    return;
}
     
     


