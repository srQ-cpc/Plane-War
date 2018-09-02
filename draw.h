

void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void SetPos(COORD a){
	HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j){
	COORD pos={i, j};
	SetPos(pos);
}

//把第y行，[x1, x2) 之间的坐标填充为 ch
void drawRow(int y, int x1, int x2, char ch){
	SetPos(x1,y);
	for(int i = 0; i <= (x2-x1); i++)
		cout << ch;
}

//把第x列，[y1, y2] 之间的坐标填充为 ch
void drawCol(int x, int y1, int y2, char ch){
	int y=y1;
	while(y!=y2+1)
	{
		SetPos(x, y);
		cout<<ch;
		y++;
	}
}

//左上角坐标、右下角坐标、用row填充行、用col填充列
void drawFrame(COORD a, COORD  b, char row, char col){
	drawRow(a.Y, a.X+1, b.X-1, row);
	drawRow(b.Y, a.X+1, b.X-1, row);
	drawCol(a.X, a.Y+1, b.Y-1, col);
	drawCol(b.X, a.Y+1, b.Y-1, col);
}

void drawFrame(int x1, int y1, int x2, int y2, char row, char col){
	COORD a={x1, y1};
	COORD b={x2, y2};
	drawFrame(a, b, row, col);
}

bool drawMenu()
{
    system("cls");
	SetPos(30, 1);
	cout<<"P l a n e  W a r";
	drawRow(3, 0, 79, '-');
	drawRow(5, 0, 79, '-');
	SetPos(28, 4);
	cout<<"w 和 s 选择， k 确定";
	SetPos(15, 11);
	cout<<"1. 简单模式";
	SetPos(15, 13);
	cout<<"2. 困难模式";
	drawRow(20, 0, 79, '-');
	drawRow(22, 0, 79, '-');
	SetPos(41, 11);
	cout<<"简单模式：";
	SetPos(45, 13);
	cout<<"敌人速度较慢，Boss的HP较少";
	SetPos(24, 21);
	cout<<"制作： 南京大学  131220003  高昊";
	bool f = true;
	SetPos(12, 11);
	cout<<">>";
	char c=_getch();
	 while(c!='k'){
        if ((c=='w')||(c=='s')){
           f = !f;
           if (f == true) {
		         SetPos(12, 13);
		         cout<<"　";
		         SetPos(12, 11);
		         cout<<">>";
		         SetPos(45, 13);
		         cout<<"　　　　　　　　　　　　  ";
		         SetPos(41, 11);
		         cout<<"简单模式：";
		         SetPos(45, 13);
		         cout<<"敌人速度较慢，Boss的HP较少";
           }
           else {
                 SetPos(12, 11);
		         cout<<"　";
		         SetPos(12, 13);
		         cout<<">>";
		         SetPos(45, 13);
		         cout<<"　　　　　　　　　　　　  ";
		         SetPos(41, 11);
		         cout<<"困难模式：";
		         SetPos(45, 13);
		         cout<<"敌人速度较快，Boss的HP较多";
            }     
        }
        c=_getch();
     }
     return f;
}


void drawPlaying(bool f){
    system("cls");
	drawFrame(0, 0, 48, 24, '=', '|');//	draw map frame;
	drawFrame(49, 0, 79, 4, '-', '|');//		draw output frame
	drawFrame(49, 4, 79, 8, '-', '|');//		draw score frame
	drawFrame(49, 8, 79, 20, '-', '|');//	draw operate frame
	drawFrame(49, 20, 79, 24, '-', '|');//	draw other message frame
	SetPos(56,2);
	cout<<"P l a n e  W a r";
	SetPos(52, 6);
	cout<<"得分：";
	SetPos(65, 6);
	cout<<"HP：";	
	SetPos(52, 22);
	cout<<"难度：";
	SetPos(65, 22);
	cout<<"进度："; 
	SetPos(52, 10);
	cout<<"操作方式：";
	SetPos(52,12);
	cout<<"  a,s,d,w 控制战机移动";
	SetPos(52,14);
	cout<<"  k 发射子弹";
	SetPos(52,16);
	cout<<"  p 暂停游戏  e 退出游戏";
	SetPos(52,18);
	cout<<"  r 重新开始游戏";
	 if (f == true) {
           SetPos(58, 22);
           cout << "简单";
           init_rank = 80;
           boss_hp = 200;
           factor = 100;
     }
     else {
           SetPos(58, 22);
           cout << "困难";
           init_rank = 50;
           boss_hp = 300;
           factor = 150;
     }   
}
