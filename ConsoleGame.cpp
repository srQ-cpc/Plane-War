#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


using namespace std;

//��Ϸ״̬ 
enum STATUS {OVER = -1 , START, PLAY, SUC};

STATUS game_status;

int init_rank,rank;//�ٶ� 

int process;//���� 

//boss
bool boss;
int boss_hp;

//��Ϸ�÷� 
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
