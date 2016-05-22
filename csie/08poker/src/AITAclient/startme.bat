@ECHO OFF

@IF "%2"=="" GOTO ERROR
java -cp pokerserver.jar;AITAPokerClient.jar AITAPokerClient %1 %2

GOTO END

:ERROR
@ECHO Usage: startme.bat ^<ipaddress^> ^<portnumber^>

:END
