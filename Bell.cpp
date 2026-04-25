//ÁåÉù By Wormwaker
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <tchar.h>
#include <time.h>
#include <vector>
using namespace std;
void DebugLog(const char* s)
{
	printf(s);
	printf("\n");
}
#include "cplayer.h"
//#define BELL_T 10*1000	//ms
CPlayer bell1;
CPlayer bell2;
CPlayer bell3;
clock_t lastBell;
bool fl=false;

int GetHour(void)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return (ltm->tm_hour);
}
int GetMinute(void)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return (ltm->tm_min);
}
void Bell(short tag)
{
	fl=true;
	printf("------%02d:%02d------\n",GetHour(),GetMinute());
//	if(!fl)
//	{
//		bell.Play();
//		fl=true;
//	}else{
//		fl=true;
//		bell.Continue();
//	}
	clock_t cd=10000;
	if(tag==1)	//up 
	{
		bell1.Play(0);cd=14500;
	}else if(tag==0){	//down
		bell2.Play(0);cd=11500;
	}else if(tag==2){	//down

		bell3.Play(0);cd=170000;
	}else if(tag==3)
	{
		bell2.Play(0);cd=45997;
	 } 
	Sleep(cd);
		
	if(tag==1)
	{
		bell1.Pause();
	}else if(tag==0||tag==3)
		bell2.Pause();
	else
		bell3.Pause();
	
}
int main()	//up1 down0 
{
	lastBell = clock() - 2000;
	const vector<short> sch {
		/*6,55,1,		7,0,1,		7,30,0,		7,40,1,		8,20,0,		8,30,1,		9,10,0,		9,20,1,		10,0,0,
		10,30,1,	11,10,0,	11,20,1,	12,0,0,		12,35,1,
		13,30,2,	13,40,1,	14,20,0,	14,30,1,	15,15,0,	15,25,1,	16,5,0,		16,15,1,	16,55,0,	17,0,3,
		//17,40,1,	18,10,1,	19,0,0,		19,15,1,	20,20,0,	20,30,1,	21,50,0*/
		13,20,2,    13,25,1,	14,5,0,		14,15,1,	14,55,0,	15,5,1,		15,45,0,
		15,55,1,	16,35,0,	17,20,1,	18,0,1,
		19,0,0,		19,15,1,	20,20,0,	20,30,1,	21,50,3
		
		};
	SetConsoleTitleA("ÁåÉù v1.0 by Wormwaker");
	printf("------¶ÁÈ¡ÎÄ¼þ------");
	bell1.Open("up.mp3");
	bell2.Open("down.mp3");
	bell3.Open("wake.mp3");
	bell1.SetVolume(60);
	bell2.SetVolume(60);
	bell3.SetVolume(72);
	while(1)
	{
		for(short i = 0; i < sch.size()/3; ++i)
		{
			if(sch[i*3] == GetHour() && sch[i*3+1] == GetMinute()
			&& (!fl || clock() - lastBell > 59998))
			{
				Bell(sch[i*3+2]);
				lastBell = clock();
			}
		}
		Sleep(1000);
	}
	bell1.Stop();
	bell2.Stop();
	bell3.Stop();
	bell1.Close();
	bell2.Close();
	bell3.Close();
	return 0;
} 
