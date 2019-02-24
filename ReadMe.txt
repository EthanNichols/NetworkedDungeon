Ethan Nichols

Usage:
This solution comes with two projects 'Server' and 'Client'. Feel free to start either program at any time. Sending commands from the client when there is no server won't cause any issues.

The built versions are located at $(SolutionDir)_Builds/$(Configuration)Platform/$(ProjectName)

Client Commands (Not case sensetive):
Enter Dungeon - Connect to the server and spawn a player
Move [Up/Down/Left/Right] - Move your character in the given direction
Get Treasure - Pickup one treasure that you're character is adjacent to. Also calls 'Treasure Amount'
Treasure Amount - Display the amount of treasure that you have
Leave Dungeon - Disconnect and delete your character from the dungeon. This also closes the client program.


Known issues:
Closing the window (Pressing 'X' in the upper right hand corner) when the client is connected to the server will not disconnect them and remove their character. Couldn't get the WM_CLOSE event to work properly to send a disconnect command to the server. This could have also been fixed by removing players that don't respond to the server after a period of time.

This isn't playable across multiple computers the server and client(s) have to be on the same computer. Could have tested this to make it work, but didn't feel like dealing with firewalls and allowing clients to set the IP for the server they want to connect to. Switching the server IP address to connect to can be done manually by editing Client/main.cpp:129(A, B, C, D, Port). If you change the port value, you'll need to change the server port as well located Server/main.cpp:140(0, Port). (You pass in 0 as the IP address so that it listens to all IPs that are coming in, with the given port value).

Changing the size of the map and treasure information can't be changed when the server is started. This is manually done by editing Server/main.cpp:132(width, height, maxTreasureValue, TreasureSpawnCount). Another simple thing I could have fixed, but didn't feel like it was necessary.

Having more than 64 tiles (treasures and players) on the map will cause clients connecting to the server to crash. An overflow occurs with the map data packet that is sent, since only 64 tile's information can be sent over. This could be fixed by splitting up the tiles that are sent into two different packets or by sending the entire map char array, which would send less data with more tiles on the map.