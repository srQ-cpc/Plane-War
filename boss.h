void drawboss(){
     SetPos(4,1);
     cout << "       ||||       _____       ||||       ";   
     SetPos(4,2);   
     cout << " _____|    |_____|__ __|_____|    |_____ ";
     SetPos(4,3); 
     cout << "|_____|    |_____|__|__|_____|    |_____|";
     SetPos(4,4); 
     cout << "      |____|   \\  |   |  /   |____|      ";
     SetPos(4,5);    
     cout << "                \\_|___|_/                ";         
     return;
}

void clearboss(){
     SetPos(4,1);
     cout << "                                         ";   
     SetPos(4,2);   
     cout << "                                         "; 
     SetPos(4,3); 
     cout << "                                         "; 
     SetPos(4,4); 
     cout << "                                         "; 
     SetPos(4,5);    
     cout << "                                         ";    
     return;
}


void judge_boss(){
    for(int i=0; i<25; i++)
	{
		if( bullet_exist[i] == true)
		{
			if(( bullet_pos[i].Y < 6 ) && (bullet_pos[i].X >= 4) && (bullet_pos[i].X <= 44)){
                boss_hp --;
			    bullet_exist[i]= false;
			    if (boss_hp < 0){
                     game_status = SUC;
                     clearboss();
                     return;
                }
            }
                            
		}
	}
	return;
}

COORD b_bullet_pos[25]; //boss子弹的坐标 

bool b_bullet_exist[25]; //boss子弹的标志位       
     
void b_init_bullet(){
     int i;
     for (i = 0; i < 25; i++){
            b_bullet_exist[i] = false;
            b_bullet_pos[i].X = 0;
            b_bullet_pos[i].Y = 0;
         }
     return;
}


void b_shoot(){
     int i;
     int tt = rand() % 12;
     if (tt > 5) return;
     for (i = 0; i < 25; i++){
         if (b_bullet_exist[i] == false){
            if (tt != 0) b_bullet_pos[i].X = rand()%47 + 1;
            else b_bullet_pos[i].X = p_pos.X; 
            b_bullet_pos[i].Y = 6;
            b_bullet_exist[i] = true;
               
            break;
         }
     }
     return;
}

     
void b_clear_bullet()
{
	for(int i=0; i<25; i++)
		if (b_bullet_exist[i] == true)
			{
				COORD temp = {b_bullet_pos[i].X, b_bullet_pos[i].Y};
				SetPos(temp);
				cout<<" ";
			}	
	return;
}

void b_move_bullet(){
	for(int i=0; i<25; i++)
	{
		if( b_bullet_exist[i] == true)
		{
			b_bullet_pos[i].Y += 1;
			if( b_bullet_pos[i].Y > 23 )
			b_bullet_exist[i]= false;
		}
	}
}

void b_draw_bullet(){
	for(int i=0; i<25; i++)
	{
		if( b_bullet_exist[i] == true)
		{
			SetPos(b_bullet_pos[i]);
			cout<<"*";	
		}
	}
}      
 
 
void b_judge(){
     for (int i = 0; i < 25; i++){
         if (b_bullet_exist[i] == true)
            if ((abs(b_bullet_pos[i].X - p_pos.X)<=1)&&(b_bullet_pos[i].Y == p_pos.Y)){
               b_bullet_exist[i] = false;
               p_hp = p_hp - 10*(2-abs(b_bullet_pos[i].X - p_pos.X));
               if (p_hp <= 0){
                  p_hp = 0;
                  game_status = OVER;
                  return;
               }
               
            }
     }
     return;
}             

