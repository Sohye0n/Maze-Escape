#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h"
#include "tri.h"
#include <deque>

class ofApp : public ofBaseApp{

	public:
		//-----기본 제공 함수----------
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//-----메뉴 기본 제공 함수----------
		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
		ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;

		// normal 모드플레이
		void Normalmode();
		// hard 모드플레이
		void Hardmode();
		//큐에 캐릭터의 초기값을 넣어주는 함수
		void move(int q);
		//종료시 메모리 정리하는 함수
		void quit();

		//s키를 눌러 본격적인 프로그램 시작시 세팅
		int program_start_flag;
		//p키를 눌러 미로 탈출을 시작시 세팅
		int game_start_flag;
		//캐릭터가 미로 탈출 지점에 도착시 세팅
		int game_over_flag;
		//노말 모드 선택시 세팅
		int normal_flag;
		//하드 모드 선택시 세팅
		int hard_flag;
		//미로가 생성되면 세팅
		int maze_created_flag;
		//귀신과 접촉해 얻은 데미지
		int damage;
		//생성할 미로의 크기(사용자 입력 받음)
		int trimaze_level;
		//삼각형 변 길이 단위
		int length = 5;
		//미로 탈출 시작, 종료, 소요 시간
		float starttime, endtime,totaltime;
		//탈출 후 화면에 띄워줄 문구 저장용 변수
		string timestring, damagestring;

		//normal 모드 미로 객체
		trimaze norm;
		//hard 모드 미로 객체
		trimaze hard;
		//귀신 경로 담은 배열
		vector<float>ghost;
		//귀신 x좌표 업데이트 값 담은 배열
		vector<double>plus;
		//캐릭터 현재 위치
		node* cur;
		//캐릭터 이동 경로 담은 큐
		deque<node*> path;
};