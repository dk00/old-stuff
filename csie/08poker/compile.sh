#!/bin/bash
#
# Linux compile script for the poker server
# After running compile.sh, look for a run.sh script
# to avoid typing out a classpath
# Author: Christian Smith
# Modified by: Yuan-hsiang Lee

# Please fill in your student ID
STUDENT_ID=your_id

if [ ! -e "expansion" ]; 
    then mkdir expansion 
fi

if [ ! -e "expansion/expansion1" ];
    then mkdir expansion/expansion1
fi

if [ ! -e "expansion/expansion2" ];
    then mkdir expansion/expansion2
fi

if [ ! -e "expansion/expansion3" ];
    then mkdir expansion/expansion3
fi

if [ ! -e "expansion/expansion4" ];
    then mkdir expansion/expansion4
fi

if [ ! -e "expansion/expansion5" ];
    then mkdir expansion/expansion5
fi

if [ ! -e "expansion/expansion6" ];
    then mkdir expansion/expansion6
fi

if [ ! -e "bots" ]; 
    then mkdir  bots 
fi
if [ ! -e "data" ]; 
    then mkdir data 
fi

if [ ! -e "data/cards" ]; 
    then mkdir data/cards
fi

if [ ! -e "data/results" ]; 
    then mkdir data/results
fi

if [ ! -e "data/serverlog" ]; 
    then mkdir data/serverlog
fi

javac -d src/AITAclient -sourcepath src/AITAclient -cp lib/pokerserver.jar:lib/activation.jar:lib/mailapi.jar:lib/meerkat-api.jar:lib/smtp.jar src/AITAclient/*.java

javac -d src/MyPokerClient -sourcepath src/MyPokerClient -cp lib/pokerserver.jar:lib/activation.jar:lib/mailapi.jar:lib/meerkat-api.jar:lib/smtp.jar src/MyPokerClient/*.java

echo Done Compiling

cp lib/pokerserver.jar src/AITAclient

cp lib/pokerserver.jar src/MyPokerClient

jar cf src/AITAclient/AITAPokerClient.jar -C src/AITAclient AITAPokerClient.class

jar cf src/MyPokerClient/MyPokerClient.jar -C src/MyPokerClient MyPokerClient.class

tar cf bots/aitaclient.tar -C src AITAclient

tar cf bots/$STUDENT_ID.tar -C src MyPokerClient

jar cf bots/aitaclient.jar -C src AITAclient

jar cf bots/$STUDENT_ID.jar -C src MyPokerClient
