#include <SFML/Graphics.hpp>     
#include "Headers/Global.h"
#include "Headers/Rectangle.h"
#include "Headers/Text.h"
#include "Headers/Button.h"
#include "Headers/Map.h"
#include "Headers/Pacman.h"
#include "Headers/Ghost.h"
#include "Headers/Blinky.h"
#include "Headers/Clyde.h"
#include "Headers/Pinky.h"
#include "Headers/Inky.h"

int main() {
	loadSettings();
	std::vector<std::vector<_i64>> GameMap;
	std::vector<std::vector<_i64>> GameplayMap;
	scanMap(GameMap, _Settings::__MapNames[_Settings::__MapNumber]);
	copyMap(GameMap, GameplayMap);
	scanHighscore(_Settings::__MapNames[_Settings::__MapNumber]);
	sf::RenderWindow GameWindow(sf::VideoMode((_Settings::__Widht + _Settings::__ExtraWidht) * _Settings::__CellSize * _Settings::__ScreenResize / 2,
											  (_Settings::__Height+ _Settings::__ExtraHeight) * _Settings::__CellSize * _Settings::__ScreenResize / 2),
								"Pacman", sf::Style::Close);
	reloadWindow(GameWindow);
	GameWindow.setVerticalSyncEnabled(true);
	sf::Texture _BackgroundTexture;
	sf::Sprite _Background; //Задний фон
	reloadBackground(_BackgroundTexture, _Background);
	sf::Texture _LogoTexture;
	sf::Sprite _Logo; 	//Логотип
	reloadLogo(_LogoTexture, _Logo);
	sf::Image _Icon;
	_Icon.loadFromFile("Materials/icon.png");
	GameWindow.setIcon(256, 256, _Icon.getPixelsPtr());
	///Начальное меню
	Button btnGame(&GameWindow);
	btnGame.setMouseClick(sf::Mouse::Button::Left);
	btnGame.RCT.setSize(150.f, 60.f);
	btnGame.RCT.setPosCentre(0.f, -40.f);
	btnGame.RCT.setColor(RGB(234, 122, 8), RGB(20, 201, 20));
	btnGame.RCT.setColorTurn(RGB(5, 129, 193), RGB(23, 160, 110));
	btnGame.RCT.setBorderColor(RGB(217, 65, 25), RGB(31, 110, 21));
	btnGame.RCT.setBorderColorTurn(RGB(23, 103, 139), RGB(19, 98, 69));
	btnGame.RCT.setBorder(4.f);
	btnGame.TXT.setColor(RGB(241, 223, 76), RGB(151, 204, 19));
	btnGame.TXT.setColorTurn(RGB(5, 175, 240), RGB(5, 193, 117));
	btnGame.TXT.setBorder(2.f);
	btnGame.TXT.setSize(24);
	btnGame.TXT.setString("Game");
	Button btnSettings = btnGame;
	btnSettings.RCT.setPosCentre(0.f, 40.f);
	btnSettings.TXT.setString("Settings");
	Button btnExit = btnGame;
	btnExit.RCT.setPosCentre(0.f, 120.f);
	btnExit.TXT.setString("Exit");
	///Возврат назад и затемнение
	Button btnReturn = btnExit;
	btnReturn.TXT.setString("Return");
	Rectangle rctDark(&GameWindow);
	rctDark.setPosition(0.f, 0.f);
	rctDark.setColor(RGB(0, 0, 0, 150));
	rctDark.setSize((_f32)((_Settings::__Widht + _Settings::__ExtraWidht) * 16.f  ),
		            (_f32)((_Settings::__Height + _Settings::__ExtraHeight) * 16.f));
	///Настройки
	Button btnNextName = btnGame;
	btnNextName.RCT.setSize(60.f, 30.f);
	btnNextName.RCT.setPosCentre(110.f, -40.f);
	btnNextName.TXT.setString(">");
	btnNextName.TXT.setSize(22);
	Button btnNextLevel = btnNextName;
	btnNextLevel.RCT.setPosCentre(110.f, 0.f);
	_ui64 _iNames = _Settings::__MapNumber;
	Rectangle rctName = btnNextName.getRectangle();
	rctName.setSize(190.f, 30.f);
	rctName.setPosCentre(-40.f, -40.f);
	Text txtName = btnNextName.getText();
	txtName.setSize(22);
	txtName.setString(_Settings::__MapNames[_iNames]);
	txtName.setCentral(rctName.getPosition(), rctName.getSize());
	_ui64 _iLevelColors = _Settings::__SkinNumber;
	Rectangle rctLevel = rctName;
	rctLevel.setPosCentre(-40.f, 0.f);
	Text txtLevel = txtName;
	txtLevel.setString(_Settings::__SkinNames[_iLevelColors]);
	txtLevel.setCentral(rctLevel.getPosition(), rctLevel.getSize());
	Button btnShow = btnGame;
	btnShow.RCT.setSize(80.f, 30.f);
	btnShow.RCT.setPosCentre(-95.f, 40.f);
	btnShow.TXT.setString("Show");
	btnShow.TXT.setSize(22);
	Button btnCreate = btnShow;
	btnCreate.RCT.setSize(170.f, 30.f);
	btnCreate.RCT.setPosCentre(55.f, 40.f);
	btnCreate.TXT.setString("Create new");
	Button btn16P = btnShow;
	btn16P.RCT.setSize(80.f, 30.f);
	btn16P.RCT.setPosCentre(-90.f, 80.f);
	btn16P.TXT.setString("16p");
	btn16P.TXT.setSize(24);
	btn16P.setButtonSwitch();
	Button btn32P = btn16P;
	btn32P.RCT.setPosCentre(0.f, 80.f);
	btn32P.TXT.setString("32p");
	Button btn64P = btn16P;
	btn64P.RCT.setPosCentre(90.f, 80.f);
	btn64P.TXT.setString("64p");
	switch (_Settings::__CellSize) {
		case 16: btn16P.turnOnSwitch(); break;
		case 32: btn32P.turnOnSwitch(); break;
		case 64: btn64P.turnOnSwitch(); break;
		default: btn16P.turnOnSwitch(); break;
	}
	Button btnReturnSett = btnGame;
	btnReturnSett.RCT.setSize(150.f, 30.f);
	btnReturnSett.RCT.setPosCentre(0.f, 120.f);
	btnReturnSett.TXT.setString("Return");
	///Просмотр карты
	Button btnDeleteMap = btnGame;
	btnDeleteMap.RCT.setSize(100.f, 15.f);
	btnDeleteMap.RCT.setPosCentre(110.f, 167.f);
	btnDeleteMap.TXT.setSize(16);
	btnDeleteMap.TXT.setString("Delete");
	Text txtErrorDel(&GameWindow);
	txtErrorDel.setString("Map cant be deleted");
	txtErrorDel.setSize(8);
	txtErrorDel.setBorder(1.f);
	txtErrorDel.setPosCentre(0.f, 167.f);
	txtErrorDel.setColor(RGB(250, 5, 5));
	txtErrorDel.setBorderColor(RGB(150, 7, 7));
	///Создание карты
	Button btnCreateMap = btnDeleteMap;
	btnCreateMap.TXT.setString("Create");
	Button bntReturnShowCreate = btnCreateMap;
	bntReturnShowCreate.RCT.setSize(100, 15);
	bntReturnShowCreate.RCT.setPosCentre(-110, 167);
	bntReturnShowCreate.TXT.setString("Return");
	Text txtError = txtErrorDel;
	txtError.setString("Error:");
	txtError.setSize(10);
	txtError.setPosCentre(0.f, 162.f);
	Text txtErrorReasonE = txtError;
	txtErrorReasonE.setString("Too many entities");
	txtErrorReasonE.setSize(8);
	txtErrorReasonE.setPosCentre(0.f, 170.f);
	Text txtErrorReasonPel = txtErrorReasonE;
	txtErrorReasonPel.setString("Pellets dont exist");
	Text txtErrorReasonPcmn = txtErrorReasonE;
	txtErrorReasonPcmn.setString("Pacman doesnt exist");
	std::vector<std::vector<_i64>> GameMapCreate;
	scanMap(GameMapCreate, "Standart");
	_bool ButMap = false;
	std::vector<std::vector<Button>> GameMapButtons;
	///Конец создания
	std::string NewMapName = "";
	Rectangle rctInputNamePlease = btnGame.getRectangle();
	rctInputNamePlease.setSize(195.f, 60.f);
	rctInputNamePlease.setPosCentre(0.f, -40.f);
	Text txtInputNamePlease = btnGame.getText();
	txtInputNamePlease.setString("Input name:");
	txtInputNamePlease.setSize(24);
	txtInputNamePlease.setCentral(rctInputNamePlease.getPosition(), rctInputNamePlease.getSize());
	Rectangle rctInputName = rctInputNamePlease;
	rctInputName.setSize(250.f, 60.f);
	rctInputName.setPosCentre(0.f, 40.f);
	Text txtTypeName(&GameWindow);
	txtTypeName.setColor(RGB(241, 223, 76), RGB(151, 204, 19));
	txtTypeName.setBorder(2.f);
	txtTypeName.setBorderColor(sf::Color::Black, RGB(217, 65, 25));
	txtTypeName.setSize(20);
	txtTypeName.setString("<<Name>>");
	Button btnReturnSave = btnReturn;
	btnReturnSave.RCT.setSize(120.f, 60.f);
	btnReturnSave.RCT.setPosCentre(-65.f, 120.f);
	Button btnSave = btnGame;
	btnSave.RCT.setSize(110.f, 60.f);
	btnSave.RCT.setPosCentre(70.f, 120.f);
	btnSave.TXT.setString("Save");
	btnSave.TXT.setSize(24);
	Text ErrorReasonSave = txtErrorReasonE;
	ErrorReasonSave.setString("The map already exists");
	///Меню: Игра
	Button btnPlay = btnGame;
	btnPlay.TXT.setString("Play");
	Button btnHighscore = btnSettings;
	btnHighscore.TXT.setString("Highscore");
	///Меню: Играть
	Button btnContinue = btnGame;
	btnContinue.RCT.setSize(150.f, 60.f);
	btnContinue.RCT.setPosCentre(0.f, -40.f);
	btnContinue.TXT.setString("Continue");
	Button btnExitGame = btnGame;
	btnExitGame.RCT.setPosCentre(0.f, 40.f);
	btnExitGame.TXT.setString("Exit");
	///Меню: Рекорды
	Rectangle rctHighscore = btnExitGame.getRectangle();
	rctHighscore.setPosCentreOff();
	rctHighscore.setPosition(50.f, 30.f);
	rctHighscore.setSize(236.f, 220.f);	
	Text txtHighscores = btnGame.getText();
	txtHighscores.setPosCentreOff();
	txtHighscores.setCentralOff();
	///Меню: Победа
	Text txtVictory = btnGame.getText();
	txtVictory.setString("Victory!");
	txtVictory.setBorderColor(RGB(76, 153, 0));
	txtVictory.setSize(40);
	txtVictory.setPosCentre(0.f, -100.f);
	///Меню: Проигрыш
	Text txtDefeat = txtVictory;
	txtDefeat.setString("Defeat");
	txtDefeat.setBorderColor(RGB(171, 9, 9));
	Button btnRestart = btnContinue;
	btnRestart.TXT.setString("Restart");
	///Меню: Пауза
	Text txtPause = txtVictory;
	txtPause.setString("Pause");
	Button btnNextGame = btnContinue;
	btnNextGame.TXT.setString("Next");
	///
	Pacman pacman(&GameWindow);
	pacman.setPosition(GameplayMap);
	Blinky ghBlinky(&GameWindow);
	ghBlinky.reset(GameplayMap);
	Clyde ghClyde(&GameWindow);
	ghClyde.reset(GameplayMap);
	Pinky ghPinky(&GameWindow);
	ghPinky.reset(GameplayMap);
	Inky ghInky(&GameWindow);
	ghInky.reset(GameplayMap);
	Text txtPressPlay = txtError;
	txtPressPlay.setString("Press key to Start");
	txtPressPlay.setSize(20);
	txtPressPlay.setPosCentre(0.f, -25.f);
	Rectangle rctGameBar;
	rctGameBar = btnGame.getRectangle();
	rctGameBar.setColor(RGB(216, 142, 0));
	rctGameBar.setBorderColor(RGB(135, 90, 0));
	rctGameBar.setSize((_f32)_Settings::__Widht * 16.f, 16.f);
	rctGameBar.setPosition(0.f, (_f32)_Settings::__Height * 16.f);
	rctGameBar.setPosCentreOff();
	Text txtGameLevel = txtVictory;
	txtGameLevel.setSize(7);
	txtGameLevel.setBorder(0.f);
	txtGameLevel.setString("Lvl " + std::to_string(_Settings::__Level));
	txtGameLevel.setPosition(2.f, 2.f);
	txtGameLevel.setPosCentreOff();
	Text txtScore = btnGame.getText();
	txtScore.setSize(10);
	txtScore.setString("Score: 0");
	txtScore.setPosition(5.f, 339.f);
	txtScore.setPosCentreOff();
	Text txtTimer = txtScore;
	txtTimer.setPosition(300.f, 339.f);
	_i8 Key = '\\';
	_bool Pause = false;
	sf::Clock clk;
	_f32 Timer = 300.f;
	_f32 PrevTimer = 300.f;
	while (GameWindow.isOpen()) {
		_Settings::__ElapsedTime = clk.getElapsedTime().asSeconds();
		clk.restart();
		GameWindow.clear();
		_bool Key_flag {false};
		sf::Event event;
		while (GameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) GameWindow.close();
			if (event.type == sf::Event::KeyPressed && !btnPlay.isActive()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Pause ^= true;
				if (!Pause && !pacman.isDead()) pacman.control();
			}
			if (event.type == sf::Event::TextEntered && !btnCreateMap.isActive()) {
				Key = (_i8)event.text.unicode;
				if (event.text.unicode < 128) {
					if (Key == '\b' && NewMapName.size() > 0) {
						NewMapName.erase(NewMapName.size() - 1);
						Key_flag = true;
					}
					if (isAllowedSymbol(Key) && NewMapName.size() < 16) {
						NewMapName += Key;
						Key_flag = true;
					}
				}
			}
		}
		if (btnSettings.isActive() && btnGame.isActive()) { //Меню: Начальное
			GameWindow.draw(_Background);
			GameWindow.draw(_Logo);
			if (btnGame.draw()) btnGame.disable(); 
			if (btnSettings.draw()) btnSettings.disable();
			if (btnExit.draw()) GameWindow.close();
		}
		if (!btnSettings.isActive() && btnShow.isActive() && btnCreate.isActive()) { //Меню: Настройки
			GameWindow.draw(_Background);
			GameWindow.draw(_Logo);
			if (btnReturnSett.draw()) btnSettings.activate(); //Возврат назад
			if (btnNextLevel.draw()) { //Поменять цвет
				_iLevelColors++;
				txtLevel.setString(_Settings::__SkinNames[_iLevelColors % _Settings::__SkinNames.size()]);
				_Settings::__SkinNumber = _iLevelColors % _Settings::__SkinNames.size();
				unloadSettings();
			}
			if (btnNextName.draw()) { //Поменять карту
				_iNames++;
				_Settings::__MapNumber = _iNames % _Settings::__MapNames.size();
				txtName.setString(_Settings::__MapNames[_Settings::__MapNumber]);
				scanMap(GameMap, _Settings::__MapNames[_Settings::__MapNumber]);
				copyMap(GameMap, GameplayMap);
				scanHighscore(_Settings::__MapNames[_Settings::__MapNumber]);
				pacman.reset(GameplayMap);
				ghBlinky.reset(GameplayMap);
				ghClyde.reset(GameplayMap);
				ghPinky.reset(GameplayMap);
				ghInky.reset(GameplayMap);
				unloadSettings();
			}
			if (btnShow.draw()) btnShow.disable();
			if (btnCreate.draw()) { 
				ButMap = true;
				btnCreate.disable(); 
			}
			if (btn16P.boolManyToOne(btn16P.draw())) {
				btn16P.turnOffMouseClick(true);
				btn32P.turnOnMouseClick();
				btn64P.turnOnMouseClick();
				btn16P.turnOnSwitch();
				btn32P.turnOffSwitch();
				btn64P.turnOffSwitch();
				_Settings::__CellSize = 16;
				_Settings::__ScreenResize = 4;
				_Settings::__ScreenCoef = 1.f;
				unloadSettings();
				reloadLogo(_LogoTexture, _Logo);
				reloadBackground(_BackgroundTexture, _Background);
				reloadWindow(GameWindow);
			}
			if (btn32P.boolManyToOne(btn32P.draw())) {
				btn16P.turnOnMouseClick();
				btn32P.turnOffMouseClick(true);
				btn64P.turnOnMouseClick();
				btn16P.turnOffSwitch();
				btn32P.turnOnSwitch();
				btn64P.turnOffSwitch();
				_Settings::__CellSize = 32;
				_Settings::__ScreenResize = 2;
				_Settings::__ScreenCoef = 2.f;
				unloadSettings();
				reloadLogo(_LogoTexture, _Logo);
				reloadBackground(_BackgroundTexture, _Background);
				reloadWindow(GameWindow);
			}
			if (btn64P.boolManyToOne(btn64P.draw())) {
				btn16P.turnOnMouseClick();
				btn32P.turnOnMouseClick();
				btn64P.turnOffMouseClick(true);
				btn16P.turnOffSwitch();
				btn32P.turnOffSwitch();
				btn64P.turnOnSwitch();
				_Settings::__CellSize = 64;
				_Settings::__ScreenResize = 1;
				_Settings::__ScreenCoef = 4.f;
				unloadSettings();
				reloadLogo(_LogoTexture, _Logo);
				reloadBackground(_BackgroundTexture, _Background);
				reloadWindow(GameWindow);
			}
			rctName.draw();
			txtName.draw();
			rctLevel.draw();
			txtLevel.draw();
		}
		if (!btnShow.isActive()) { //Меню: Карта
			GameWindow.draw(_Background);
			rctDark.draw();
			drawMap(GameMap, GameWindow, true);
			if (bntReturnShowCreate.draw()) btnShow.activate(); //Возврат назад
			_bool ptr = (_Settings::__MapNames[_Settings::__MapNumber] == "Standart");
			if (btnDeleteMap.draw() && !ptr) {
				deleteMap(_iNames % _Settings::__MapNames.size());
				_iNames = 0;
				_Settings::__MapNumber = 0;
				scanMap(GameMap, _Settings::__MapNames[_Settings::__MapNumber]);
				copyMap(GameMap, GameplayMap);
				pacman.reset(GameplayMap);
				ghBlinky.reset(GameplayMap);
				ghClyde.reset(GameplayMap);
				ghPinky.reset(GameplayMap);
				ghInky.reset(GameplayMap);
				scanHighscore(_Settings::__MapNames[_Settings::__MapNumber]);
				txtName.setString(_Settings::__MapNames[_Settings::__MapNumber]);
				unloadSettings();
				btnShow.activate();
			}
			if (ptr) txtErrorDel.draw();
		}
		if (!btnCreate.isActive() && btnCreateMap.isActive()) { //Меню: Редактирование
			GameWindow.draw(_Background);
			rctDark.draw();
			drawMap(GameMapCreate, GameWindow, true);
			if (btnCreate.boolManyToOne(ButMap)) createButtonsMap(GameMapButtons, GameWindow);
			changeMap(GameMapCreate, GameMapButtons);
			Error_list ptr = changedMapIsCorrect(GameMapCreate);
			if (btnCreateMap.draw() && !ptr._Entity && !ptr._Pacman) btnCreateMap.disable(); //Потвердить создание
			if (bntReturnShowCreate.draw()) btnCreate.activate(); //Возврат назад
			if (ptr._Entity && !ptr._Pacman && !ptr._Pellet) { //Ошибка: Много сущностей
				txtError.draw();
				txtErrorReasonE.draw();
			}
			if (ptr._Pellet && !ptr._Pacman) { //Ошибка: Монеток не существует
				txtError.draw();
				txtErrorReasonPel.draw();
			}
			if (ptr._Pacman) { //Ошибка: Пакман не существует
				txtError.draw();
				txtErrorReasonPcmn.draw();
			}
		}
		if (!btnCreateMap.isActive()) { //Название карты
			GameWindow.draw(_Background);
			rctDark.draw();
			drawMap(GameMapCreate, GameWindow, true);
			GameWindow.draw(_Logo);
			rctInputNamePlease.draw();
			txtInputNamePlease.draw();
			rctInputName.draw();
			txtTypeName.setCentral(rctInputName.getPosition(), rctInputName.getSize());
			txtTypeName.draw();
			if (Key_flag) txtTypeName.setString(NewMapName);
			_bool ptr = isMapExist(NewMapName);
			if (btnSave.draw() && (NewMapName != "") && !ptr) { //Сохранение карты
				saveMap(GameMapCreate, NewMapName);
				scanMap(GameMap, NewMapName);
				copyMap(GameMap, GameplayMap);
				pacman.reset(GameplayMap); 
				ghBlinky.reset(GameplayMap); 
				ghClyde.reset(GameplayMap); 
				ghPinky.reset(GameplayMap); 
				ghInky.reset(GameplayMap);
				saveHighscore(0, NewMapName, true);
				txtName.setString(NewMapName);
				_iNames = _Settings::__MapNames.size() - 1;		
				_Settings::__MapNumber;
				scanHighscore(_Settings::__MapNames[_Settings::__MapNumber]);
				NewMapName = "";
				txtTypeName.setString("<<Name>>");
				unloadSettings();
				btnCreateMap.activate();
				btnCreate.activate();
			}
			if (btnReturnSave.draw()) { //Возврат назад
				if (NewMapName == "") txtTypeName.setString("<<Name>>");
				btnCreateMap.activate();
			} 
			if (ptr) {
				txtError.draw();
				ErrorReasonSave.draw();
			}
		}
		if (!btnGame.isActive() && btnPlay.isActive() && btnHighscore.isActive()) { //Меню: Игра
			GameWindow.draw(_Background);
			GameWindow.draw(_Logo);
			if (btnReturn.draw()) btnGame.activate(); //Возврат назад
			if (btnPlay.draw()) btnPlay.disable(); //Играть
			if (btnHighscore.draw()) btnHighscore.disable(); //Очки
		}
		if (!btnHighscore.isActive()) { //Меню: Игра
			GameWindow.draw(_Background);
			rctHighscore.draw();
			_Logo.setPosition(_f32(((_Settings::__Widht + _Settings::__ExtraWidht)* _Settings::__CellSize - _LogoTexture.getSize().x) / 2.f), 5.f * _Settings::__ScreenCoef);
			GameWindow.draw(_Logo);
			_i32 i = 0;
			for (auto u : _Settings::__MapScores) {
				txtHighscores.setSize(10);
				if (i > 8) txtHighscores.setString(std::to_string(i + 1) + ": " + std::to_string(_Settings::__MapScores[i]));
				else txtHighscores.setString(std::to_string(i + 1) + ":  " + std::to_string(_Settings::__MapScores[i]));
				txtHighscores.setPosition(55.f, _f32(90 + 15 * (i - 1)));
				if (i == 0) {
					txtHighscores.setString("Best: " + std::to_string(_Settings::__MapScores[0]));
					txtHighscores.setSize(15);
					txtHighscores.setPosition(55, 70);
				}
				txtHighscores.draw();
				i++;
			}
			reloadLogo(_LogoTexture, _Logo);
			if (btnReturn.draw()) btnHighscore.activate(); //Возврат назад
		}
		if (!btnPlay.isActive()) {
			drawMap(GameplayMap, GameWindow);
			pacman.mapCollision(GameplayMap);
			if (!Pause && !_Settings::__Victory && !_Settings::__Death && !pacman.isDead()) Timer -= _Settings::__ElapsedTime;
			if (Timer <= 0) pacman.die();
			_i32 minutes = (_i32)floorf(Timer / 60),
				 seconds = (_i32)floorf(Timer) - minutes * 60;
			if (PrevTimer - Timer >= 1.f && Timer > 0.f && !_Settings::__Victory && !pacman.isDead()) {
				pacman.addScore(-2);
				PrevTimer = Timer;
			}
			if (pacman.pressKeyPlease()) {
				ghBlinky.stop();
				ghClyde.stop();
				ghPinky.stop();
				ghInky.stop();
				Timer = 300.f;
				PrevTimer = 300.f;
				if (_Settings::__Level == 1) pacman.setScore(600);
			}
			else {
				ghBlinky.go();
				ghClyde.go();
				ghPinky.go();
				ghInky.go();
			}
			if (Pause || pacman.isDead()) {
				pacman.stop();
				ghBlinky.stop();
				ghClyde.stop();
				ghPinky.stop();
				ghInky.stop();
			}
			pacman.draw();
			ghBlinky.search(GameplayMap, pacman);
			ghBlinky.draw();
			ghClyde.search(GameplayMap, pacman);
			ghClyde.draw();
			ghPinky.search(GameplayMap, pacman);
			ghPinky.draw();
			ghInky.search(GameplayMap, pacman);
			ghInky.draw();
			rctGameBar.draw();
			txtScore.setString("Score: " + std::to_string(pacman.getScore()));
			txtScore.draw();
			std::string seconds_s = std::to_string(seconds);
			if (seconds_s.size() == 1) seconds_s = '0' + seconds_s;
			txtTimer.setString(std::to_string(minutes) + ':' + seconds_s);
			if (Timer <= 0) txtTimer.setString("0:00");
			txtTimer.draw();
			if (pacman.pressKeyPlease()) txtPressPlay.draw();
			txtGameLevel.draw();
			if (_Settings::__Victory || _Settings::__Death) {
				Pause = false;
				rctDark.draw();
				if (_Settings::__Victory) {
					txtVictory.draw();
					if (btnContinue.draw()) {
						copyMap(GameMap, GameplayMap);
						pacman.nextGame(GameplayMap);
						ghBlinky.nextGame();
						ghClyde.nextGame();
						ghPinky.nextGame();
						ghInky.nextGame();
						txtGameLevel.setString("Lvl " + std::to_string(_Settings::__Level));
						pacman.addScore(600);
						PrevTimer = 300.f;
						Timer = 300.f;
					}
				}
				if (_Settings::__Death) {
					txtDefeat.draw();
					PrevTimer = 300.f;
					Timer = 300.f;
					if (btnRestart.draw()) {
						saveHighscore(pacman.getScore(), _Settings::__MapNames[_Settings::__MapNumber]);
						copyMap(GameMap, GameplayMap);
						pacman.reset(GameplayMap);
						ghBlinky.reset(GameplayMap);
						ghClyde.reset(GameplayMap);
						ghPinky.reset(GameplayMap);
						ghInky.reset(GameplayMap);
						_Settings::__Level = 1;
						txtGameLevel.setString("Lvl " + std::to_string(_Settings::__Level));
					}
				}
				if (btnExitGame.draw()) {
					saveHighscore(pacman.getScore(), _Settings::__MapNames[_Settings::__MapNumber]);
					copyMap(GameMap, GameplayMap);
					pacman.reset(GameplayMap);
					ghBlinky.reset(GameplayMap);
					ghClyde.reset(GameplayMap);
					ghPinky.reset(GameplayMap);
					ghInky.reset(GameplayMap);
					btnPlay.activate();
					_Settings::__Level = 1;
					txtGameLevel.setString("Lvl " + std::to_string(_Settings::__Level));
				}
			}
			if (Pause && !pacman.isDead()) {
				rctDark.draw();
				txtPause.draw();
				if (btnContinue.draw()) {
					Pause = false;
					pacman.go();
					ghBlinky.go();
					ghClyde.go();
					ghPinky.go();
					ghInky.go();
				}
				if (btnExitGame.draw()) {
					if (!pacman.pressKeyPlease()) saveHighscore(pacman.getScore(), _Settings::__MapNames[_Settings::__MapNumber]);
					copyMap(GameMap, GameplayMap);
					pacman.reset(GameplayMap);
					ghBlinky.reset(GameplayMap);
					ghClyde.reset(GameplayMap);
					ghPinky.reset(GameplayMap);
					ghInky.reset(GameplayMap);
					btnPlay.activate();
					_Settings::__Level = 1;
					txtGameLevel.setString("Lvl " + std::to_string(_Settings::__Level));
					Pause = false;
				}
			}
		}
		GameWindow.display();
	}
	return 0;
}