@ECHO OFF

@IF "%2"=="" GOTO ERROR
java -cp pokerserver.jar;MyPokerClient.jar MyPokerClient %1 %2

GOTO END

:ERROR
@ECHO Usage: startme.bat ^<ipaddress^> ^<portnumber^>

:END
