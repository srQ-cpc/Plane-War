class Enemy{
      COORD e_pos;
      public:
             bool exist;
             Enemy(){ 
                      e_pos.X = 0; 
                      e_pos.Y = 0;
                      exist = true;
             } 
             Enemy(int x,int y){ 
                      e_pos.X = x; 
                      e_pos.Y = y;
                      exist = true;
             } 
             void boom(); 
             bool crash(int x,int y); 
             bool bullet_crash(int x,int y); 
             void alive();
             friend void move(Enemy &p , int q);
             friend void e_shoot();
             void drawtonull();
             void draw();
};



void Enemy::boom(){
     if ((abs(p_pos.X - e_pos.X)<=2)&&(p_pos.Y == e_pos.Y))
     game_status = OVER;
     return;
}

bool Enemy::crash(int x,int y){
     if ((abs(x - e_pos.X)<=2)&&(y == e_pos.Y))return true;
     else return false;
}

bool Enemy::bullet_crash(int x,int y){
     if ((abs(x - e_pos.X)<=1)&&(y == e_pos.Y))return true;
     else return false;
}



void Enemy::alive(){
     for (int i = 0; i < 25; i++){
         if (bullet_exist[i] == true)
            if ((abs(bullet_pos[i].X - e_pos.X)<=1)&&(bullet_pos[i].Y == e_pos.Y)){
               drawtonull();
               bullet_exist[i] = false;
               exist = false;
               score = score + factor;
               return;
            }
     }
     return;
}


void Enemy::drawtonull(){
     if (exist == true){
        SetPos(e_pos.X - 1, e_pos.Y);
        cout << "   ";
     }
     return;
}

void Enemy::draw(){
     if (exist == true){
        SetPos(e_pos.X - 1, e_pos.Y);
        cout << "-V-";
     }
     return;
}

#define MAX 5

static Enemy enemy[MAX];

void init_enemy(){
     for (int i = 0; i < MAX; i++){
         enemy[i].exist = false;
     }
     return;
}
    
bool enemy_crash(int x, int y){
     for (int i = 0; i < MAX; i++)
         if (enemy[i].exist == true)
            if (enemy[i].crash(x , y) == true) return true;
            
     return false;
}
   
void move(Enemy &p , int q){
     int t = rand()%6;
     int xx,yy;
     switch(t){
               case 0: 
                    xx = p.e_pos.X - 1;
                    yy = p.e_pos.Y;
                    if (xx < 2) return;
                    for (int i = 0; i < MAX; i++)
                        if ((enemy[i].exist == true) && (i != q)) 
                           if (enemy[i].crash(xx , yy) == true) return;
                    p.e_pos.X = xx;     
                    p.e_pos.Y = yy;
                    break;
               case 1:
                    xx = p.e_pos.X + 1;
                    yy = p.e_pos.Y;
                    if (xx > 46) return;
                    for (int i = 0; i < MAX; i++)
                        if ((enemy[i].exist == true) && (i != q)) 
                           if (enemy[i].crash(xx , yy) == true) return;
                    p.e_pos.X = xx;     
                    p.e_pos.Y = yy;
                    break;   
               default:
                    xx = p.e_pos.X;
                    yy = p.e_pos.Y + 1;
                    if (yy > 23) {
                           p_hp = p_hp - 5;
                           if (p_hp <= 0){
                                    p_hp = 0;
                                    game_status = OVER;
                           }
                           p.exist = false;
                           return;
                    }
                    for (int i = 0; i < MAX; i++)
                        if ((enemy[i].exist == true) && (i != q)) 
                           if (enemy[i].crash(xx , yy) == true) return;
                    p.e_pos.X = xx;     
                    p.e_pos.Y = yy;
                    break;    
      
     }
     return;
}   
  


void new_enemy(){
     for (int i = 0; i < MAX; i++){
         if (enemy[i].exist == false){
            int xx = 2 + rand()%45;
            if (enemy_crash(xx , 1) == true) return;
            Enemy t(xx, 1);
            enemy[i] = t;
            enemy[i].exist = true;
            process ++;
            return;
         }
     }
     return;
}

void draw_enemy_to_null(){
     for (int i = 0; i < MAX; i++){
         if (enemy[i].exist == true)
            enemy[i].drawtonull();
     }
     return;
}
     

void enemy_move(){
     for (int i = 0; i < MAX; i++){
         if (enemy[i].exist == true)
            move(enemy[i] , i);
     }
     return;
}

void draw_enemy(){
     for (int i = 0; i < MAX; i++){
         if (enemy[i].exist == true)
            enemy[i].draw();  
     }
     return;     
}

void judge_enemy(){
     for (int i = 0; i < MAX; i++){
         if (enemy[i].exist == true)
            enemy[i].alive();   
     }
     return;    
}

void judge_plane(){
     for (int i = 0; i < MAX; i++){
         if (enemy[i].exist == true)
            enemy[i].boom();    
     }
     return;   
}
  
COORD e_bullet_pos[25]; //敌人子弹的坐标 

bool e_bullet_exist[25]; //敌人子弹的标志位       
     
void e_init_bullet(){
     int i;
     for (i = 0; i < 25; i++){
            e_bullet_exist[i] = false;
            e_bullet_pos[i].X = 0;
            e_bullet_pos[i].Y = 0;
         }
     return;
}

bool draw_crash(int x, int y){
     for (int i = 0; i < MAX; i++)
         if (enemy[i].bullet_crash(x,y) == true) return true;
     return false;
}

void e_shoot(){
     int i;
     int tt = rand() % 10;
     if (tt != 0) return;
     for (i = 0; i < 25; i++){
         if (e_bullet_exist[i] == false){
            int t = rand() % MAX;
            if ((enemy[t].exist == true)&&(enemy[t].e_pos.Y < 23)){
               e_bullet_pos[i].X = enemy[t].e_pos.X;
               e_bullet_pos[i].Y = enemy[t].e_pos.Y + 1;
               e_bullet_exist[i] = true;
            }
            break;
         }
     }
     return;
}

     
void e_clear_bullet()
{
	for(int i=0; i<25; i++)
		if (e_bullet_exist[i] == true)
			{
                if (draw_crash(e_bullet_pos[i].X,e_bullet_pos[i].Y) == true) continue;
				COORD temp = {e_bullet_pos[i].X, e_bullet_pos[i].Y};
				SetPos(temp);
				cout<<" ";
			}	
	return;
}

void e_move_bullet(){
	for(int i=0; i<25; i++)
	{
		if( e_bullet_exist[i] == true)
		{
			e_bullet_pos[i].Y += 1;
			if( e_bullet_pos[i].Y > 23 )
			e_bullet_exist[i]= false;
		}
	}
}

void e_draw_bullet(){
	for(int i=0; i<25; i++)
	{
		if( e_bullet_exist[i] == true)
		{
            if (draw_crash(e_bullet_pos[i].X,e_bullet_pos[i].Y) == true) continue;
			SetPos(e_bullet_pos[i]);
			cout<<".";	
		}
	}
}      
 
 
void e_judge(){
     for (int i = 0; i < 25; i++){
         if (e_bullet_exist[i] == true)
            if ((abs(e_bullet_pos[i].X - p_pos.X)<=1)&&(e_bullet_pos[i].Y == p_pos.Y)){
               e_bullet_exist[i] = false;
               p_hp = p_hp - 5*(2-abs(e_bullet_pos[i].X - p_pos.X));
               if (p_hp <= 0){
                  p_hp = 0;
                  game_status = OVER;
                  return;
               }
               
            }
     }
     return;
}             

bool enemy_end(){
     for (int i = 0; i< MAX;i++)
         if (enemy[i].exist == true) return false;
     return true;
} 

bool bullet_end(){
     for (int i = 0; i< 25;i++)
         if (e_bullet_exist[i] == true) return false;
     return true;
} 
