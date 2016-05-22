@ECHO OFF

rem ECHO Please your student ID here

SET STUDENT_ID=b

IF NOT EXIST expansion mkdir expansion

IF NOT EXIST expansion\expansion1 mkdir expansion\expansion1

IF NOT EXIST expansion\expansion2 mkdir expansion\expansion2

IF NOT EXIST expansion\expansion3 mkdir expansion\expansion3

IF NOT EXIST expansion\expansion4 mkdir expansion\expansion4

IF NOT EXIST expansion\expansion5 mkdir expansion\expansion5

IF NOT EXIST expansion\expansion6 mkdir expansion\expansion6

IF NOT EXIST bots mkdir bots

IF NOT EXIST data mkdir data

IF NOT EXIST data\cards mkdir data\cards

IF NOT EXIST data\results mkdir data\results

IF NOT EXIST data\serverlog mkdir data\serverlog

javac -d src\AITAclient -sourcepath src\AITAclient -cp lib\pokerserver.jar;lib]activation.jar;lib\mailapi.jar;lib\meerkat-api.jar;lib\smtp.jar src\AITAclient\*.java

javac -d src\MyPokerClient -sourcepath src\MyPokerClient -cp lib\pokerserver.jar;lib]activation.jar;lib\mailapi.jar;lib\meerkat-api.jar;lib\smtp.jar src\MyPokerClient\*.java

jar cf src\AITAclient\AITAPokerClient.jar -C src\AITAclient AITAPokerClient.class

jar cf src\MyPokerClient\MyPokerClient.jar -C src\MyPokerClient MyPokerClient.class

copy lib\pokerserver.jar src\AITAclient

copy lib\pokerserver.jar src\MyPokerClient

rem tar cf bots\aitaclient.tar -C src AITAclient
rem tar cf bots\%STUDENT_ID%.tar -C src MyPokerClient

jar cf bots\aitaclient.jar -C src AITAclient

jar cf bots\%STUDENT_ID%.jar -C src MyPokerClient
