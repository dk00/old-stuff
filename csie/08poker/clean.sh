#!/bin/bash
# Linux clean script for the poker server
# Author: Yuan-hsiang Lee

if [ -e "expansion" ]; 
    then rm -r -f expansion 
fi

if [ -e "bots" ]; 
    then rm -r -f bots
fi
if [ -e "data" ]; 
    then rm -r -f data 
fi

rm -f src/AITAclient/*.class

rm -f src/AITAclient/pokerserver.jar

rm -f src/AITAclient/AITAPokerClient.jar

rm -f src/MyPokerClient/*.class

rm -f src/MyPokerClient/pokerserver.jar

rm -f src/MyPokerClient/MyPokerClient.jar

rm -f status.txt

echo Cleaned
