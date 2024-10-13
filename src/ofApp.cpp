#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//---준코드 그대로---
	ofSetWindowTitle("TriMaze Escape"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	//---준코드 그대로---

	//---플래그 변수 세팅---
	program_start_flag = 0;
	game_start_flag = 0;
	trimaze_level = 0;
	normal_flag = 0;
	hard_flag = 0;
	maze_created_flag = 0;
	//---플래그 변수 세팅---


	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "Quit");


	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Play");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Normal mode", false, false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Hard mode", false, false); // Not checked (default)



	// Set the menu to the window
	menu->SetWindowMenu();

}

void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if (title == "Open") {
		//freeMemory();
		//openFile();
	}
	if (title == "Exit") {
		quit();
		ofExit(); // Quit the application
		//freeMemory();
	}

	//
	// Window menu
	//
	if (title == "Normal mode") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		//새로운 normal 미로를 그리는 것이므로 normal_flag 외에 다 0
		if (program_start_flag)
		{
			normal_flag = 1;
			hard_flag = 0;
			maze_created_flag = 0;
			game_start_flag = 0;
			damagestring = "";
			timestring = "";
			damage = 0;
			game_over_flag = 0;
			damage = 0;
			Normalmode();
		}
		else
			cout << "you must press S key first" << endl;

	}

	if (title == "Hard mode") {
		//새로운 hard 미로를 그리는 것이므로 hard_flag 외에 다 0
		if (program_start_flag)
		{
			normal_flag = 0;
			hard_flag = 1;
			maze_created_flag = 0;
			game_start_flag = 0;
			damagestring = "";
			timestring = "";
			damage = 0;
			game_over_flag = 0;
			damage = 0;
			Hardmode();

		}
		else
			cout << "you must press S key first" << endl;

	}


}
//--------------------------------------------------------------
void ofApp::update(){
	
	//normal mode
	if (maze_created_flag && game_start_flag &&normal_flag ) {
		//귀신 좌표 업데이트
		//모든 귀신에 대해 체크
		for (int i = 0; i < norm.ghostvertice.size(); i++) {
			ghost[i] += plus[i];
			if (ghost[i] >= length * norm.ghostvertice[i].x_end || ghost[i] <= length * norm.ghostvertice[i].x_st) {
				plus[i] = plus[i] * -1;
			}

			//캐릭터와 만나면 damage 증가시킨다.
			if (path.back()->mid.second == norm.ghostvertice[i].y) {
				if (abs(length*path.back()->mid.first - ghost[i]) < 5) {
					damage++;
				}
			}
		}


		//탈출지점에 도착했는지 체크
		if (path.back()->mid.first == norm.endnode->mid.first && path.back()->mid.second == norm.endnode->mid.second) {
			//game_over_flag 외에 전부 0으로 세팅해 초기화.
			game_start_flag = 0;
			game_over_flag = 1;
			normal_flag = 0;
			hard_flag = 0;
			maze_created_flag = 0;
		}

	}

	//hard mode
	if (maze_created_flag && hard_flag && game_start_flag) {

		//귀신 좌표 업데이트
		//모든 귀신에 대해 체크
		for (int i = 0; i < hard.ghostvertice.size(); i++) {
			ghost[i] += plus[i];
			if (ghost[i] >= length * hard.ghostvertice[i].x_end || ghost[i] <= length * hard.ghostvertice[i].x_st) {
				plus[i] = plus[i] * -1;
			}

			//캐릭터와 만나면 damage 증가시킨다.
			if (path.back()->mid.second == hard.ghostvertice[i].y) {
				if (abs(length*path.back()->mid.first - ghost[i]) < 5) {
					damage++;
				}
			}
		}

		//탈출지점에 도착했는지 체크
		if (path.back()->mid.first == hard.endnode->mid.first && path.back()->mid.second == hard.endnode->mid.second) {
			//game_over_flag 외에 전부 0으로 세팅해 초기화.
			game_start_flag = 0;
			game_over_flag = 1;
			normal_flag = 0;
			hard_flag = 0;
			maze_created_flag = 0;
		}
	}


}

//--------------------------------------------------------------
void ofApp::draw(){
	//int length = 5;
	//미로 틀 그리기
	ofBackground(0, 0, 0, 0);

	//미로 생성되면 바로 그리기
	if (maze_created_flag) {
		int p1x, p1y;
		int p2x, p2y;
		int p3x, p3y;
		int cnt = 1;
		//노말모드 객체
		if (normal_flag) {
			ofSetLineWidth(3);
			ofSetColor(0, 0, 255);
			for (int i = 0; i < norm.vertice_num; i++) {
				p1x = norm.tree[i].p1.first*length; p1y = norm.tree[i].p1.second*length;
				p2x = norm.tree[i].p2.first*length; p2y = norm.tree[i].p2.second*length;
				p3x = norm.tree[i].p3.first*length; p3y = norm.tree[i].p3.second*length;
				
				//제일 위 삼각형
				if (i == 0) {
					ofDrawLine(p1x, p1y, p2x, p2y);
					ofDrawLine(p3x, p3y, p1x, p1y);
				}
				//왼쪽벽 삼각형
				if (i == cnt * cnt) {
					ofDrawLine(p1x, p1y, p2x, p2y);
					cnt++;
				}
				//오른쪽벽 삼각형
				else if (i == cnt * cnt - 1) ofDrawLine(p3x, p3y, p1x, p1y);

				//뒤집어지지 않은 바닥 삼각형
				if (i >= (norm.vertice_num - norm.nodes_in_level[trimaze_level - 1]) && p1y < p2y) ofDrawLine(p3x, p3y, p2x, p2y);

				//아래와 연결되지 않은 경우 변
				if (norm.tree[i].adj[1] == nullptr  && p1y < p2y) {
					ofDrawLine(p2x, p2y, p3x, p3y);
				}
				//왼쪽과 연결되지 않은 경우 변
				if (norm.tree[i].adj[2] == nullptr) {
					ofDrawLine(p2x, p2y, p1x, p1y);
				}
				//오른쪽과 연결되지 않은 경우 변
				if (norm.tree[i].adj[3] == nullptr) {
					ofDrawLine(p1x, p1y, p3x, p3y);
				}

			}
			program_start_flag++;

			//귀신 그리기
			for (int i = 0; i < ghost.size(); i++) {
				ofDrawCircle(ghost[i], length*norm.ghostvertice[i].y, 3);
			}
		}
		//하드모드 객체
		else if (hard_flag) {
			ofSetLineWidth(3);
			ofSetColor(0, 255, 0);
			for (int i = 0; i < hard.vertice_num; i++) {
				p1x = hard.tree[i].p1.first*length; p1y = hard.tree[i].p1.second*length;
				p2x = hard.tree[i].p2.first*length; p2y = hard.tree[i].p2.second*length;
				p3x = hard.tree[i].p3.first*length; p3y = hard.tree[i].p3.second*length;

				//topmost triangle
				if (i == 0) {
					ofDrawLine(p1x, p1y, p2x, p2y);
					ofDrawLine(p3x, p3y, p1x, p1y);
				}
				//leftmost triangle
				if (i == cnt * cnt) {
					ofDrawLine(p1x, p1y, p2x, p2y);
					cnt++;
				}
				//rightmost triangle
				else if (i == cnt * cnt - 1) ofDrawLine(p3x, p3y, p1x, p1y);

				//non-reverse bottomost triangle
				if (i >= (hard.vertice_num - hard.nodes_in_level[trimaze_level - 1]) && p1y < p2y) ofDrawLine(p3x, p3y, p2x, p2y);

				//not connected to down
				if (hard.tree[i].adj[1] == nullptr  && p1y < p2y) {
					ofDrawLine(p2x, p2y, p3x, p3y);
				}
				//not connected to left
				if (hard.tree[i].adj[2] == nullptr) {
					ofDrawLine(p2x, p2y, p1x, p1y);
				}
				//not connected to right
				if (hard.tree[i].adj[3] == nullptr) {
					ofDrawLine(p1x, p1y, p3x, p3y);
				}

			}
			program_start_flag++;
			//귀신 그리기
			for (int i = 0; i < ghost.size(); i++) {
				ofDrawCircle(ghost[i], length*hard.ghostvertice[i].y, 3);
			}
		}

	}

	//게임 시작. 이동 경로 그리기
	if (maze_created_flag && game_start_flag) {

		if (normal_flag) {
			//도착 지점 그리기
			ofDrawCircle(length * norm.endnode->mid.first, length * norm.endnode->mid.second, 5);

			if (path.size() >= 5) {
				path.pop_front();
			}
			if (path.size() > 0) {
				for (int i = 0; i < path.size() - 1; i++) {
					ofSetLineWidth(3);
					ofDrawLine(length*path[i]->mid.first, length*path[i]->mid.second, length*path[i + 1]->mid.first, length*path[i + 1]->mid.second);
				}
			}
			//지렁이 머리 그리기
			node* head = path.back();
			ofDrawCircle(length * head->mid.first, length * head->mid.second, 5);
		}

		else if (hard_flag) {
			//도착 지점 그리기
			ofDrawCircle(length * hard.endnode->mid.first, length * hard.endnode->mid.second, 5);
			if (path.size() >= 5) {
				path.pop_front();
			}
			if (path.size() > 0) {
				for (int i = 0; i < path.size() - 1; i++) {
					ofSetLineWidth(3);
					ofDrawLine(length*path[i]->mid.first, length*path[i]->mid.second, length*path[i + 1]->mid.first, length*path[i + 1]->mid.second);
				}
			}
			//지렁이 머리 그리기
			node* head = path.back();
			ofDrawCircle(length * head->mid.first, length * head->mid.second, 5);
		}
	}

	if (game_over_flag >= 1) {
		ofSetColor(255, 0, 0);
		if (game_over_flag == 1) {
			//종료 시간 측정
			endtime = (ofGetElapsedTimeMillis() - starttime) / 1000;
			char totaltime[100];
			//sprintf로 float를 char으로 바꾸기
			sprintf(totaltime, "%.3f", endtime);
			//char에서 한글자씩 떼와서 string에 붙여주기
			for (int i = 0; i < strlen(totaltime); i++) timestring += totaltime[i];
			timestring += " seconds used";
			
			damagestring += "Damage you got by the ghost ";
			char tmp[100];
			//sprintf로 int를 char로 바꾸기
			sprintf(tmp, "%d", damage);
			for (int i = 0; i < strlen(tmp); i++) damagestring += tmp[i];
			//char에서 한글자씩 떼와서 string에 붙여주기
			damagestring += "point";
		}
		//drawstring으로 화면에 출력
		myFont.drawString("You escaped!",100,380);
		myFont.drawString(timestring, 100, 400);
		myFont.drawString(damagestring, 100, 420);
		game_over_flag++;
	}

}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (game_start_flag) {
		
		//오른쪽 키 선택
		if (key == OF_KEY_RIGHT) {
			//오른쪽에 연결된 노드가 있으면
			if (cur->adj[3] != nullptr) {
				cur = cur->adj[3];
				path.push_back(cur);
			}
		}

		//왼쪽 키 선택
		if (key == OF_KEY_LEFT) {
			//왼쪽에 연결된 노드가 있으면
			if (cur->adj[2] != nullptr) {
				cur = cur->adj[2];
				path.push_back(cur);
			}
		}

		//아래쪽 키 선택
		if (key == OF_KEY_DOWN) {
			//path.push_back(cur);
			//아래쪽에 연결된 노드가 있으면
			if (cur->adj[1] != nullptr) {
				cur = cur->adj[1];
				path.push_back(cur);
			}
		}

		if (key == OF_KEY_UP) {
			//path.push_back(cur);
			//위쪽에 연결된 노드가 있으면
			if (cur->adj[0] != nullptr) {
				cur = cur->adj[0];
				path.push_back(cur);
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 's') {
		cout << "creating trimaze..." << endl;
		cout << "input the size of maze (under 35)"; cin >> trimaze_level;
		cout << "select normal/hard mode..." << endl;
		program_start_flag = 1;
	}

	if (key == 'p') {
		if (program_start_flag && maze_created_flag&&!game_start_flag) {
			cout << "game play" << endl;
			game_start_flag = 1;
			cout << "now trying to move..." << endl;
			if(normal_flag) move(0);
			else if (hard_flag) move(1);
			starttime = ofGetElapsedTimeMillis();
			cout << "dondddd" << endl;
		}
		else cout << "press s first" << endl;
	}
}

void ofApp::Normalmode() {
	if (program_start_flag) {
		cout << "creating normal trimaze..." << endl;

		//배열 비우기
		vector<float>().swap(ghost);
		vector<double>().swap(plus);
		while (path.size()) path.pop_back();

		//norm 내 값들도 초기화
		norm.initialize();
		//새롭게 미로 생성
		norm.build_a_maze(trimaze_level,0);
		cout << "done" << endl;

		//귀신 정보를 ghost에 저장
		for (int i = 0; i < norm.ghostvertice.size(); i++) {
			ghost.push_back(length*norm.ghostvertice[i].x_st);
			plus.push_back(0.33f);
		}

		maze_created_flag = 1;
		cout << "maze created" << endl;
	}
}

void ofApp::Hardmode() {
	if (program_start_flag) {
		cout << "creating hard trimaze..." << endl;

		//배열 비우기
		vector<float>().swap(ghost);
		vector<double>().swap(plus);
		while (path.size()) path.pop_back();

		//hard 내 값들도 초기화
		hard.initialize();
		//새롭게 미로 생성
		hard.build_a_maze(trimaze_level,1);
		cout << "done" << endl;

		for (int i = 0; i < hard.ghostvertice.size(); i++) {
			ghost.push_back(length*hard.ghostvertice[i].x_st);
			plus.push_back(0.33f);
		}

		//귀신 정보를 ghost에 저장
		maze_created_flag = 1;
		cout << "maze created" << endl;

	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::move(int q) {
	//크루스칼이냐 프림이냐
	if(q==0) cur = &norm.tree[0];
	else if (q == 1) cur = &hard.tree[0];
	//큐에 경로 추가
	cout << cur->mid.first << endl;
	path.push_back(cur);
	cout << "psuh" << endl;
}

void ofApp::quit() {
	//종료 전 메모리 정리
	vector<float>().swap(ghost);
	vector<double>().swap(plus);
	deque<node*>().swap(path);
}