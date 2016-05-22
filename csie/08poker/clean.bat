@ECHO OFF

IF EXIST expansion rd /s /q expansion

IF EXIST bots rd /s /q bots

IF EXIST data rd /s /q data

IF EXIST src\AITAclient\*.class del /q src\AITAclient\*.class

IF EXIST src\AITAclient\pokerserver.jar del /q src\AITAclient\pokerserver.jar

IF EXIST src\AITAclient\AITAPokerClient.jar del /q src\AITAclient\AITAPokerClient.jar

IF EXIST src\MyPokerClient\*.class del /q src\MyPokerClient\*.class

IF EXIST src\MyPokerClient\pokerserver.jar del /q src\MyPokerClient\pokerserver.jar

IF EXIST src\MyPokerClient\MyPokerClient.jar del /q src\MyPokerClient\MyPokerClient.jar

IF EXIST status.txt del /q status.txt

ECHO Cleaned
