#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//---���ڵ� �״��---
	ofSetWindowTitle("TriMaze Escape"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	//---���ڵ� �״��---

	//---�÷��� ���� ����---
	program_start_flag = 0;
	game_start_flag = 0;
	trimaze_level = 0;
	normal_flag = 0;
	hard_flag = 0;
	maze_created_flag = 0;
	//---�÷��� ���� ����---


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
		//���ο� normal �̷θ� �׸��� ���̹Ƿ� normal_flag �ܿ� �� 0
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
		//���ο� hard �̷θ� �׸��� ���̹Ƿ� hard_flag �ܿ� �� 0
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
		//�ͽ� ��ǥ ������Ʈ
		//��� �ͽſ� ���� üũ
		for (int i = 0; i < norm.ghostvertice.size(); i++) {
			ghost[i] += plus[i];
			if (ghost[i] >= length * norm.ghostvertice[i].x_end || ghost[i] <= length * norm.ghostvertice[i].x_st) {
				plus[i] = plus[i] * -1;
			}

			//ĳ���Ϳ� ������ damage ������Ų��.
			if (path.back()->mid.second == norm.ghostvertice[i].y) {
				if (abs(length*path.back()->mid.first - ghost[i]) < 5) {
					damage++;
				}
			}
		}


		//Ż�������� �����ߴ��� üũ
		if (path.back()->mid.first == norm.endnode->mid.first && path.back()->mid.second == norm.endnode->mid.second) {
			//game_over_flag �ܿ� ���� 0���� ������ �ʱ�ȭ.
			game_start_flag = 0;
			game_over_flag = 1;
			normal_flag = 0;
			hard_flag = 0;
			maze_created_flag = 0;
		}

	}

	//hard mode
	if (maze_created_flag && hard_flag && game_start_flag) {

		//�ͽ� ��ǥ ������Ʈ
		//��� �ͽſ� ���� üũ
		for (int i = 0; i < hard.ghostvertice.size(); i++) {
			ghost[i] += plus[i];
			if (ghost[i] >= length * hard.ghostvertice[i].x_end || ghost[i] <= length * hard.ghostvertice[i].x_st) {
				plus[i] = plus[i] * -1;
			}

			//ĳ���Ϳ� ������ damage ������Ų��.
			if (path.back()->mid.second == hard.ghostvertice[i].y) {
				if (abs(length*path.back()->mid.first - ghost[i]) < 5) {
					damage++;
				}
			}
		}

		//Ż�������� �����ߴ��� üũ
		if (path.back()->mid.first == hard.endnode->mid.first && path.back()->mid.second == hard.endnode->mid.second) {
			//game_over_flag �ܿ� ���� 0���� ������ �ʱ�ȭ.
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
	//�̷� Ʋ �׸���
	ofBackground(0, 0, 0, 0);

	//�̷� �����Ǹ� �ٷ� �׸���
	if (maze_created_flag) {
		int p1x, p1y;
		int p2x, p2y;
		int p3x, p3y;
		int cnt = 1;
		//�븻��� ��ü
		if (normal_flag) {
			ofSetLineWidth(3);
			ofSetColor(0, 0, 255);
			for (int i = 0; i < norm.vertice_num; i++) {
				p1x = norm.tree[i].p1.first*length; p1y = norm.tree[i].p1.second*length;
				p2x = norm.tree[i].p2.first*length; p2y = norm.tree[i].p2.second*length;
				p3x = norm.tree[i].p3.first*length; p3y = norm.tree[i].p3.second*length;
				
				//���� �� �ﰢ��
				if (i == 0) {
					ofDrawLine(p1x, p1y, p2x, p2y);
					ofDrawLine(p3x, p3y, p1x, p1y);
				}
				//���ʺ� �ﰢ��
				if (i == cnt * cnt) {
					ofDrawLine(p1x, p1y, p2x, p2y);
					cnt++;
				}
				//�����ʺ� �ﰢ��
				else if (i == cnt * cnt - 1) ofDrawLine(p3x, p3y, p1x, p1y);

				//���������� ���� �ٴ� �ﰢ��
				if (i >= (norm.vertice_num - norm.nodes_in_level[trimaze_level - 1]) && p1y < p2y) ofDrawLine(p3x, p3y, p2x, p2y);

				//�Ʒ��� ������� ���� ��� ��
				if (norm.tree[i].adj[1] == nullptr  && p1y < p2y) {
					ofDrawLine(p2x, p2y, p3x, p3y);
				}
				//���ʰ� ������� ���� ��� ��
				if (norm.tree[i].adj[2] == nullptr) {
					ofDrawLine(p2x, p2y, p1x, p1y);
				}
				//�����ʰ� ������� ���� ��� ��
				if (norm.tree[i].adj[3] == nullptr) {
					ofDrawLine(p1x, p1y, p3x, p3y);
				}

			}
			program_start_flag++;

			//�ͽ� �׸���
			for (int i = 0; i < ghost.size(); i++) {
				ofDrawCircle(ghost[i], length*norm.ghostvertice[i].y, 3);
			}
		}
		//�ϵ��� ��ü
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
			//�ͽ� �׸���
			for (int i = 0; i < ghost.size(); i++) {
				ofDrawCircle(ghost[i], length*hard.ghostvertice[i].y, 3);
			}
		}

	}

	//���� ����. �̵� ��� �׸���
	if (maze_created_flag && game_start_flag) {

		if (normal_flag) {
			//���� ���� �׸���
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
			//������ �Ӹ� �׸���
			node* head = path.back();
			ofDrawCircle(length * head->mid.first, length * head->mid.second, 5);
		}

		else if (hard_flag) {
			//���� ���� �׸���
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
			//������ �Ӹ� �׸���
			node* head = path.back();
			ofDrawCircle(length * head->mid.first, length * head->mid.second, 5);
		}
	}

	if (game_over_flag >= 1) {
		ofSetColor(255, 0, 0);
		if (game_over_flag == 1) {
			//���� �ð� ����
			endtime = (ofGetElapsedTimeMillis() - starttime) / 1000;
			char totaltime[100];
			//sprintf�� float�� char���� �ٲٱ�
			sprintf(totaltime, "%.3f", endtime);
			//char���� �ѱ��ھ� ���ͼ� string�� �ٿ��ֱ�
			for (int i = 0; i < strlen(totaltime); i++) timestring += totaltime[i];
			timestring += " seconds used";
			
			damagestring += "Damage you got by the ghost ";
			char tmp[100];
			//sprintf�� int�� char�� �ٲٱ�
			sprintf(tmp, "%d", damage);
			for (int i = 0; i < strlen(tmp); i++) damagestring += tmp[i];
			//char���� �ѱ��ھ� ���ͼ� string�� �ٿ��ֱ�
			damagestring += "point";
		}
		//drawstring���� ȭ�鿡 ���
		myFont.drawString("You escaped!",100,380);
		myFont.drawString(timestring, 100, 400);
		myFont.drawString(damagestring, 100, 420);
		game_over_flag++;
	}

}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (game_start_flag) {
		
		//������ Ű ����
		if (key == OF_KEY_RIGHT) {
			//�����ʿ� ����� ��尡 ������
			if (cur->adj[3] != nullptr) {
				cur = cur->adj[3];
				path.push_back(cur);
			}
		}

		//���� Ű ����
		if (key == OF_KEY_LEFT) {
			//���ʿ� ����� ��尡 ������
			if (cur->adj[2] != nullptr) {
				cur = cur->adj[2];
				path.push_back(cur);
			}
		}

		//�Ʒ��� Ű ����
		if (key == OF_KEY_DOWN) {
			//path.push_back(cur);
			//�Ʒ��ʿ� ����� ��尡 ������
			if (cur->adj[1] != nullptr) {
				cur = cur->adj[1];
				path.push_back(cur);
			}
		}

		if (key == OF_KEY_UP) {
			//path.push_back(cur);
			//���ʿ� ����� ��尡 ������
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

		//�迭 ����
		vector<float>().swap(ghost);
		vector<double>().swap(plus);
		while (path.size()) path.pop_back();

		//norm �� ���鵵 �ʱ�ȭ
		norm.initialize();
		//���Ӱ� �̷� ����
		norm.build_a_maze(trimaze_level,0);
		cout << "done" << endl;

		//�ͽ� ������ ghost�� ����
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

		//�迭 ����
		vector<float>().swap(ghost);
		vector<double>().swap(plus);
		while (path.size()) path.pop_back();

		//hard �� ���鵵 �ʱ�ȭ
		hard.initialize();
		//���Ӱ� �̷� ����
		hard.build_a_maze(trimaze_level,1);
		cout << "done" << endl;

		for (int i = 0; i < hard.ghostvertice.size(); i++) {
			ghost.push_back(length*hard.ghostvertice[i].x_st);
			plus.push_back(0.33f);
		}

		//�ͽ� ������ ghost�� ����
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
	//ũ�罺Į�̳� �����̳�
	if(q==0) cur = &norm.tree[0];
	else if (q == 1) cur = &hard.tree[0];
	//ť�� ��� �߰�
	cout << cur->mid.first << endl;
	path.push_back(cur);
	cout << "psuh" << endl;
}

void ofApp::quit() {
	//���� �� �޸� ����
	vector<float>().swap(ghost);
	vector<double>().swap(plus);
	deque<node*>().swap(path);
}