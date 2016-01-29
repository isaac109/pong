#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Paddle.h"


//game logic
namespace GUI
{
	void initialize(int argc, char* argv[], bool p1);
	void update();
	//function called by glut on key press
	void special(int key, int, int); 
	//determines what to do with special key press
	void determinePlayerMovement( int key, int, int);
	//function called to mimic special on recieving an opponent key press
	void special2(char key); 
	//determines what to do with special2 key press
	void determineOpponentMovement(char key);
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
			,_ballW(400.0f)
			,_ballH(500.0f)
			,_ballR(30.0f)
			,_ballSpeed(5.0f)
			,_ballSeg(32)
			,_scoreP1(0)
			,_scoreP2(0)
			,_winScore(10)
			,_time(5)
			,_isP1(false)
			,_ballUp(true)
			,_ballLeft(true)
			,_hitP1(true)
			,_isWon(false)
			,_isStart(true)
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
		float _ballW;
		float _ballH;
		float _ballR;
		float _ballSpeed;
		int _scoreP1;
		int _scoreP2;
		int _ballSeg;
		int _winScore;
		int _time;
		bool _ballUp;
		bool _ballLeft;
		bool _isP1;
		bool _hitP1;
		bool _isWon;
		bool _isStart;
		Paddle myPaddle;
		Paddle theirPaddle;

	};

	const GUIData& GetData();
	GUIData& MutableData();
};