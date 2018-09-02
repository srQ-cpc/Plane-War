#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


using namespace std;

//游戏状态 
enum STATUS {OVER = -1 , START, PLAY, SUC};

STATUS game_status;

int init_rank,rank;//速度 

int process;//进程 

//boss
bool boss;
int boss_hp;

//游戏得分 
int factor; 
int score; 

#include"draw.h"
#include"plane.h"
#include"enemy.h"
#include"boss.h"
#include"control.h"



int main()
{
    PlayGame();
    return 0;
}
