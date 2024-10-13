#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h"
#include "tri.h"
#include <deque>

class ofApp : public ofBaseApp{

	public:
		//-----�⺻ ���� �Լ�----------
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

		//-----�޴� �⺻ ���� �Լ�----------
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

		// normal ����÷���
		void Normalmode();
		// hard ����÷���
		void Hardmode();
		//ť�� ĳ������ �ʱⰪ�� �־��ִ� �Լ�
		void move(int q);
		//����� �޸� �����ϴ� �Լ�
		void quit();

		//sŰ�� ���� �������� ���α׷� ���۽� ����
		int program_start_flag;
		//pŰ�� ���� �̷� Ż���� ���۽� ����
		int game_start_flag;
		//ĳ���Ͱ� �̷� Ż�� ������ ������ ����
		int game_over_flag;
		//�븻 ��� ���ý� ����
		int normal_flag;
		//�ϵ� ��� ���ý� ����
		int hard_flag;
		//�̷ΰ� �����Ǹ� ����
		int maze_created_flag;
		//�ͽŰ� ������ ���� ������
		int damage;
		//������ �̷��� ũ��(����� �Է� ����)
		int trimaze_level;
		//�ﰢ�� �� ���� ����
		int length = 5;
		//�̷� Ż�� ����, ����, �ҿ� �ð�
		float starttime, endtime,totaltime;
		//Ż�� �� ȭ�鿡 ����� ���� ����� ����
		string timestring, damagestring;

		//normal ��� �̷� ��ü
		trimaze norm;
		//hard ��� �̷� ��ü
		trimaze hard;
		//�ͽ� ��� ���� �迭
		vector<float>ghost;
		//�ͽ� x��ǥ ������Ʈ �� ���� �迭
		vector<double>plus;
		//ĳ���� ���� ��ġ
		node* cur;
		//ĳ���� �̵� ��� ���� ť
		deque<node*> path;
};