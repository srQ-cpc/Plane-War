COORD p_pos; //玩家的坐标 

COORD bullet_pos[25]; //子弹的坐标 

bool bullet_exist[25]; //子弹的标志位 

int p_hp;//玩家的HP 


//玩家 
void display_plane(){
     SetPos(p_pos.X - 1, p_pos.Y);
     cout << "-A-";
     return;
}  

void init_plane(){
     p_pos.X = 24;
     p_pos.Y = 23;
     display_plane();
     return;
}

void move_plane(char x){
     switch(x){
               case 'w':
                    int tt;
                    if (p_pos.Y != 7){
                         SetPos(p_pos.X - 1, p_pos.Y);
                         cout << "   ";
                         p_pos.Y --;
                    }
                    break;
               case 'a':
                    if (p_pos.X != 2){
                         SetPos(p_pos.X - 1, p_pos.Y);
                         cout << "   ";
                         p_pos.X --;
                    }
                    break;
               case 's':
                    if (p_pos.Y != 23){
                         SetPos(p_pos.X - 1, p_pos.Y);
                         cout << "   ";
                         p_pos.Y ++;
                         display_plane();
                    }
                    break;
               case 'd':
                    if (p_pos.X != 46){
                         SetPos(p_pos.X - 1, p_pos.Y);
                         cout << "   ";
                         p_pos.X ++;
                    }
                    break;
               default: break;
     }
     display_plane();
     return;
}    

//子弹 
void init_bullet(){
     int i;
     for (i = 0; i < 25; i++){
            bullet_exist[i] = false;
            bullet_pos[i].X = 0;
            bullet_pos[i].Y = 0;
         }
}

void shoot(){
     int i;
     for (i = 0; i < 25; i++){
         if (bullet_exist[i] == false){
            bullet_pos[i].X = p_pos.X;
            bullet_pos[i].Y = p_pos.Y - 1;
            bullet_exist[i] = true;
            SetPos(bullet_pos[i]);
			cout<<"^";
            break;
         }
     }
     return;
}

void clear_bullet()
{
	for(int i=0; i<25; i++)
		if ((bullet_exist[i] == true)&&(( bullet_pos[i].X != p_pos.X)||( bullet_pos[i].Y != p_pos.Y)))
			{
				COORD temp = {bullet_pos[i].X, bullet_pos[i].Y};
				SetPos(temp);
				cout<<" ";
			}	
}

void move_bullet(){
	for(int i=0; i<25; i++)
	{
		if( bullet_exist[i] == true)
		{
			bullet_pos[i].Y -= 1;
			if( bullet_pos[i].Y < 1 )
			bullet_exist[i]= false;
		}
	}
}

void draw_bullet(){
	for(int i=0; i<25; i++)
	{
		if( bullet_exist[i] == true)
		{
			SetPos(bullet_pos[i]);
			cout<<"^";	
		}
	}
}
     
        



