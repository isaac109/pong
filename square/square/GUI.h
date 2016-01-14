#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Paddle.h"

namespace GUI
{
	void initialize(int argc, char* argv[], bool p1);
	void update();
	void special(int key, int, int); // GLUT function for reading key input
	void special2(char key); //based off glut function but for moving opponent
	void changeViewport(int w, int h);
	void render();
	void moveBall();
	void newBall();
	void newBall(char x, char y);
	struct GUIData
	{
		GUIData()
			:_heightp1(400.0f)
			, _widthp1(50.0f)
			, _heightp2(400.0f)
			,_widthp2(800.0f)
			,_paddleSpeed(100.0f)
			,_maxHeight(600.0f)
			,_minHeight(100.0f)
			,_isP1(false)
			,_ballW(400.0f)
			,_ballH(500.0f)
			,_ballR(30.0f)
			,_ballSeg(32)
			,_ballUp(true)
			,_ballLeft(true)
			,_ballSpeed(5.0f)
			,_scoreP1(0)
			,_scoreP2(0)
			,_hitP1(true)
			,_isWon(false)
			,_winScore(10)
			,_isStart(true)
			,_time(5)
		{
		}
		//void MoveLeft(bool isMine);
		//void MoveRight(bool isMine);
		void MoveUp(bool isMine);
		void MoveDown(bool isMine);
		void clearMessage();
		void setP1(bool p1);
		void setPaddles();
		void drawCircle();
		void displayScore();
		void checkIfWin();
		void displayWin();
		void displayCountDown();
		char message[4];
		float _heightp1;
		float _widthp1;
		float _heightp2;
		float _widthp2;
		float _paddleSpeed;
		float _maxHeight;
		float _minHeight;
		int _scoreP1;
		int _scoreP2;
		float _ballW;
		float _ballH;
		float _ballR;
		int _ballSeg;
		bool _ballUp;
		bool _ballLeft;
		float _ballSpeed;
		bool _isP1;
		bool _hitP1;
		bool _isWon;
		int _winScore;
		bool _isStart;
		int _time;
		Paddle myPaddle;
		Paddle theirPaddle;

	};

	const GUIData& GetData();
	GUIData& MutableData();
};